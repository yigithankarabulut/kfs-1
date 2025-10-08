#ifndef IO_H
# define IO_H 202507

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
/* *************************** [v] PROTOTYPES [v] *************************** */

static INLINE uint8_t	inb(uint16_t);
static INLINE uint16_t	inw(uint16_t);
static INLINE uint32_t  inl(uint16_t);
static INLINE void		insb(uint16_t, void *, uint32_t);
static INLINE void		insw(uint16_t, void *, uint32_t);
static INLINE void		insl(uint16_t, void *, uint32_t);
static INLINE void		outb(uint16_t, uint8_t);
static INLINE void		outw(uint16_t, uint16_t);
static INLINE void		outl(uint16_t, uint32_t);
static INLINE void		outsb(uint16_t, const void *, uint32_t);
static INLINE void		outsw(uint16_t, const void *, uint32_t);
static INLINE void		outsl(uint16_t, const void *, uint32_t);
static INLINE void		io_wait(void);

/* *************************** [^] PROTOTYPES [^] *************************** */
/* *************************** [v] FUNCTIONS [v] **************************** */

static INLINE uint8_t
	inb(uint16_t port)
{
	uint8_t ret;
	__asm__ __volatile__
	(
		"inb %1, %0"
		: "=a"(ret)
		: "dN"(port)
		: "memory"
	);
	return (ret);
}

static INLINE uint16_t
	inw(uint16_t port)
{
	uint16_t	ret;

	__asm__ __volatile__
	(
		"inw %1, %0"
		: "=a"(ret)
		: "dN"(port)
		: "memory"
	);
	return (ret);
}

static INLINE uint32_t
	inl(uint16_t port)
{
	uint32_t	ret;

	__asm__ __volatile__
	(
		"inl %1, %0"
		: "=a"(ret)
		: "dN"(port)
		: "memory"
	);
	return (ret);
}

static INLINE void
	insb(uint16_t port, void *addr, uint32_t count)
{
	__asm__ __volatile__
	(
		"rep insb"
		: "+D"(addr), "+c"(count)
		: "d"(port)
		: "memory"
	);
}

static INLINE void
	insw(uint16_t port, void *addr, uint32_t count)
{
	__asm__ __volatile__
	(
		"rep insw"
		: "+D"(addr), "+c"(count)
		: "d"(port)
		: "memory"
	);
}

static INLINE void
	insl(uint16_t port, void *addr, uint32_t count)
{
	__asm__ __volatile__
	(
		"rep insl"
		: "+D"(addr), "+c"(count)
		: "d"(port)
		: "memory"
	);
}

static INLINE void
	outb(uint16_t port, uint8_t value)
{
	__asm__ __volatile__
	(
		"outb %0, %1"
		:
		: "a"(value), "dN"(port)
		: "memory"
	);
}

static INLINE void
	outw(uint16_t port, uint16_t value)
{
	__asm__ __volatile__
	(
		"outw %0, %1"
		:
		: "a"(value), "dN"(port)
		: "memory"
	);
}

static INLINE void
	outl(uint16_t port, uint32_t value)
{
	__asm__ __volatile__
	(
		"outl %0, %1"
		:
		: "a"(value), "dN"(port)
		: "memory"
	);
}

static INLINE void
	outsb(uint16_t port, const void *addr, uint32_t count)
{
	__asm__ __volatile__
	(
		"rep outsb"
		: "+S"(addr), "+c"(count)
		: "d"(port)
		: "memory"
	);
}

static INLINE void
	outsw(uint16_t port, const void *addr, uint32_t count)
{
	__asm__ __volatile__
	(
		"rep outsw"
		: "+S"(addr), "+c"(count)
		: "d"(port)
		: "memory"
	);
}

static INLINE void
	outsl(uint16_t port, const void *addr, uint32_t count)
{
	__asm__ __volatile__
	(
		"rep outsl"
		: "+S"(addr), "+c"(count)
		: "d"(port)
		: "memory"
	);
}

static INLINE void
	io_wait(void)
{
	__asm__ __volatile__
	(
		"outb %%al, $0x80"
		:
		: "a"(0)
		: "memory"
	);
}

/* *************************** [^] FUNCTIONS [^] **************************** */

#endif /* IO_H */
