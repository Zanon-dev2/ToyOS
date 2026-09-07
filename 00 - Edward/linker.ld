OUTPUT_FORMAT("elf64-x86-64")
ENTRY(_comecar)

SECTIONS
{
    . = 1M;

    .text ALIGN(16) :
    {
        KEEP(*(.multiboot_header))
        *(.text)
    }

    .rodata ALIGN(16) :
    {
        *(.rodata)
    }

    .data ALIGN(16) :
    {
        *(.data)
    }

    .bss ALIGN(4096) :
    {
        *(COMMON)
        *(.bss)
    }
}