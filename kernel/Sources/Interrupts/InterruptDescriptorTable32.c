#include "Interrupts.h"

void InsertNewEntry(_InterruptDescriptorTable32 *IDT, _GateDescriptor32 Descriptor, size_t Index)
{
    if (Index < IDT_SIZE)
        IDT->Descriptors[Index] = Descriptor;
}

const _GateDescriptor32 *GetEntry(_InterruptDescriptorTable32 *IDT, size_t Index)
{
    if (Index < IDT_SIZE)
        return &IDT->Descriptors[Index];
    return NULL;
}
