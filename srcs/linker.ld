OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
SECTIONS
{
	. = 1M;
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	} :text

	.data :
	{
		*(.data)
	} :data

	.bss :
	{
		*(.bss)
	} :data
}

PHDRS
{
	text PT_LOAD FLAGS(0x5);
	data PT_LOAD FLAGS(0x6);
}
