#include "TTY.h"
#include "Interrupts.h"

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

void KeyboardHandler(void);
void DefaultHandler(void);

void KernelMain(void *InterruptDescriptorTableAddress, void *IDTDescriptorAddress)
{
    /* Initialize terminal interface */
    TerminalInitialize();

    _InterruptDescriptorTable32 *IDT = (_InterruptDescriptorTable32 *)InterruptDescriptorTableAddress;
    _IDTDescriptor *IDTDescriptor = (_IDTDescriptor *)IDTDescriptorAddress;

    /* Initialize IDT */
    _GateDescriptor32 GateDescriptor = CreateGateDescriptor32((uint32_t)KeyboardHandler, 0x08, GATE_INTERRUPT_32, 0x0, true);
    InsertNewEntry(&IDT, GateDescriptor, 0x20 + 1);

    SetAddress(IDTDescriptor, (uint32_t)InterruptDescriptorTableAddress);
    SetSize(IDTDescriptor, sizeof(_InterruptDescriptorTable32) - 1);

    TerminalWriteString("Hello, \akernel\a World!\n\n\n", Terminal.ForegroundDefault);
    TerminalWriteString("Error: Abort.\n", VGA_COLOR_RED);
}
