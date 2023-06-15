#include "tty.h"
#include "lib.h"

void terminal_initialize(void)
{
	terminal.row = 0;
	terminal.column = 0;
	terminal.fg_default = VGA_COLOR_LIGHT_GREY;
	terminal.bg_default = VGA_COLOR_BLACK;
	terminal.color = vga_entry_color(terminal.fg_default, terminal.bg_default);
	terminal.buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal.buffer[index] = vga_entry(' ', terminal.color);
		}
	}
}

void terminal_putchar(char c)
{
	if (c == '\n')
		terminal.column = VGA_WIDTH - 1;
	else
		terminal_putentryat(c, terminal.color, terminal.column, terminal.row);
	if (++terminal.column == VGA_WIDTH) {
		terminal.column = 0;
		if (++terminal.row == VGA_HEIGHT)
			terminal.row = 0;
	}
}

void terminal_write(const char* data, size_t size, uint8_t color)
{
	terminal_setcolor(color);
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data, uint8_t color)
{
	terminal_write(data, strlen(data), color);
}

void terminal_setcolor(uint8_t color)
{
	terminal.color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal.buffer[index] = vga_entry(c, color);
}
