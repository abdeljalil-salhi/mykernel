#include "Interrupts.h"

void SetSize(_IDTDescriptor *Descriptor, uint16_t Size)
{
    Descriptor->Size = Size;
}

void SetAddress(_IDTDescriptor *Descriptor, uint32_t Address)
{
    Descriptor->Address = Address;
}

uint16_t GetSize(_IDTDescriptor *Descriptor)
{
    return Descriptor->Size;
}

uint32_t GetAddress(_IDTDescriptor *Descriptor)
{
    return Descriptor->Address;
}
