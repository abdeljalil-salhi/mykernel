#include "Keyboard.h"
#include "CPU.h"

_Keyboard Keyboard;

void KeyboardInitialize(void)
{
    Keyboard.ScancodeIndex = 0;
    Keyboard.ScancodeSet = 2;
    Keyboard.IsExtended = false;
    Keyboard.IsLeftShiftPressed = false;
    Keyboard.IsRightShiftPressed = false;
    Keyboard.IsCapsLockPressed = false;
    Keyboard.IsNumLockPressed = false;
    Keyboard.IsScrollLockPressed = false;
    Keyboard.Scancodes[0x01] = (_Scancode){0x01, '?', false};
    Keyboard.Scancodes[0x02] = (_Scancode){0x02, '1', false};
    Keyboard.Scancodes[0x03] = (_Scancode){0x03, '2', false};
    Keyboard.Scancodes[0x04] = (_Scancode){0x04, '3', false};
    Keyboard.Scancodes[0x05] = (_Scancode){0x05, '4', false};
    Keyboard.Scancodes[0x06] = (_Scancode){0x06, '5', false};
    Keyboard.Scancodes[0x07] = (_Scancode){0x07, '6', false};
    Keyboard.Scancodes[0x08] = (_Scancode){0x08, '7', false};
    Keyboard.Scancodes[0x09] = (_Scancode){0x09, '8', false};
    Keyboard.Scancodes[0x0A] = (_Scancode){0x0A, '9', false};
    Keyboard.Scancodes[0x0B] = (_Scancode){0x0B, '0', false};
    Keyboard.Scancodes[0x0C] = (_Scancode){0x0C, '-', false};
    Keyboard.Scancodes[0x0D] = (_Scancode){0x0D, '=', false};
    Keyboard.Scancodes[0x0E] = (_Scancode){0x0E, '\b', false};
    Keyboard.Scancodes[0x0F] = (_Scancode){0x0F, '\t', false};
    Keyboard.Scancodes[0x10] = (_Scancode){0x10, 'q', false};
    Keyboard.Scancodes[0x11] = (_Scancode){0x11, 'w', false};
    Keyboard.Scancodes[0x12] = (_Scancode){0x12, 'e', false};
    Keyboard.Scancodes[0x13] = (_Scancode){0x13, 'r', false};
    Keyboard.Scancodes[0x14] = (_Scancode){0x14, 't', false};
    Keyboard.Scancodes[0x15] = (_Scancode){0x15, 'y', false};
    Keyboard.Scancodes[0x16] = (_Scancode){0x16, 'u', false};
    Keyboard.Scancodes[0x17] = (_Scancode){0x17, 'i', false};
    Keyboard.Scancodes[0x18] = (_Scancode){0x18, 'o', false};
    Keyboard.Scancodes[0x19] = (_Scancode){0x19, 'p', false};
    Keyboard.Scancodes[0x1A] = (_Scancode){0x1A, '[', false};
    Keyboard.Scancodes[0x1B] = (_Scancode){0x1B, ']', false};
    Keyboard.Scancodes[0x1C] = (_Scancode){0x1C, '\n', false};
    Keyboard.Scancodes[0x1D] = (_Scancode){0x1D, 0, false}; // Left Control
    Keyboard.Scancodes[0x1E] = (_Scancode){0x1E, 'a', false};
    Keyboard.Scancodes[0x1F] = (_Scancode){0x1F, 's', false};
    Keyboard.Scancodes[0x20] = (_Scancode){0x20, 'd', false};
    Keyboard.Scancodes[0x21] = (_Scancode){0x21, 'f', false};
    Keyboard.Scancodes[0x22] = (_Scancode){0x22, 'g', false};
    Keyboard.Scancodes[0x23] = (_Scancode){0x23, 'h', false};
    Keyboard.Scancodes[0x24] = (_Scancode){0x24, 'j', false};
    Keyboard.Scancodes[0x25] = (_Scancode){0x25, 'k', false};
    Keyboard.Scancodes[0x26] = (_Scancode){0x26, 'l', false};
    Keyboard.Scancodes[0x27] = (_Scancode){0x27, ';', false};
    Keyboard.Scancodes[0x28] = (_Scancode){0x28, '\'', false};
    Keyboard.Scancodes[0x29] = (_Scancode){0x29, '`', false};
    Keyboard.Scancodes[0x2A] = (_Scancode){0x2A, 0, false}; // Left Shift
    Keyboard.Scancodes[0x2B] = (_Scancode){0x2B, '\\', false};
    Keyboard.Scancodes[0x2C] = (_Scancode){0x2C, 'z', false};
    Keyboard.Scancodes[0x2D] = (_Scancode){0x2D, 'x', false};
    Keyboard.Scancodes[0x2E] = (_Scancode){0x2E, 'c', false};
    Keyboard.Scancodes[0x2F] = (_Scancode){0x2F, 'v', false};
    Keyboard.Scancodes[0x30] = (_Scancode){0x30, 'b', false};
    Keyboard.Scancodes[0x31] = (_Scancode){0x31, 'n', false};
    Keyboard.Scancodes[0x32] = (_Scancode){0x32, 'm', false};
    Keyboard.Scancodes[0x33] = (_Scancode){0x33, ',', false};
    Keyboard.Scancodes[0x34] = (_Scancode){0x34, '.', false};
    Keyboard.Scancodes[0x35] = (_Scancode){0x35, '/', false};
    Keyboard.Scancodes[0x36] = (_Scancode){0x36, 0, false}; // Right Shift
    Keyboard.Scancodes[0x37] = (_Scancode){0x37, '*', false};
    Keyboard.Scancodes[0x38] = (_Scancode){0x38, 0, false}; // Left Alt
    Keyboard.Scancodes[0x39] = (_Scancode){0x39, ' ', false};
    Keyboard.Scancodes[0x3A] = (_Scancode){0x3A, 0, false}; // Caps Lock
    Keyboard.Scancodes[0x3B] = (_Scancode){0x3B, 0, false}; // F1
    Keyboard.Scancodes[0x3C] = (_Scancode){0x3C, 0, false}; // F2
    Keyboard.Scancodes[0x3D] = (_Scancode){0x3D, 0, false}; // F3
    Keyboard.Scancodes[0x3E] = (_Scancode){0x3E, 0, false}; // F4
    Keyboard.Scancodes[0x3F] = (_Scancode){0x3F, 0, false}; // F5
    Keyboard.Scancodes[0x40] = (_Scancode){0x40, 0, false}; // F6
    Keyboard.Scancodes[0x41] = (_Scancode){0x41, 0, false}; // F7
    Keyboard.Scancodes[0x42] = (_Scancode){0x42, 0, false}; // F8
    Keyboard.Scancodes[0x43] = (_Scancode){0x43, 0, false}; // F9
    Keyboard.Scancodes[0x44] = (_Scancode){0x44, 0, false}; // F10
    Keyboard.Scancodes[0x45] = (_Scancode){0x45, 0, false}; // Num Lock
}

bool IsSpecialKey(uint8_t Key)
{
    if (Key == 0x3A)
        Keyboard.IsCapsLockPressed = !Keyboard.IsCapsLockPressed;
    return Key == 0x2A || Key == 0x36 || Key == 0x1D || Key == 0x38 || Key == 0x3A || Key == 0x45;
}

char GetCharacterFromScancode(uint8_t Scancode)
{
    for (int I = 0; i < 0x46; I++)
    {
        if (Keyboard.Scancodes[I].Value == Scancode)
        {
            if (IsSpecialKey(Scancode))
                return 0;
            if (Keyboard.IsCapsLockPressed)
                return Keyboard.Scancodes[I].Value - 32;
            return Keyboard.Scancodes[I].Value;
        }
    }
}

uint8_t Scancode(void)
{
    return InByte(0x60);
}
