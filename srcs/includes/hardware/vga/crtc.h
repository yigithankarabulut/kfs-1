#ifndef CRTC_H
# define CRTC_H 202507

/* *************************** [v] CONSTANTS [v] **************************** */

// Cathode Ray Tube Controller (CRTC) registers for VGA

# define VGA_CRTC_COMMAND_PORT 0x3D4
# define VGA_CRTC_DATA_PORT  0x3D5

// Register Indexes

# define VGA_CRTC_REG_HORIZONTAL_TOTAL            0x00
# define VGA_CRTC_REG_HORIZONTAL_DISPLAY_END      0x01
# define VGA_CRTC_REG_START_HORIZONTAL_BLANK      0x02
# define VGA_CRTC_REG_END_HORIZONTAL_BLANK        0x03
# define VGA_CRTC_REG_START_HORIZONTAL_RETRACE    0x04
# define VGA_CRTC_REG_END_HORIZONTAL_RETRACE      0x05
# define VGA_CRTC_REG_VERTICAL_TOTAL              0x06
# define VGA_CRTC_REG_OVERFLOW                    0x07
# define VGA_CRTC_REG_PRESET_ROW_SCAN             0x08
# define VGA_CRTC_REG_MAX_SCAN_LINE               0x09
# define VGA_CRTC_REG_CURSOR_START                0x0A
# define VGA_CRTC_REG_CURSOR_END                  0x0B
# define VGA_CRTC_REG_START_ADDR_HIGH             0x0C
# define VGA_CRTC_REG_START_ADDR_LOW              0x0D
# define VGA_CRTC_REG_CURSOR_LOC_HIGH             0x0E
# define VGA_CRTC_REG_CURSOR_LOC_LOW              0x0F
# define VGA_CRTC_REG_VERTICAL_RETRACE_START      0x10
# define VGA_CRTC_REG_VERTICAL_RETRACE_END        0x11
# define VGA_CRTC_REG_VERTICAL_DISPLAY_END        0x12
# define VGA_CRTC_REG_OFFSET                      0x13
# define VGA_CRTC_REG_UNDERLINE_LOC               0x14
# define VGA_CRTC_REG_START_VERTICAL_BLANK        0x15
# define VGA_CRTC_REG_END_VERTICAL_BLANK          0x16
# define VGA_CRTC_REG_MODE_CONTROL                0x17
# define VGA_CRTC_REG_LINE_COMPARE                0x18

/* *************************** [^] CONSTANTS [^] **************************** */

#endif /* CRTC_H */