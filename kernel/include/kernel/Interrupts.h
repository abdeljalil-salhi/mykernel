#ifndef KERNEL_INTERRUPTS_H
#define KERNEL_INTERRUPTS_H

#include <stddef.h>
#include <stdint.h>

#define IDT_SIZE 256

enum GateType
{
    GATE_UNDEFINED = 0x0,
    GATE_TYPE_TASK = 0x5,
    GATE_INTERRUPT_16 = 0x6,
    GATE_TRAP_16 = 0x7,
    GATE_INTERRUPT_32 = 0xE,
    GATE_TRAP_32 = 0xF
};

typedef struct
{
    uint32_t OffsetLow : 16;
    uint32_t SegmentSelector : 16;
    uint32_t Reserved : 8;
    uint32_t GateType : 4;
    uint32_t Zero : 1;
    uint32_t DPL : 2;
    uint32_t Present : 1;
    uint32_t OffsetHigh : 16;
} __attribute__((packed)) _GateDescriptor32;

typedef struct
{
    _GateDescriptor32 Descriptors[IDT_SIZE];
} __attribute__((packed)) _InterruptDescriptorTable32;

typedef struct
{
    uint16_t Size;
    uint32_t Address;
} __attribute__((packed)) _IDTDescriptor;

#endif