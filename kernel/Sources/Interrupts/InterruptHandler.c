#include "Interrupts.h"
#include "Keyboard.h"
#include "TTY.h"
#include "CPU.h"

extern void _KeyboardHandler(void)
{
    char String[2] = {0};
    uint8_t _Scancode = Scancode();
    String[0] = GetCharacterFromScancode(_Scancode);
    TerminalWriteString(String, Terminal.ForegroundDefault);
    OutByte(0x20, 0x20);
}

extern void _DefaultHandler(void)
{
    TerminalWriteString("DefaultHandler\n", Terminal.ForegroundDefault);
}
