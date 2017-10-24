; Based on James Molloy's tutorial file boot.s
; Which was based on Bran's kernel development tutorial file start.asm

MBOOT_PAGE_ALIGN	equ	1<<0	; load kernel and kernel modules on a page boundary
MBOOT_MEM_INFO		equ	1<<1	; allow kernel to know how much memory is available (useful for memory management)
MBOOT_HEADER_MAGIC	equ	0x1BADB002	; GRUB needs this to find the kernel in a multiboot scenario
MBOOT_HEADER_FLAGS	equ	MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM		equ	-(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[BITS 32]

[GLOBAL mboot]
[EXTERN code]
[EXTERN bss]
[EXTERN end]

mboot:
	dd	MBOOT_HEADER_MAGIC
	dd	MBOOT_HEADER_FLAGS
	dd	MBOOT_CHECKSUM
	dd	mboot
	dd	code
	dd	bss
	dd	end
	dd	start

[GLOBAL start]
[EXTERN main]

start:
	push	ebx

	cli
	call main
	jmp $
