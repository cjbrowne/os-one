ENTRY(start)

SECTIONS
{
	. = 1M;

	.boot :
	{
		*(.multiboot_header)
	}

	.text :
	{
		code = .; _code = .; __code = .;
		*(.text)
	}

	.data : 
	{
		data = .; _data = .; __data = .;
		*(.data)
		*(.rodata)
	}

	.bss :
	{
		bss = .; _bss = .; __bss = .;
		*(.bss)
	}

	end = .; _end = .; __end = .;

}
