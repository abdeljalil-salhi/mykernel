#include "TTY.h"
#include "Lib.h"

void TerminalInitialize(void)
{
    Terminal.ForegroundDefault = VGA_COLOR_LIGHT_GREY;
    Terminal.BackgroundDefault = VGA_COLOR_BLACK;
    Terminal.Color = VGAEntryColor(Terminal.ForegroundDefault, Terminal.BackgroundDefault);
    Terminal.Buffer = (uint16_t *)0xB8000;
    TerminalClear();
}

void TerminalClear(void)
{
    for (size_t X = 0; X < VGA_WIDTH; X++)
    {
        const size_t Index = X;
        Terminal.Buffer[Index] = VGAEntry(' ', VGAEntryColor(VGA_COLOR_WHITE, VGA_COLOR_BLUE));
    }
    for (size_t Y = 1; Y < VGA_HEIGHT - 1; Y++)
    {
        for (size_t X = 0; X < VGA_WIDTH; X++)
        {
            const size_t Index = Y * VGA_WIDTH + X;
            Terminal.Buffer[Index] = VGAEntry(' ', Terminal.Color);
        }
    }
    for (size_t X = 0; X < VGA_WIDTH; X++)
    {
        const size_t Index = (VGA_HEIGHT - 1) * VGA_WIDTH + X;
        Terminal.Buffer[Index] = VGAEntry(' ', VGAEntryColor(VGA_COLOR_WHITE, VGA_COLOR_BLUE));
    }
    Terminal.Row = 2;
    Terminal.Column = 2;
}

void TerminalSpecial(char C)
{
    if (C == '\b')
    {
        if (Terminal.Column > 2)
            Terminal.Column--;
        TerminalPutEntryAt(' ', Terminal.Color, Terminal.Column, Terminal.Row);
    }
    else if (C == '\n')
        Terminal.Column = VGA_WIDTH - 3;
    else if (C == '\t')
    {
        Terminal.Column += 4;
        if (Terminal.Column >= VGA_WIDTH - 3)
            Terminal.Column = VGA_WIDTH - 3;
    }
    else if (C == '\r')
        Terminal.Column = 2;
    else if (C == '\f')
        TerminalClear();
    else if (C == '\v' && ++Terminal.Row >= VGA_HEIGHT - 2)
        Terminal.Row = 2;
    else if (C == '\a' && Terminal.Color != VGAEntryColor(VGA_COLOR_RED, VGA_COLOR_BLACK))
        Terminal.Color = VGAEntryColor(VGA_COLOR_RED, VGA_COLOR_BLACK), Terminal.Column--;
    else if (C == '\a' && Terminal.Color == VGAEntryColor(VGA_COLOR_RED, VGA_COLOR_BLACK))
        Terminal.Color = VGAEntryColor(Terminal.ForegroundDefault, Terminal.BackgroundDefault), Terminal.Column--;
}

void TerminalPutCharacter(char C)
{
    if (C == '\b' || C == '\n' || C == '\t' || C == '\r' || C == '\f' || C == '\v' || C == '\a')
        TerminalSpecial(C);
    else
        TerminalPutEntryAt(C, Terminal.Color, Terminal.Column, Terminal.Row);
    if (++Terminal.Column == VGA_WIDTH - 2)
    {
        Terminal.Column = 2;
        if (++Terminal.Row == VGA_HEIGHT - 2)
            Terminal.Row = 2;
    }
}

void TerminalWrite(const char *Data, size_t Size, uint8_t Color)
{
    TerminalSetColor(Color);
    for (size_t I = 0; I < Size; I++)
        TerminalPutCharacter(Data[I]);
}

void TerminalWriteString(const char *Data, uint8_t Color)
{
    TerminalWrite(Data, StringLength(Data), Color);
}

void TerminalSetColor(uint8_t Color)
{
    Terminal.Color = Color;
}

void TerminalPutEntryAt(char C, uint8_t Color, size_t X, size_t Y)
{
    const size_t Index = Y * VGA_WIDTH + X;
    Terminal.Buffer[Index] = VGAEntry(C, Color);
}
