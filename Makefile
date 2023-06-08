CC		=	i686-elf-gcc
NASM	=	nasm
NAME	=	mykernel.bin

all		:
			$(CC) -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
			$(NASM) -f elf boot.asm -o boot.o
			$(CC) -T linker.ld -o $(NAME) -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

fclean	:
			rm -rf kernel.o boot.o $(NAME)

.PHONY	:	all fclean
