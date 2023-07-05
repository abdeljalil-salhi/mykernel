#ifndef KERNEL_CPU_H
#define KERNEL_CPU_H

#include "TypeDefs.h"

typedef struct
{

} _CPU;

void OutByte(uint16_t Port, uint8_t Value);
uint8_t InByte(uint16_t Port);
void IOWait(void);

#endif // KERNEL_CPU_H