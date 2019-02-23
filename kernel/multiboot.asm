BITS 32

; ====================================
;   Multiboot2
; ====================================

; ------------------------------------
; Header values
; ------------------------------------
MAGIC equ 0xE85250D6
ARCHITECTURE equ 0
LENGTH equ (multiboot_header_end - multiboot_header)
CHECKSUM equ  -(MAGIC + ARCHITECTURE + LENGTH)

; ------------------------------------
; Actual header
; ------------------------------------
SECTION .multiboot_header
ALIGN 8
multiboot_header:
DD MAGIC
DD ARCHITECTURE
DD LENGTH
DD CHECKSUM

; Null tag (end of tags)
DW 0
DW 0
DW 8
multiboot_header_end:

; ====================================
;   Multiboot entry
; ====================================
SECTION .text

global multiboot_main
multiboot_main:

    ; set the pml4 entry
    lea eax, [pdpe]
    and eax, 0xFFFF000
    or eax, 0x3
    mov [pml4 + 4], eax

    ; set the pdpe entry
    mov eax, 0x83
    mov [pdpe + 4], eax

    lea eax, [pml4]
    mov cr3, eax

    ; Enable PAE-paging
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    ; Enter long mode compatability mode
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    ; Enable paging
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    ; Jump to the kernel using real long mode (64bit)
    lgdt [gdt64]
    jmp 8:multiboot_64bit

BITS 64
    extern kernel_main
    multiboot_64bit:
        mov rsp, kernel_stack
        push rbx
        call kernel_main
        add rsp, 4

        ; halt if we reach here
        cli
        hlt

; ====================================
;   64Bit GDT
; ====================================

; --------------------------------
; The GDT64 table
; --------------------------------
gdt64_start:

    ; --------------------------------
    ; NULL entry
    ; --------------------------------
    dw 0xFFFF
    dw 0
    db 0
    db 0
    db 1
    db 0

    ; --------------------------------
    ; Code segment
    ; --------------------------------
    dw 0
    dw 0
    db 0
    db 10011010b
    db 10101111b
    db 0

    ; --------------------------------
    ; Data segment
    ; --------------------------------
    dw 0
    dw 0
    db 0
    db 10010010b
    db 00000000b
    db 0

gdt64_end:

; --------------------------------
; The actual pointer
; --------------------------------
global gdt64
gdt64:
    dw gdt64_end - gdt64_start - 1
    dq gdt64_start

; ====================================
;   Paging (1GB identity mapping)
; ====================================
SECTION .bss

alignb 4096

pml4:
resq 512

pdpe:
resq 512

; ====================================
;   Stack
; ====================================
SECTION .bss

resb 2 * 1024 * 1024
kernel_stack: