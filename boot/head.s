/*
 * CarlOS - head.s
 * Early x86 setup:
 *  - enable PAE
 *  - load PML4
 *  - enable long mode
 *  - enable paging
 *  - jump to 64-bit entry (_start)
 */

.global _head_start
.extern _start          # defined in boot.s
.extern pml4_table      # PML4 table symbol

.section .text
.align 16

_head_start:
    cli

    # Enable PAE
    mov %cr4, %eax
    or  $0x20, %eax            # set PAE bit
    mov %eax, %cr4

    # Load PML4 base into CR3
    mov $pml4_table, %eax
    mov %eax, %cr3

    # Enable long mode via EFER.LME
    mov $0xC0000080, %ecx      # EFER MSR
    rdmsr
    or  $0x00000100, %eax      # set LME bit
    wrmsr

    # Enable paging + protected mode (PG + PE)
    mov %cr0, %eax
    or  $0x80000001, %eax
    mov %eax, %cr0

    # Far jump to 64-bit code: CS = 0x08, RIP = _start
    ljmp $0x08, $_start
