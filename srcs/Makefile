NAME		= norx
NAME_BIN	= $(NAME).bin
NAME_ISO	= $(NAME).iso

RM			= rm -rf

AS			= nasm
ASFLAGS		= -f elf32

CC			= clang
CFLAGS		= -Wall -Wextra -Werror
CFLAGS		+= -O3
CFLAGS		+= -I./includes
CFLAGS		+= -m32 -ffreestanding
CFLAGS		+= -fno-builtin -fno-exceptions
CFLAGS		+= -fno-stack-protector -nostdlib -nodefaultlibs

LD			= ld
LDFLAGS		= -m elf_i386 -T linker.ld

ASM_SRCS	=	libs/srcs/boot.s
C_SRCS		=	\
				libs/libvga/vga_cursor_disable.c \
				libs/libvga/vga_cursor_enable.c \
				libs/libvga/vga_cursor_move.c \
				libs/libvga/vga_memset.c \
				libs/libft/ft_memset.c \
				libs/libft/ft_memcpy.c \
				libs/srcs/kmain.c

ASM_OBJS	= $(ASM_SRCS:.s=.o)
C_OBJS		= $(C_SRCS:.c=.o)
OBJS		= $(ASM_OBJS) $(C_OBJS)

GRUB_MKRESCUE = grub-mkrescue
ISO_DIR		= iso
BOOT_DIR	= $(ISO_DIR)/boot

build: check all

all: $(NAME_BIN)

$(NAME_BIN): $(OBJS)
	$(LD) $(LDFLAGS) -o $(BOOT_DIR)/$(NAME_BIN) $(OBJS)
	$(GRUB_MKRESCUE) -o $(NAME_ISO) $(ISO_DIR)

$(ASM_OBJS): %.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

$(C_OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

c: clean
clean:
	$(RM) $(OBJS)

f: fclean
fclean: clean
	$(RM) $(BOOT_DIR)/$(NAME_BIN)
	$(RM) $(NAME_ISO)

re: fclean all

check:
	@command -v $(AS) >/dev/null 2>&1 || { echo >&2 "Assembler $(AS) is required but not installed. Aborting."; exit 1; }
	@command -v $(CC) >/dev/null 2>&1 || { echo >&2 "Compiler $(CC) is required but not installed. Aborting."; exit 1; }
	@command -v $(LD) >/dev/null 2>&1 || { echo >&2 "Linker $(LD) is required but not installed. Aborting."; exit 1; }
	@command -v $(GRUB_MKRESCUE) >/dev/null 2>&1 || { echo >&2 "Grub mkrescue tool is required but not installed. Aborting."; exit 1; }
