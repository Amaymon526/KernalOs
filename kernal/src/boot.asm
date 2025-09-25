; Minimal Multiboot Header für GRUB
section .multiboot
align 4
    dd 0x1BADB002            ; magic number (Multiboot v1)
    dd 0x0                   ; flags
    dd -(0x1BADB002 + 0x0)   ; checksum

section .text
global _start
_start:
    extern kernel_main
    call kernel_main
    cli
.hang:
    hlt
    jmp .hang
