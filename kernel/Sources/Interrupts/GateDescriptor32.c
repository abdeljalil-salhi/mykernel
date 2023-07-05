#include "Interrupts.h"

void SetOffset(_GateDescriptor32 *Descriptor, uint32_t Offset)
{
    Descriptor->OffsetLow = Offset & 0xFFFF;
    Descriptor->OffsetHigh = (Offset >> 16) & 0xFFFF;
}

void SetSegmentSelector(_GateDescriptor32 *Descriptor, uint16_t SegmentSelector)
{
    Descriptor->SegmentSelector = SegmentSelector;
}

void SetGateType(_GateDescriptor32 *Descriptor, enum GateType GateType)
{
    Descriptor->GateType = GateType;
}

void SetDPL(_GateDescriptor32 *Descriptor, uint8_t DPL)
{
    Descriptor->DPL = DPL;
}

void SetPresent(_GateDescriptor32 *Descriptor, bool Present)
{
    Descriptor->Present = Present;
}

uint32_t GetOffset(_GateDescriptor32 *Descriptor)
{
    return (Descriptor->OffsetHigh << 16) | Descriptor->OffsetLow;
}

uint16_t GetSegmentSelector(_GateDescriptor32 *Descriptor)
{
    return Descriptor->SegmentSelector;
}

enum GateType GetGateType(_GateDescriptor32 *Descriptor)
{
    if (Descriptor->GateType == GATE_TYPE_TASK)
        return GATE_TYPE_TASK;
    if (Descriptor->GateType == GATE_INTERRUPT_16)
        return GATE_INTERRUPT_16;
    if (Descriptor->GateType == GATE_TRAP_16)
        return GATE_TRAP_16;
    if (Descriptor->GateType == GATE_INTERRUPT_32)
        return GATE_INTERRUPT_32;
    if (Descriptor->GateType == GATE_TRAP_32)
        return GATE_TRAP_32;
    return GATE_UNDEFINED;
}

uint8_t GetDPL(_GateDescriptor32 *Descriptor)
{
    return Descriptor->DPL;
}

bool GetPresent(_GateDescriptor32 *Descriptor)
{
    return Descriptor->Present;
}

_GateDescriptor32 CreateGateDescriptor32(uint32_t Offset, uint16_t SegmentSelector,
                                         enum GateType GateType, uint8_t DPL, bool Present)
{
    _GateDescriptor32 Descriptor;
    SetOffset(&Descriptor, Offset);
    SetSegmentSelector(&Descriptor, SegmentSelector);
    SetGateType(&Descriptor, GateType);
    Descriptor.Reserved = 0;
    Descriptor.Zero = 0;
    SetDPL(&Descriptor, DPL);
    SetPresent(&Descriptor, Present);
    return Descriptor;
}
