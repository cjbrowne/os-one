#include "common.h"
#include "idt.h"

extern void idt_flush(u64int);

static void init_idt();
static void idt_set_gate(u8int, u64int, u16int, u8int);

idt_entry idt_entries[256];
idt_ptr idt;

void init_descriptor_tables()
{
	init_idt();
}

static void init_idt()
{
	idt.limit = sizeof (idt_entry) * 256 - 1;
	idt.base  = (u64int)&idt_entries;

	memset(&idt_entries, 0, sizeof(idt_entry)*256);

	idt_set_gate(0, (u64int)isr0, 0x08, 0x8E);
	idt_set_gate(1, (u64int)isr1, 0x08, 0x8E);
	idt_set_gate(2, (u64int)isr2, 0x08, 0x8E);
	idt_set_gate(3, (u64int)isr3, 0x08, 0x8E);
	idt_set_gate(4, (u64int)isr4, 0x08, 0x8E);
	idt_set_gate(5, (u64int)isr5, 0x08, 0x8E);
	idt_set_gate(6, (u64int)isr6, 0x08, 0x8E);
	idt_set_gate(7, (u64int)isr7, 0x08, 0x8E);
	idt_set_gate(8, (u64int)isr8, 0x08, 0x8E);
	idt_set_gate(9, (u64int)isr9, 0x08, 0x8E);
	idt_set_gate(10, (u64int)isr10, 0x08, 0x8E);
	idt_set_gate(11, (u64int)isr11, 0x08, 0x8E);
	idt_set_gate(12, (u64int)isr12, 0x08, 0x8E);
	idt_set_gate(13, (u64int)isr13, 0x08, 0x8E);
	idt_set_gate(14, (u64int)isr14, 0x08, 0x8E);
	idt_set_gate(15, (u64int)isr15, 0x08, 0x8E);
	idt_set_gate(16, (u64int)isr16, 0x08, 0x8E);
	idt_set_gate(17, (u64int)isr17, 0x08, 0x8E);
	idt_set_gate(18, (u64int)isr18, 0x08, 0x8E);
	idt_set_gate(19, (u64int)isr19, 0x08, 0x8E);
	idt_set_gate(20, (u64int)isr20, 0x08, 0x8E);
	idt_set_gate(21, (u64int)isr21, 0x08, 0x8E);
	idt_set_gate(22, (u64int)isr22, 0x08, 0x8E);
	idt_set_gate(23, (u64int)isr23, 0x08, 0x8E);
	idt_set_gate(24, (u64int)isr24, 0x08, 0x8E);
	idt_set_gate(25, (u64int)isr25, 0x08, 0x8E);
	idt_set_gate(26, (u64int)isr26, 0x08, 0x8E);
	idt_set_gate(27, (u64int)isr27, 0x08, 0x8E);
	idt_set_gate(28, (u64int)isr28, 0x08, 0x8E);
	idt_set_gate(29, (u64int)isr29, 0x08, 0x8E);
	idt_set_gate(30, (u64int)isr30, 0x08, 0x8E);
	idt_set_gate(31, (u64int)isr31, 0x08, 0x8E);

	idt_flush((u64int) &idt);
}

static void idt_set_gate(u8int num, u64int base, u16int sel, u8int flags)
{
	idt_entries[num].base_lo = base & 0xFFFF;
	idt_entries[num].base_mid = (base >> 16) & 0xFFFF;
	idt_entries[num].base_hi = (base >> 32) & 0xFFFFFFFF;
	idt_entries[num].sel     = sel;
	idt_entries[num].always0 = 0;
	idt_entries[num].pad_zero = 0;
	// when we get to user mode, add | 0x60
	// to set the interrupt gate's privilege level to 3
	idt_entries[num].flags   = flags;
}
