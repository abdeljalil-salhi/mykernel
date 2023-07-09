KERNEL		=	mykernel.bin

CROSS_CC	=	i686-elf-gcc
CROSS_FLAGS	=	-std=gnu99 -ffreestanding -O2 -Wall -Wextra
GRUB_ISO	=	grub-mkrescue
NASM		=	i686-elf-as

BOOT_LOADER	:=	Boot.s
BOOT_LOADER	:=	$(addprefix Kernel/, $(BOOT_LOADER))
C_SOURCES	:=	Kernel.c
_INTERRUPTS	:=	Interrupts/GateDescriptor32.c Interrupts/InterruptDescriptorTable32.c Interrupts/IDTDescriptor.c \
				Interrupts/InterruptHandler.c
_C_SOURCES	:=	TTY.c Lib.c CPU.c
_C_SOURCES	+=	$(_INTERRUPTS)
_C_SOURCES	:=	$(addprefix Sources/, $(_C_SOURCES))
C_SOURCES	:=	$(addprefix Kernel/, $(C_SOURCES) $(_C_SOURCES))
LINKER		:=	Linker.ld
GRUB_CONF	:=	GRUB.cfg

OBJS		=	$(BOOT_LOADER:.s=.o) $(C_SOURCES:.c=.o)

INCLUDES	=	Kernel/Include/Kernel Kernel/Include
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
				mkdir -p ISODir/Boot/GRUB
				cp $(KERNEL) ISODir/Boot/$(KERNEL)
				cp $(GRUB_CONF) ISODir/Boot/GRUB/$(GRUB_CONF)
				$(GRUB_ISO) -o $(KERNEL:.bin=.iso) ISODir

.PHONY		:	run
run			:	$(KERNEL)
				qemu-system-i386 -kernel $(KERNEL)

.PHONY		:	clean
clean		:
				rm -rf $(OBJS)
.PHONY		:	fclean
fclean		:	clean
				rm -rf $(KERNEL) $(KERNEL:.bin=.iso) ISODir

.PHONY		:	re
re			:	fclean all
