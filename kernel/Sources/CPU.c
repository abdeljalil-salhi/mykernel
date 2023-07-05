#include "CPU.h"

void OutByte(uint16_t Port, uint8_t Value)
{
    asm volatile("outb %0, %1"
                 :
                 : "a"(Value), "Nd"(Port));
}

uint8_t InByte(uint16_t Port)
{
    uint8_t Result;
    asm volatile("inb %1, %0"
                 : "=a"(Result)
                 : "Nd"(Port));
    return Result;
}

void IOWait(void)
{
    OutByte(0x80, 0);
}

// Path: Kernel/Sources/CPU.c