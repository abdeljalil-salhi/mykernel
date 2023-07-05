#ifndef KERNEL_INTERRUPTS_H
#define KERNEL_INTERRUPTS_H

#include "TypeDefs.h"

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

void SetOffset(_GateDescriptor32 *Descriptor, uint32_t Offset);
void SetSegmentSelector(_GateDescriptor32 *Descriptor, uint16_t SegmentSelector);
void SetGateType(_GateDescriptor32 *Descriptor, enum GateType GateType);
void SetDPL(_GateDescriptor32 *Descriptor, uint8_t DPL);
void SetPresent(_GateDescriptor32 *Descriptor, bool Present);

uint32_t GetOffset(_GateDescriptor32 *Descriptor);
uint16_t GetSegmentSelector(_GateDescriptor32 *Descriptor);
enum GateType GetGateType(_GateDescriptor32 *Descriptor);
uint8_t GetDPL(_GateDescriptor32 *Descriptor);
bool GetPresent(_GateDescriptor32 *Descriptor);

_GateDescriptor32 CreateGateDescriptor32(uint32_t Offset, uint16_t SegmentSelector,
                                         enum GateType GateType, uint8_t DPL, bool Present);

typedef struct
{
    _GateDescriptor32 Descriptors[IDT_SIZE];
} __attribute__((packed)) _InterruptDescriptorTable32;

void InsertNewEntry(_InterruptDescriptorTable32 *IDT, _GateDescriptor32 Descriptor, size_t Index);
const _GateDescriptor32 *GetEntry(_InterruptDescriptorTable32 *IDT, size_t Index);

typedef struct
{
    uint16_t Size;
    uint32_t Address;
} __attribute__((packed)) _IDTDescriptor;

void SetSize(_IDTDescriptor *Descriptor, uint16_t Size);
void SetAddress(_IDTDescriptor *Descriptor, uint32_t Address);

uint16_t GetSize(_IDTDescriptor *Descriptor);
uint32_t GetAddress(_IDTDescriptor *Descriptor);

#endif