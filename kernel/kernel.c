#include "tty.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
# error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
# error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

t_terminal terminal = {
    .row = 0,
    .column = 0,
    .color = 0,
    .buffer = NULL,
    .fg_default = 0,
    .bg_default = 0
};

void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();

	terminal_writestring("Hello, \akernel\a World!\n\n\n", terminal.fg_default);
	terminal_writestring("Error: Abort.\n", VGA_COLOR_RED);
}
