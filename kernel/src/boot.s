; Based on James Molloy's tutorial file boot.s
; Which was based on Bran's kernel development tutorial file start.asm

MBOOT_PAGE_ALIGN	equ	1<<0	; load kernel and kernel modules on a page boundary
MBOOT_MEM_INFO		equ	1<<1	; allow kernel to know how much memory is available (useful for memory management)
MBOOT_HEADER_MAGIC	equ	0xE85250D6	; GRUB needs this to find the kernel in a multiboot scenario
MBOOT_ARCH		equ	0x00000000	; architecture = i386

[BITS 32]

[GLOBAL header_start]
[EXTERN code]
[EXTERN bss]
[EXTERN end]

section .multiboot_header
header_start:
	dd	MBOOT_HEADER_MAGIC
	dd	MBOOT_ARCH
	dd	header_end - header_start
	dd	0x100000000 - (MBOOT_HEADER_MAGIC + MBOOT_ARCH + (header_end - header_start))

	; required end tag
	dw	0 ; type
	dw	0 ; flags
	dd	8 ; size
header_end:

[GLOBAL start]
[EXTERN main]

section .bss
align 4096
p4_table:
	resb 4096
p3_table:
	resb 4096
p2_table:
	resb 4096
stack_bottom:
	resb 4096 * 4
stack_top:

section .rodata
gdt64:
	dq 0 ; zero entry
.code: equ $ - gdt64
	dq (1<<43) | (1<<44) | (1<<47) | (1<<53) ; code segment
.pointer:
	dw $ - gdt64 - 1
	dq gdt64

section .text
start:
	mov esp, stack_top

	call check_multiboot
	call check_cpuid
	call check_long_mode

	call set_up_page_tables
	call enable_paging

	lgdt [gdt64.pointer]


	jmp gdt64.code:main

	jmp infinite_loop



; simply prints the message 'error', followed by the error code in AL
error:
	mov dword [0xb8000], 0x4f524f45
	mov dword [0xb8004], 0x4f3a4f52
	mov dword [0xb8008], 0x4f204f20
	mov byte  [0xb800a], al
	jmp infinite_loop

set_up_page_tables:
	; map first P4 entry to P3 table
	mov eax, p3_table
	or eax, 0b11 ; present + writeable
	mov [p4_table], eax

	; map first P3 entry to P2 table
	mov eax, p2_table
	or eax, 0b11 ; present + writeable
	mov [p3_table], eax

	mov ecx, 0

.map_p2_table:
	mov eax, 0x200000
	mul ecx
	or eax, 0b10000011 ; present + writeable + huge
	mov [p2_table + ecx * 8], eax

	inc ecx
	cmp ecx, 512
	jne .map_p2_table

	ret

enable_paging:
	mov eax, p4_table
	mov cr3, eax

	mov eax, cr4
	or eax, 1 << 5
	mov cr4, eax

	mov ecx, 0xC0000080
	rdmsr
	or eax, 1 << 8
	wrmsr

	mov eax, cr0
	or eax, 1 << 31
	mov cr0, eax

	ret


; check if multiboot was successful
check_multiboot:
	cmp	eax, 0x36d76289
	jne	.no_multiboot
	ret

.no_multiboot:
	mov	al, "0"
	jmp	error

check_cpuid:
	pushfd
	pop eax

	mov ecx, eax
	xor eax, 1 << 21

	push eax
	popfd

	pushfd
	pop eax

	push ecx
	popfd

	cmp eax, ecx
	je .no_cpuid
	ret
.no_cpuid:
	mov al, "1"
	jmp error


check_long_mode:
	mov eax, 0x80000000
	cpuid
	cmp eax, 0x80000001
	jb .no_long_mode

	mov eax, 0x80000001
	cpuid
	test edx, 1 << 29
	jz .no_long_mode
	ret
.no_long_mode:
	mov al, "2"
	jmp error
infinite_loop:
	jmp $


