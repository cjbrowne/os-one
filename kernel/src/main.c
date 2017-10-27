#include "vga.h"
#include "util.h"
#include "idt.h"

#define VERSION "0.01"

struct meminfo
{
	u32int flags;
	u32int mem_lower;
	u32int mem_upper;
	u32int boot_device;
	u32int cmdline;
	u32int mods_count;
	u32int mods_addr;
	u32int syms[3];
	u32int mmap_length;
	u32int mmap_addr;
	u32int drives_length;
	u32int drives_adr;
	u32int config_table;
	u32int boot_loader_name;
	u32int apm_table;
	u32int vbe_control_info;
	u32int vbe_mode_info;
	u16int vbe_mode;
	u16int vbe_interface_seg;
	u16int vbe_interface_off;
	u16int vbe_interface_len;
	u64int framebuffer_addr;
	u32int framebuffer_pitch;
	u32int framebuffer_width;
	u32int framebuffer_height;
	u8int framebuffer_bpp;
	u8int framebuffer_type;
	u8int color_info[5];
}__attribute__((packed));

void reset_cpu(void)
{
	asm volatile ("mov $0, %ax");
	asm volatile ("mov %ax, %ss");
	asm volatile ("mov %ax, %ds");
	asm volatile ("mov %ax, %es");
	asm volatile ("mov %ax, %fs");
	asm volatile ("mov %ax, %gs");
}

void print_mem_info(void)
{
	register int ebx asm ("ebx");
	struct meminfo* meminfo_ptr;
	meminfo_ptr = (struct meminfo*) ebx;
	vga_print("memory start:");
	vga_print("memory length:");
}

int main(struct multiboot *mboot_ptr)
{
	reset_cpu();
	vga_clear();
	vga_print("OS One version");
	vga_print(VERSION);
	vga_print("\n");
	init_descriptor_tables();
	asm volatile("int $0x3");
	asm volatile("int $0x4");
	for(;;);
	return 0x1337C0DE;
}
