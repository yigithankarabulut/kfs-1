#ifndef VGA_H
# define VGA_H 202507

/* *************************** [v] CONSTANTS [v] **************************** */

// VGA memory base address
# define VGA_ADDRESS 0xB8000

// Utility macros for VGA text mode
# define VGA_COLS 80
# define VGA_ROWS 25
# define VGA_WIDTH 80
# define VGA_HEIGHT 25
# define VGA_BUFFER ((__volatile__ uint16_t *)VGA_ADDRESS)
# define VGA_SIZE (VGA_WIDTH * VGA_HEIGHT)
# define VGA_LINE_SIZE (VGA_WIDTH << (sizeof(uint16_t) >> 1))
# define VGA_BUFFER_SIZE (VGA_SIZE << (sizeof(uint16_t) >> 1))
# define VGA_COLOR(fg, bg) ((bg << 4) | (fg & 0x0F))
# define VGA_ENTRY(c, color) ((uint16_t)(color << 8 | c))

/* *************************** [^] CONSTANTS [^] **************************** */
/* **************************** [v] INCLUDES [v] **************************** */
# include <stdint.h> /*
# typedef uint8_t;
# typedef uint16_t;
#         */
# include <stddef.h> /*
# typedef size_t;
#         */
# include <INLINE.h> /*
#  define INLINE
#         */
/* **************************** [^] INCLUDES [^] **************************** */
/* ***************************** [v] ENUMS [v] ****************************** */
enum vga_color
{
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GRAY = 7,
	VGA_COLOR_DARK_GRAY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_YELLOW = 14,
	VGA_COLOR_WHITE = 15
};
/* ***************************** [^] ENUMS [^] ****************************** */
/* *************************** [v] PROTOTYPES [v] *************************** */

extern void	vga_memset(volatile uint16_t *, uint16_t, size_t);
extern void	vga_cursor_disable(void);
extern void	vga_cursor_enable(uint8_t, uint8_t);
extern void	vga_cursor_move(__volatile__ uint16_t *);

/* *************************** [^] PROTOTYPES [^] *************************** */
/* *************************** [v] FUNCTIONS [v] **************************** */

static INLINE void
	vga_putchar(__volatile__ uint16_t *stty, uint8_t c, uint8_t fg, uint8_t bg, uint8_t x, uint8_t y)
{
	uint16_t pos = y * VGA_WIDTH + x;
	stty[pos] = VGA_ENTRY(c, VGA_COLOR(fg, bg));

}

/* *************************** [^] FUNCTIONS [^] **************************** */

#endif /* VGA_H */
