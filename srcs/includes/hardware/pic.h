#ifndef PIC_H
# define PIC_H 202507

/* *************************** [v] CONSTANTS [v] **************************** */

# define PIC1 0x20
# define PIC2 0xA0
# define PIC1_COMMAND_PORT PIC1
# define PIC1_DATA_PORT    (PIC1 + 1)
# define PIC2_COMMAND_PORT PIC2
# define PIC2_DATA_PORT    (PIC2 + 1)

# define PIC1_VECTOR_OFFSET 0x20
# define PIC2_VECTOR_OFFSET 0x28
# define PIC_EOI 0x20

# define IRQ0_VECTOR_OFFSET  (PIC1_VECTOR_OFFSET + 0)
# define IRQ1_VECTOR_OFFSET  (PIC1_VECTOR_OFFSET + 1)
# define IRQ2_VECTOR_OFFSET  (PIC1_VECTOR_OFFSET + 2)
# define IRQ3_VECTOR_OFFSET  (PIC1_VECTOR_OFFSET + 3)
# define IRQ4_VECTOR_OFFSET  (PIC1_VECTOR_OFFSET + 4)
# define IRQ5_VECTOR_OFFSET  (PIC1_VECTOR_OFFSET + 5)
# define IRQ6_VECTOR_OFFSET  (PIC1_VECTOR_OFFSET + 6)
# define IRQ7_VECTOR_OFFSET  (PIC1_VECTOR_OFFSET + 7)

# define IRQ8_VECTOR_OFFSET  (PIC2_VECTOR_OFFSET + 0)
# define IRQ9_VECTOR_OFFSET  (PIC2_VECTOR_OFFSET + 1)
# define IRQ10_VECTOR_OFFSET (PIC2_VECTOR_OFFSET + 2)
# define IRQ11_VECTOR_OFFSET (PIC2_VECTOR_OFFSET + 3)
# define IRQ12_VECTOR_OFFSET (PIC2_VECTOR_OFFSET + 4)
# define IRQ13_VECTOR_OFFSET (PIC2_VECTOR_OFFSET + 5)
# define IRQ14_VECTOR_OFFSET (PIC2_VECTOR_OFFSET + 6)
# define IRQ15_VECTOR_OFFSET (PIC2_VECTOR_OFFSET + 7)

# define IRQ0   0
# define IRQ1   1
# define IRQ2   2
# define IRQ3   3
# define IRQ4   4
# define IRQ5   5
# define IRQ6   6
# define IRQ7   7
# define IRQ8   8
# define IRQ9   9
# define IRQ10  10
# define IRQ11  11
# define IRQ12  12
# define IRQ13  13
# define IRQ14  14
# define IRQ15  15

# define ICW1_ICW4 0x01
# define ICW1_SINGLE 0x02
# define ICW1_INTERVAL4 0x04
# define ICW1_LEVEL 0x08
# define ICW1_INIT 0x10

# define ICW2_PIC1_VECTOR PIC1_VECTOR_OFFSET
# define ICW2_PIC2_VECTOR PIC2_VECTOR_OFFSET

# define CASCADE_IRQ 2

# define ICW3_PIC1_SLAVE 1 << CASCADE_IRQ
# define ICW3_PIC2_MASTER CASCADE_IRQ

# define ICW4_8086 0x01
# define ICW4_AUTO 0x02
# define ICW4_BUF_SLAVE 0x08
# define ICW4_BUF_MASTER 0x0C
# define ICW4_SFNM 0x10

/* *************************** [^] CONSTANTS [^] **************************** */
/* **************************** [v] INCLUDES [v] **************************** */
# include <stdint.h> /*
# typedef uint8_t;
# typedef uint16_t;
# typedef uint32_t;
#         */
# include <INLINE.h> /*
#  define INLINE
#         */
# include <hardware/io.h> /*
# uint8_t inb(uint16_t);
#    void outb(uint16_t, uint8_t);
#    void io_wait(void);
#         */
/* **************************** [^] INCLUDES [^] **************************** */
/* *************************** [v] PROTOTYPES [v] *************************** */

static INLINE void	PIC_remap(uint8_t, uint8_t);
static INLINE void	PIC_sendEOI(uint8_t);
static INLINE void	PIC_disable(void);
static INLINE void	IRQ_set_mask(uint8_t);
static INLINE void	IRQ_clear_mask(uint8_t);

/* *************************** [^] PROTOTYPES [^] *************************** */
/* *************************** [v] FUNCTIONS [v] **************************** */

static INLINE void
	PIC_remap(uint8_t offset1, uint8_t offset2)
{
	outb(PIC1_COMMAND_PORT, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC2_COMMAND_PORT, ICW1_INIT | ICW1_ICW4);
	io_wait();

	outb(PIC1_DATA_PORT, offset1);
	io_wait();
	outb(PIC2_DATA_PORT, offset2);
	io_wait();

	outb(PIC1_DATA_PORT, ICW3_PIC1_SLAVE);
	io_wait();
	outb(PIC2_DATA_PORT, ICW3_PIC2_MASTER);
	io_wait();

	outb(PIC1_DATA_PORT, ICW4_8086);
	io_wait();
	outb(PIC2_DATA_PORT, ICW4_8086);
	io_wait();

	outb(PIC1_DATA_PORT, 0xFF);
	outb(PIC2_DATA_PORT, 0xFF);
}

static INLINE void
	PIC_sendEOI(uint8_t irq)
{
	switch (irq)
	{
		case 0 ... 7:
			outb(PIC1_COMMAND_PORT, PIC_EOI);
			break;
		case 8 ... 15:
			outb(PIC2_COMMAND_PORT, PIC_EOI);
			break;
		default:
			break;
	}
}

static INLINE void
	PIC_disable(void)
{
	outb(PIC1_DATA_PORT, 0xFF);
	outb(PIC2_DATA_PORT, 0xFF);
}

static INLINE void
	IRQ_set_mask(uint8_t IRQline)
{
	switch (IRQline)
	{
		case 0 ... 7:
			outb(PIC1_DATA_PORT, inb(PIC1_DATA_PORT) | (1 << IRQline));
			break;
		case 8 ... 15:
			outb(PIC2_DATA_PORT, inb(PIC2_DATA_PORT) | (1 << (IRQline - 8)));
			break;
		default:
			break;
	}
}

static INLINE void
	IRQ_clear_mask(uint8_t IRQline)
{
	switch (IRQline)
	{
		case 0 ... 7:
			outb(PIC1_DATA_PORT, inb(PIC1_DATA_PORT) & ~(1 << IRQline));
			break;
		case 8 ... 15:
			outb(PIC2_DATA_PORT, inb(PIC2_DATA_PORT) & ~(1 << (IRQline - 8)));
			break;
		default:
			break;
	}
}

/* *************************** [^] FUNCTIONS [^] **************************** */

#endif /* PIC_H */