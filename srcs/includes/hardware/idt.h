#ifndef IDT_H
# define IDT_H 202507

/* *************************** [v] CONSTANTS [v] **************************** */

# define IDT_SIZE 256
# define IDT_OFFSET_LOW_MASK 0x0000FFFF
# define IDT_SELECTOR 0x10
# define IDT_ZERO 0
# define IDT_TYPE_ATTR 0x8E
# define IDT_OFFSET_HIGH_MASK 0xFFFF0000
# define OFFSET_LOW_MASK(offset) ((offset) & IDT_OFFSET_LOW_MASK)
# define OFFSET_HIGH_MASK(offset) (((offset) & IDT_OFFSET_HIGH_MASK) >> 16)

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
/* **************************** [^] INCLUDES [^] **************************** */
/* **************************** [v] STRUCTS [v] ***************************** */

struct IDTEntry
{
	uint16_t	offset_low;
	uint16_t	selector;
	uint8_t		zero;
	uint8_t		type_attr;
	uint16_t	offset_high;
} __attribute__((packed));

/* **************************** [^] STRUCTS [^] ***************************** */
/* **************************** [v] TYPEDEFS [v] **************************** */

typedef unsigned long irq_flags_t;

/* **************************** [^] TYPEDEFS [^] **************************** */
/* **************************** [v] GLOBALS [v] ***************************** */

extern struct IDTEntry	IDT[IDT_SIZE];

/* **************************** [^] GLOBALS [^] ***************************** */
/* *************************** [v] PROTOTYPES [v] *************************** */

static INLINE void			cli(void);
static INLINE void			sti(void);
static INLINE int			irq_enabled(void);
static INLINE irq_flags_t	save_irqdisable(void);
static INLINE void			irqrestore(irq_flags_t flags);
static INLINE void			idt_set(uint8_t, void (*)(void));
static INLINE void			lidt(void);

/* *************************** [^] PROTOTYPES [^] *************************** */
/* *************************** [v] FUNCTIONS [v] **************************** */

static INLINE void
	cli(void)
{
	__asm__ __volatile__
	(
		"cli"
	);
}

static INLINE void
	sti(void)
{
	__asm__ __volatile__
	(
		"sti"
	);
}

static INLINE int
	irq_enabled(void)
{
	irq_flags_t	flags;

	__asm__ __volatile__
	(
		"pushf"	"\n\t"
		"pop %0"
		: "=g"(flags)
	);
	return (flags & (1 << 9));
}

static INLINE irq_flags_t
	save_irqdisable(void)
{
	irq_flags_t	flags;

	__asm__ __volatile__
	(
		"pushf"   "\n\t"
		"cli"     "\n\t"
		"pop %0"
		: "=r"(flags)
		:
		: "memory"
	);
	return (flags);
}

static INLINE void
	irqrestore(irq_flags_t flags)
{
	__asm__ __volatile__
	(
		"push %0" "\n\t"
		"popf"
		:
		: "rm"(flags)
		: "memory", "cc"
	);
}

static INLINE void
	idt_set(uint8_t vector, void (*handler)(void))
{
	IDT[vector] = (struct IDTEntry)
	{
		.offset_low = (uint16_t)OFFSET_LOW_MASK((uint32_t)(uintptr_t)handler),
		.selector = IDT_SELECTOR,
		.zero = IDT_ZERO,
		.type_attr = IDT_TYPE_ATTR,
		.offset_high = (uint16_t)OFFSET_HIGH_MASK((uint32_t)(uintptr_t)handler)
	};
}

static INLINE void
	lidt(void)
{
	struct {
		uint16_t	length;
		void		*base;
	} __attribute__((packed)) IDTR = {
		.length = (sizeof(struct IDTEntry) * IDT_SIZE) - 1,
		.base = &IDT
	};
	__asm__ __volatile__ ("lidt %0" : : "m"(IDTR));
}

/* *************************** [^] FUNCTIONS [^] **************************** */

#endif /* IDT_H */
