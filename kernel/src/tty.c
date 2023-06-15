#include "tty.h"
#include "lib.h"

void terminal_initialize(void)
{
	terminal.fg_default = VGA_COLOR_LIGHT_GREY;
	terminal.bg_default = VGA_COLOR_BLACK;
	terminal.color = vga_entry_color(terminal.fg_default, terminal.bg_default);
	terminal.buffer = (uint16_t*) 0xB8000;
	terminal_clear();
}

void terminal_clear(void)
{
	for (size_t x = 0; x < VGA_WIDTH; x++) {
		const size_t index = x;
		terminal.buffer[index] = vga_entry(' ', vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLUE));
	}
	for (size_t y = 1; y < VGA_HEIGHT - 1; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal.buffer[index] = vga_entry(' ', terminal.color);
		}
	}
	for (size_t x = 0; x < VGA_WIDTH; x++) {
		const size_t index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
		terminal.buffer[index] = vga_entry(' ', vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLUE));
	}
	terminal.row = 2;
	terminal.column = 2;
}

void terminal_special(char c)
{
	if (c == '\b')
	{
		if (terminal.column > 2)
			terminal.column--;
		terminal_putentryat(' ', terminal.color, terminal.column, terminal.row);
	}
	else if (c == '\n')
		terminal.column = VGA_WIDTH - 3;
	else if (c == '\t')
	{
		terminal.column += 4;
		if (terminal.column >= VGA_WIDTH - 3)
			terminal.column = VGA_WIDTH - 3;
	}
	else if (c == '\r')
		terminal.column = 2;
	else if (c == '\f')
		terminal_clear();
	else if (c == '\v' && ++terminal.row >= VGA_HEIGHT - 2)
		terminal.row = 2;
	else if (c == '\a' && terminal.color != vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK))
		terminal.color = vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK), terminal.column--;
	else if (c == '\a' && terminal.color == vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK))
		terminal.color = vga_entry_color(terminal.fg_default, terminal.bg_default), terminal.column--;
}

void terminal_putchar(char c)
{
	if (c == '\b' || c == '\n' || c == '\t' || c == '\r' || c == '\f' || c == '\v' || c == '\a')
		terminal_special(c);
	else
		terminal_putentryat(c, terminal.color, terminal.column, terminal.row);
	if (++terminal.column == VGA_WIDTH - 2) {
		terminal.column = 2;
		if (++terminal.row == VGA_HEIGHT - 2)
			terminal.row = 2;
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
