section .multiboot_header
align 8

header_start:

    dd 0xE85250D6
    dd 0
    dd header_end - header_start
    dd -(0xE85250D6 + (header_end - header_start))

    ; End tag
    dw 0
    dw 0
    dd 8

header_end:


section .bss

align 4096

pg14:
    resb 4096

pg13:
    resb 4096

pg12:
    resb 4096

align 16

stack_bottom:
    resb 4096 * 4

stack_top:


section .rodata

align 8

gdt64:

    dq 0
    dq 0x00AF9A000000FFFF
    dq 0x00CF92000000FFFF

gdt64_end:

gdt64_pointer:
    dw gdt64_end - gdt64 - 1
    dq gdt64


section .text
    

bits 32

global _comecar

_comecar:

    cli

    mov esp, stack_top

    mov edi, pg14
    xor eax, eax

    mov ecx, 4096 * 3 / 4
    rep stosd

    mov eax, pg13
    or eax, 0b11

    mov [pg14], eax

    mov eax, pg12
    or eax, 0b11

    mov [pg13], eax

    mov eax, 0x00000000
    or eax, 0b10000011

    mov [pg12], eax

    mov eax, 0x00200000
    or eax, 0b10000011

    mov [pg12 + 8], eax

    mov eax, pg14
    mov cr3, eax

    mov eax, cr4
    or eax, (1 << 5)
    mov cr4, eax

    mov ecx, 0xC0000080

    rdmsr

    or eax, (1 << 8)

    wrmsr

    mov eax, cr0
    or eax, (1 << 31)
    mov cr0, eax

    mov word [0xB8000], 0x0F31
    mov word [0xB8002], 0x0F32
    mov word [0xB8004], 0x0F33
    mov word [0xB8006], 0x0F34

    lgdt [gdt64_pointer]

    jmp 0x08:init_64

bits 64
init_64:

    mov rsp, stack_top

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    extern toy
    call toy

.loop:
    hlt
    jmp .loop