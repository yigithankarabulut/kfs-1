/* **************************** [v] INCLUDES [v] **************************** */
#include <stdint.h> /*
#typedef uint8_t;
#        */
#include <hardware/io.h> /*
#   void outb(uint16_t, uint8_t);
#uint8_t inb(uint16_t);
#        */
#include <hardware/vga/crtc.h> /*
# define VGA_CRTC_COMMAND_PORT
# define VGA_CRTC_DATA_PORT
# define VGA_CRTC_REG_CURSOR_START
# define VGA_CRTC_REG_CURSOR_END
#        */
/* **************************** [^] INCLUDES [^] **************************** */

void
	vga_cursor_enable(uint8_t start, uint8_t end)
{
	outb(VGA_CRTC_COMMAND_PORT, VGA_CRTC_REG_CURSOR_START);
	outb(VGA_CRTC_DATA_PORT, (inb(VGA_CRTC_DATA_PORT) & 0xC0) | start);

	outb(VGA_CRTC_COMMAND_PORT, VGA_CRTC_REG_CURSOR_END);
	outb(VGA_CRTC_DATA_PORT, (inb(VGA_CRTC_DATA_PORT) & 0xE0) | end);
}
