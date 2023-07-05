#include "TTY.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

_Terminal Terminal = {
    .Row = 0,
    .Column = 0,
    .Color = 0,
    .Buffer = NULL,
    .ForegroundDefault = 0,
    .BackgroundDefault = 0};

void KernelMain(void)
{
    /* Initialize terminal interface */
    TerminalInitialize();

    TerminalWriteString("Hello, \akernel\a World!\n\n\n", Terminal.ForegroundDefault);
    TerminalWriteString("Error: Abort.\n", VGA_COLOR_RED);
}
