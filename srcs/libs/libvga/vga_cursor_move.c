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
#include <hardware/vga/vga.h> /*
# define VGA_WIDTH
#        */
/* **************************** [^] INCLUDES [^] **************************** */

void
	vga_cursor_move(__volatile__ uint16_t *pos)
{
	outb(VGA_CRTC_COMMAND_PORT, VGA_CRTC_REG_CURSOR_LOC_HIGH);
	outb(VGA_CRTC_DATA_PORT, (uint8_t)(((pos - VGA_BUFFER) >> 8) & 0xFF));

	outb(VGA_CRTC_COMMAND_PORT, VGA_CRTC_REG_CURSOR_LOC_LOW);
	outb(VGA_CRTC_DATA_PORT, (uint8_t)((pos - VGA_BUFFER) & 0xFF));
}
