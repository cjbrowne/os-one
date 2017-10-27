#include "common.h"
#include "isr.h"
#include "vga.h"

void isr_handler(registers_t regs)
{
	vga_print("received interrupt: ");
	vga_print_dec(regs.int_no);
	vga_putc('\n');
}
