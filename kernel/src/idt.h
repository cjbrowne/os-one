#ifndef IDT_H
#define IDT_H

typedef
struct id_entry_struct
{
	u16int base_lo;		// the lower 16 bits of the address to jump to when this interrupt fires
	u16int sel;		// kernel segment selector
	u8int  always0;		// an always-zero value (some kind of error checking?)
	u8int  flags; 		// some IDT flags (see dox)
	u16int base_mid;	// the mid 16 bits of the address to jump to when this interrupt fires
	u32int base_hi;		// the higher 16 bits of the address to jump to when this interrupt fires
	u32int pad_zero;
} __attribute__((packed))
idt_entry;


typedef
struct idt_ptr_struct
{
	u16int limit;
	u64int base;
} __attribute__((packed))
idt_ptr;


#define EXC_DIVISION_BY_ZERO 		0
#define EXC_DEBUG 			1
#define EXC_NON_MASKABLE_INT 		2
#define EXC_BREAKPOINT 			3
#define EXC_INTO_DETECTED_OVERFLOW 	4
#define EXC_OUT_OF_BOUNDS		5
#define EXC_INVALID_OPCODE		6
#define EXC_NO_COPROCESSOR		7
#define EXC_DOUBLE_FAULT		8
#define EXC_COPROCESSOR_SEG_OVERRUN	9
#define EXC_BAD_TSS			10
#define EXC_SEGMENT_NOT_PRESENT		11
#define EXC_STACK_FAULT			12
#define EXC_GENERAL_PROTECTION_FAULT	13
#define EXC_PAGE_FAULT			14
#define EXC_UNKNOWN_INTERRUPT		15
#define EXC_COPROCESSOR_FAULT		16
#define EXC_ALIGNMENT_CHECK		17
#define EXC_MACHINE_CHECK		18
// 19-31 are reserved exceptions

// ISR handlers are written in ASM
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

void init_descriptor_tables();

#endif
