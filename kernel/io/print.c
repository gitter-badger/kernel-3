#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

/* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

static const uint32_t VGA_WIDTH = 80;
static const uint32_t VGA_HEIGHT = 25;

uint32_t terminal_row;
uint32_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void print_init()
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (uint32_t y = 0; y < VGA_HEIGHT; y++) {
		for (uint32_t x = 0; x < VGA_WIDTH; x++) {
			const uint32_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, uint32_t x, uint32_t y)
{
	const uint32_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void putc(char c)
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

void puts(const char *s)
{
	while (*s) {
		putc(*s);
		++s;
	}
}

void uitoa(uint32_t num, uint32_t base, bool uc, char * bf)
{
	int n=0;
	uint32_t d = 1;
	uint32_t a = num;
	while (a >= base) {
		d *= base;
		a = num/d;
	}

	while (d != 0) {
		uint32_t dgt = num / d;
		num = num % d;
		d /= base;
		if (n || dgt > 0 || d == 0) {
			*bf = dgt+(dgt < 10 ? '0' : (uc ? 'A' : 'a') - 10);
			++bf;
			++n;
		}
	}

	*bf = '\0';
}

void itoa (int num, unsigned int base, char * bf)
{
	if (num<0) {
		num=-num;
		*bf++ = '-';
	}

	uitoa(num, base, false, bf);
}

/**
 * Super simple printf for the kernel
 */
void kprintf(const char *fmt, ...)
{
	va_list va;
	va_start(va,fmt);

	char c;
	char buffer[32];
	while ((c = *fmt)) {

		if (c != '%') {
			putc(c);
		} else {
			++fmt;
			c = *fmt;
			switch (c) {
				case 'x':
				case 'X':
					{
						uitoa(va_arg(va, uint32_t), 16, c == 'X', buffer);
						puts(buffer);
						break;
					}
				case 's':
					{
						const char *s = va_arg(va, char*);
						puts(s);
						break;
					}
				case 'd':
					{
						itoa(va_arg(va, int32_t), 10, buffer);
						puts(buffer);
						break;
					}
				case 'u':
					{
						uitoa(va_arg(va, uint32_t), 10, false, buffer);
						puts(buffer);
						break;
					}
			}
		}

		++fmt;
	}


	va_end(va);
}
