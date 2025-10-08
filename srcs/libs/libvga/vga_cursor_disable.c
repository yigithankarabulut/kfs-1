/* **************************** [v] INCLUDES [v] **************************** */
#include <hardware/io.h> /*
#   void outb(uint16_t, uint8_t);
#        */
#include <hardware/vga/crtc.h> /*
# define VGA_CRTC_COMMAND_PORT
# define VGA_CRTC_DATA_PORT
# define VGA_CRTC_REG_CURSOR_START
#        */
/* **************************** [^] INCLUDES [^] **************************** */

void
	vga_cursor_disable(void)
{
	outb(VGA_CRTC_COMMAND_PORT, VGA_CRTC_REG_CURSOR_START);
	outb(VGA_CRTC_DATA_PORT, 0x20);
}
