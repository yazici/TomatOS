BITS 64
SECTION .text

; GDT stuff
GDT_KERNEL_CODE equ 8
GDT_KERNEL_DATA equ 16
GDT_USER_DATA equ (24 | 3)
GDT_USER_CODE equ (32 | 3)

fix_data_segment:
	mov ax, GDT_KERNEL_DATA
	mov ds, ax
	mov es, ax

	; we set gs and fs here to a user segment
	; since we are gonna set the msrs for the
	; base
	mov ax, GDT_USER_DATA
	mov fs, ax
	mov gs, ax
	ret


GLOBAL gdt_fix_segments
gdt_fix_segments:
	mov rax, rsp
	push qword GDT_KERNEL_DATA
	push qword rax
	pushf
	push qword GDT_KERNEL_CODE
	push qword fix_data_segment
	iretq
