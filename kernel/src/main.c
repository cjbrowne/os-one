#include "vga.h"

int main(struct multiboot *mboot_ptr)
{
	vga_clear();
	vga_print("Hello, world!");
	return 0x1337C0DE;
}
