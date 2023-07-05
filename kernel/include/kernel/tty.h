#ifndef KERNEL_TTY_H
#define KERNEL_TTY_H

#include "TypeDefs.h"

/* Hardware text mode color constants. */
enum VGAColor
{
    VGA_COLOR_BLACK,
    VGA_COLOR_BLUE,
    VGA_COLOR_GREEN,
    VGA_COLOR_CYAN,
    VGA_COLOR_RED,
    VGA_COLOR_MAGENTA,
    VGA_COLOR_BROWN,
    VGA_COLOR_LIGHT_GREY,
    VGA_COLOR_DARK_GREY,
    VGA_COLOR_LIGHT_BLUE,
    VGA_COLOR_LIGHT_GREEN,
    VGA_COLOR_LIGHT_CYAN,
    VGA_COLOR_LIGHT_RED,
    VGA_COLOR_LIGHT_MAGENTA,
    VGA_COLOR_LIGHT_BROWN,
    VGA_COLOR_WHITE,
};

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

typedef struct
{
    size_t Row;
    size_t Column;
    uint8_t Color;
    uint16_t *Buffer;
    uint8_t ForegroundDefault;
    uint8_t BackgroundDefault;
} _Terminal;

extern _Terminal Terminal;

static inline uint8_t VGAEntryColor(enum VGAColor Foreground, enum VGAColor Background)
{
    return Foreground | Background << 4;
}

static inline uint16_t VGAEntry(unsigned char UC, uint8_t Color)
{
    return (uint16_t)UC | (uint16_t)Color << 8;
}

void TerminalInitialize(void);
void TerminalClear(void);
void TerminalPutCharacter(char C);
void TerminalWrite(const char *Data, size_t Size, uint8_t Color);
void TerminalWriteString(const char *Data, uint8_t Color);
void TerminalSetColor(uint8_t Color);
void TerminalPutEntryAt(char C, uint8_t Color, size_t X, size_t Y);

#endif