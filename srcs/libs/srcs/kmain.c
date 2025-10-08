#include <hardware/vga/crtc.h>
#include <libft.h>
#include <hardware/vga/vga.h>
#include <hardware/pic.h>
#include <hardware/idt.h>
#include <keyboard.h>

#define PROMPT "42$>"
#define PROMPT_LENGTH 4
# define TTY_COUNT 2

struct IDTEntry IDT[IDT_SIZE] = {0};

uint16_t	tty_idx = 0;
__volatile__ uint16_t	*prompt = VGA_BUFFER;
__volatile__ uint16_t	tty[TTY_COUNT][VGA_SIZE];
__volatile__ uint16_t	*cursor[TTY_COUNT];
__volatile__ uint8_t	cursor_col[TTY_COUNT];
__volatile__ uint8_t	cursor_row[TTY_COUNT];
uint8_t					color[TTY_COUNT] = {VGA_COLOR_LIGHT_GRAY, VGA_COLOR_GREEN};

extern void	keyboard_interrupt_handler(void);

void scroll_screen(void)
{
	for (uint8_t row = 0; row < VGA_HEIGHT - 1; row++)
	{
		for (uint8_t col = 0; col < VGA_WIDTH; col++)
		{
			tty[tty_idx][row * VGA_WIDTH + col] = tty[tty_idx][(row + 1) * VGA_WIDTH + col];
		}
	}
	for (uint8_t col = 0; col < VGA_WIDTH; col++)
	{
		tty[tty_idx][(VGA_HEIGHT - 1) * VGA_WIDTH + col] = VGA_ENTRY(' ', VGA_COLOR_WHITE);
	}
	prompt -= VGA_WIDTH;
}

size_t
	write(const char* buf, size_t count)
{
	size_t	idx;

	for (idx = 0; idx < count; idx++)
	{
		char c = buf[idx];

		if (c == '\n')
		{
			cursor_col[tty_idx] = 0;
			cursor_row[tty_idx]++;
			cursor[tty_idx] = VGA_BUFFER + (cursor_row[tty_idx] * VGA_WIDTH);
			prompt = cursor[tty_idx];
		}
		else if (c == '\b')
		{
			if (cursor[tty_idx] > prompt + PROMPT_LENGTH)
			{
				cursor_col[tty_idx]--;
				cursor[tty_idx]--;
				vga_putchar(tty[tty_idx], ' ', color[tty_idx], VGA_COLOR_BLACK, cursor_col[tty_idx], cursor_row[tty_idx]);
			}
		}
		else
		{
			if (cursor_col[tty_idx] < VGA_WIDTH-1)
			{
				vga_putchar(tty[tty_idx], c, color[tty_idx], VGA_COLOR_BLACK, cursor_col[tty_idx], cursor_row[tty_idx]);
				cursor_col[tty_idx]++;
				cursor[tty_idx]++;
			}
		}
		if (cursor_row[tty_idx] >= VGA_HEIGHT)
		{
			scroll_screen();
			cursor_row[tty_idx] = VGA_HEIGHT - 1;
			cursor[tty_idx] = VGA_BUFFER + (cursor_row[tty_idx] * VGA_WIDTH);
		}
		vga_cursor_move(cursor[tty_idx]);
		ft_memcpy((void *)VGA_BUFFER, (void *)tty[tty_idx], VGA_SIZE * sizeof(uint16_t));
	}
	return (idx);
}

void
	init_screen(void)
{
	for (int idx = 0; idx < TTY_COUNT; idx++)
	{
		vga_memset(tty[idx], VGA_ENTRY(' ', VGA_COLOR(color[idx], VGA_COLOR_BLACK)), VGA_BUFFER_SIZE);
	}
	for (int idx = 0; idx < TTY_COUNT; idx++)
	{
		cursor[idx] = VGA_BUFFER;
		cursor_col[idx] = 0;
		cursor_row[idx] = 0;
	}
	ft_memcpy((void *)VGA_BUFFER, (void *)tty[tty_idx], VGA_SIZE * sizeof(uint16_t));
	vga_cursor_move(cursor[tty_idx]);
	vga_cursor_enable(0, 15);
	for (int idx = TTY_COUNT-1; idx >= 0; idx--)
	{
		tty_idx = idx;
		write(PROMPT, PROMPT_LENGTH);
	}
}

void
	write_char(char ascii_char)
{
	if (ascii_char == '\n')
	{
		write(&ascii_char, 1);
		write(PROMPT, PROMPT_LENGTH);
	}
	else if (ascii_char)
	{
		write(&ascii_char, 1);
	}
}

void
	handle_char(uint8_t code)
{
	int caps = kbd_map[CAPS_LOCK][0];
	int shift = kbd_map[LEFT_SHIFT][0] || kbd_map[RIGHT_SHIFT][0];
	int idx = 0;
	
	if (shift == caps)
		idx = kbd_map[code][2] == 2;
	else if (shift)
		idx = 1;
	else if (caps)
		idx = kbd_map[code][2] == 1;
	write_char(kbd_map[code][idx]);
}

void
	keyboard_handler(void)
{
	uint8_t	code;

	PIC_sendEOI(IRQ1);
	while (inb(PS2_STATUS_PORT) & PS2_STATUS_OUTPUT_BUFFER_FULL)
	{
		code = inb(PS2_DATA_PORT);
		switch (code)
		{
			case CAPS_LOCK:
				kbd_map[code][0] = !kbd_map[code][0];
				break;
			case 0X3B:
				tty_idx = 0;
				ft_memcpy((void *)VGA_BUFFER, (void *)tty[tty_idx], VGA_SIZE * sizeof(uint16_t));
				vga_cursor_move(cursor[tty_idx]);
				break;
			case 0x3C:
				tty_idx = 1;
				ft_memcpy((void *)VGA_BUFFER, (void *)tty[tty_idx], VGA_SIZE * sizeof(uint16_t));
				vga_cursor_move(cursor[tty_idx]);
				break;
			case NUM_LOCK:
				kbd_map[code][0] = !kbd_map[code][0];
				break;
			default:
				switch (code)
				{
					case 0x00 ... 0x7F:
						if (!kbd_map[code][2])
						{
							kbd_map[code][0] = 1;
							break;
						}
						handle_char(code);
						break;
					case 0x80 ... 0xFF:
						code &= 0x7F;
						switch (code)
						{
							case ESC: outw(0x604, 0x2000); break;
							case CAPS_LOCK: break;
							case NUM_LOCK: break;
							default:
								if (!kbd_map[code][2])
									kbd_map[code][0] = 0;
								break;
						}
						break;
					default: break;
				}
				break;
		}
	}
}

void
	init_idt(void)
{
	PIC_remap(PIC1_VECTOR_OFFSET, PIC2_VECTOR_OFFSET);
	ft_memset(&IDT, 0, sizeof(IDT));
	idt_set(IRQ1_VECTOR_OFFSET, keyboard_interrupt_handler);
	lidt();
	IRQ_clear_mask(IRQ1);
	sti();
}

void
	kmain(void)
{
	init_idt();
	init_screen();
}
