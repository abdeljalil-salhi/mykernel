#ifndef KERNEL_KEYBOARD_H
#define KERNEL_KEYBOARD_H

#include "TypeDefs.h"

typedef struct
{
    uint8_t Key;
    uint8_t Value;
    bool IsPressed;
} _Scancode;

typedef struct
{
    _Scancode Scancodes[256];
    uint8_t ScancodeIndex;
    uint8_t ScancodeSet;
    bool IsExtended;
    bool IsLeftShiftPressed;
    bool IsRightShiftPressed;
    bool IsCapsLockPressed;
    bool IsNumLockPressed;
    bool IsScrollLockPressed;
} _Keyboard;

extern _Keyboard Keyboard;

void KeyboardInitialize(void);
bool IsSpecialKey(uint8_t Key);
char GetCharacterFromScancode(uint8_t Scancode);
uint8_t Scancode(void);

#endif // KERNEL_KEYBOARD_H