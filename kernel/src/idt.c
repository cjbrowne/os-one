#include "idt.h"

extern void idt_flush(u32int);

static void init_idt();
static void idt_set_gate(u8int, u32int, u16int, u8int);

idt_entry idt_entries[256];
idt_ptr idt;

void init_descriptor_tables()
{
	init_idt();
}
