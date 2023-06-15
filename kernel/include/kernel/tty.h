#ifndef KERNEL_TTY_H
# define KERNEL_TTY_H

# include <stddef.h>
# include <stdint.h>

/* Hardware text mode color constants. */
enum vga_color {
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

typedef struct s_terminal {
	size_t		row;
	size_t		column;
	uint8_t		color;
	uint16_t*	buffer;
	uint8_t		fg_default;
	uint8_t		bg_default;
}	t_terminal;

extern t_terminal	terminal;

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

void		terminal_initialize(void);
void		terminal_clear(void);
void		terminal_putchar(char c);
void		terminal_write(const char* data, size_t size, uint8_t color);
void		terminal_writestring(const char* data, uint8_t color);
void		terminal_setcolor(uint8_t color);
void		terminal_putentryat(char c, uint8_t color, size_t x, size_t y);

#endif