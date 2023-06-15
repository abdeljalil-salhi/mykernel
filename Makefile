KERNEL		=	mykernel.bin

CROSS_CC	=	i686-elf-gcc
CROSS_FLAGS	=	-std=gnu99 -ffreestanding -O2 -Wall -Wextra
GRUB_ISO	=	grub-mkrescue
NASM		=	i686-elf-as

BOOT_LOADER	:=	boot.s
BOOT_LOADER	:=	$(addprefix kernel/, $(BOOT_LOADER))
C_SOURCES	:=	kernel.c
_C_SOURCES	:=	tty.c lib.c
_C_SOURCES	:=	$(addprefix src/, $(_C_SOURCES))
C_SOURCES	:=	$(addprefix kernel/, $(C_SOURCES) $(_C_SOURCES))
LINKER		:=	linker.ld
GRUB_CONF	:=	grub.cfg

OBJS		=	$(BOOT_LOADER:.s=.o) $(C_SOURCES:.c=.o)

INCLUDES	=	kernel/include/kernel
CROSS_FLAGS	+=	$(addprefix -I, $(INCLUDES))

.s.o		:
				$(NASM) $< -o $(<:.s=.o)
.c.o		:
				$(CROSS_CC) -c $< -o $(<:.c=.o) $(CROSS_FLAGS)

.PHONY		:	all
all			:	$(KERNEL)

$(KERNEL)	:	$(OBJS)
				$(CROSS_CC) -T $(LINKER) -o $(KERNEL) -ffreestanding -O2 -nostdlib $(OBJS)

.PHONY		:	verify
verify		:	$(KERNEL)
				sh test.sh

.PHONY		:	build
build		:	$(KERNEL)
				mkdir -p isodir/boot/grub
				cp $(KERNEL) isodir/boot/$(KERNEL)
				cp $(GRUB_CONF) isodir/boot/grub/$(GRUB_CONF)
				$(GRUB_ISO) -o $(KERNEL:.bin=.iso) isodir

.PHONY		:	run
run			:	$(KERNEL)
				qemu-system-i386 -kernel $(KERNEL)

.PHONY		:	clean
clean		:
				rm -rf $(OBJS)
.PHONY		:	fclean
fclean		:	clean
				rm -rf $(KERNEL) $(KERNEL:.bin=.iso) isodir

.PHONY		:	re
re			:	fclean all
