
.global page_fault_handler

.section .text
.align 16

page_fault_handler:
    /* ---------------------------------------------------------
     * Save general-purpose registers
     * --------------------------------------------------------- */
    pushq %rax
    pushq %rcx
    pushq %rdx
    pushq %rbx
    pushq %rbp
    pushq %rsi
    pushq %rdi
    pushq %r8
    pushq %r9
    pushq %r10
    pushq %r11

    /* ---------------------------------------------------------
     * Load kernel data segment (CarlOS uses selector 0x10)
     * --------------------------------------------------------- */
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    /* ---------------------------------------------------------
     * Read CR2 (faulting virtual address)
     * --------------------------------------------------------- */
    mov %cr2, %rdi        /* arg0: fault address */

    /* ---------------------------------------------------------
     * Read error code pushed by CPU
     * (the error code is at the top of the stack)
     * --------------------------------------------------------- */
    mov 8(%rsp), %rsi     /* arg1: error code */

    /* ---------------------------------------------------------
     * Call mm_fault_dispatch(addr, error_code)
     * --------------------------------------------------------- */
    call mm_fault_dispatch

    /* ---------------------------------------------------------
     * Restore registers
     * --------------------------------------------------------- */
    popq %r11
    popq %r10
    popq %r9
    popq %r8
    popq %rdi
    popq %rsi
    popq %rbp
    popq %rbx
    popq %rdx
    popq %rcx
    popq %rax

    /* ---------------------------------------------------------
     * Return from exception
     * --------------------------------------------------------- */
    iretq
