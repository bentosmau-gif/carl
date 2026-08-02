/*
 * CarlOS - boot.s
 * Kernel entry point in long mode (x86_64).
 * Performs minimal setup and transfers control to run_kernel().
 */

.global _start
.section .text
.align 16

_start:
    cli                         # disable interrupts

    # Temporary stack (adjust according to your memory map)
    mov $0x800000, %rsp
    mov $0x800000, %rbp

    # Load kernel data segments (GDT must be loaded before this)
    mov $0x10, %ax              # kernel data selector
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    # Jump into the C kernel entry
    call run_kernel

.hang:
    hlt
    jmp .hang
