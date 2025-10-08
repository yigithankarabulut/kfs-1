; ============================================================
;                      Multiboot Header
; ============================================================
; This section is required for multiboot-compliant bootloaders
; such as GRUB to properly load and start your kernel.
;
; The Multiboot header begins with a fixed magic number,
; specifies the kernel's requested features (FLAGS), and
; includes a CHECKSUM so that the sum of magic + flags + checksum = 0.
;
; All fields must be defined sequentially as 32-bit values (dd).
;
; You can customize the values easily by modifying the %define
; constants below.
;
; ------------------------------------------------------------
; Field order and descriptions:
; ------------------------------------------------------------
; 1) MULTIBOOT_HEADER_MAGIC    : Identifies the kernel as multiboot compliant.
; 2) MULTIBOOT_HEADER_FLAGS    : Flags specifying kernel requirements.
;    - BIT 0 (0x1) : Align modules on page boundaries.
;    - BIT 1 (0x2) : Request memory map information.
;    - BIT 2 (0x4) : Request video mode (framebuffer).
; 3) MULTIBOOT_HEADER_CHECKSUM : Checksum to validate the header.
; 4) HEADER_ADDR              : Optional, usually zero.
; 5) LOAD_ADDR                : Optional, usually zero.
; 6) LOAD_END_ADDR            : Optional, usually zero.
; 7) BSS_END_ADDR             : Optional, usually zero.
; 8) ENTRY_ADDR               : Optional, usually zero.
; 9) MODE_TYPE                : Video mode type (0 = text, 1 = graphics).
; 10) SCREEN_WIDTH            : Screen width in pixels (graphics mode).
; 11) SCREEN_HEIGHT           : Screen height in pixels (graphics mode).
; 12) COLOR_DEPTH             : Bits per pixel (color depth).
;
; ------------------------------------------------------------
; Example flag values:
; ------------------------------------------------------------
; %define MULTIBOOT_FLAG_ALIGN        0x00000001  ; Align modules on page boundaries
; %define MULTIBOOT_FLAG_MEMINFO      0x00000002  ; Request memory map
; %define MULTIBOOT_FLAG_VIDEO_MODE   0x00000004  ; Request video mode
;
; ------------------------------------------------------------
; Video mode types:
; ------------------------------------------------------------
; %define MODE_TYPE_TEXT      0
; %define MODE_TYPE_GRAPHICS  1
;
; ------------------------------------------------------------
; Screen resolution settings:
; ------------------------------------------------------------
; %define SCREEN_WIDTH        1024
; %define SCREEN_HEIGHT       768
; %define COLOR_DEPTH         32
; ============================================================

%define MULTIBOOT_HEADER_MAGIC      0x1BADB002

%define MULTIBOOT_FLAG_ALIGN        0x00000001
%define MULTIBOOT_FLAG_MEMINFO      0x00000002
%define MULTIBOOT_FLAG_VIDEO_MODE   0x00000004

;MULTIBOOT_HEADER_FLAGS = (MULTIBOOT_FLAG_ALIGN | MULTIBOOT_FLAG_MEMINFO)
%define MULTIBOOT_HEADER_FLAGS      0x00000003
%define MULTIBOOT_HEADER_CHECKSUM   -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

%define HEADER_ADDR         0x0
%define LOAD_ADDR           0x0
%define LOAD_END_ADDR       0x0
%define BSS_END_ADDR        0x0
%define ENTRY_ADDR          0x0

%define MODE_TYPE_TEXT      0
%define MODE_TYPE_GRAPHICS  1

%define SCREEN_WIDTH        1024
%define SCREEN_HEIGHT       768
%define COLOR_DEPTH         32

SECTION .multiboot
	align 4
	dd MULTIBOOT_HEADER_MAGIC
	dd MULTIBOOT_HEADER_FLAGS
	dd MULTIBOOT_HEADER_CHECKSUM
	dd HEADER_ADDR
	dd LOAD_ADDR
	dd LOAD_END_ADDR
	dd BSS_END_ADDR
	dd ENTRY_ADDR
	dd MODE_TYPE_TEXT
	dd SCREEN_WIDTH
	dd SCREEN_HEIGHT
	dd COLOR_DEPTH

SECTION .text
	GLOBAL start
	GLOBAL keyboard_interrupt_handler
	EXTERN keyboard_handler
	EXTERN kmain

keyboard_interrupt_handler:
	PUSHAD
	CALL keyboard_handler
	POPAD
	IRETD

start:
	CLI

	CALL kmain

.HEALT:
	HLT
	JMP .HEALT
