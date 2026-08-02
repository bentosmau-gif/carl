/*
 * carl_traps.S
 * Low-level trap handlers for CarlOS (GPLv2).
 * Inspirado en el patrón clásico x86: guarda contexto, llama a C, iret.
 */

    .globl carl_divide_error, carl_debug, carl_nmi, carl_int3
    .globl carl_overflow, carl_bounds, carl_invalid_op
    .globl carl_device_not_available, carl_double_fault
    .globl carl_coprocessor_segment_overrun
    .globl carl_invalid_tss, carl_segment_not_present
    .globl carl_stack_segment, carl_general_protection
    .globl carl_coprocessor_error, carl_reserved

/* Prototipos C (lado kernel Carl):
 * void carl_do_divide_error(struct carl_trap_frame *tf, unsigned long err);
 * void carl_do_debug(struct carl_trap_frame *tf, unsigned long err);
 * ...
 */

#define CARL_DS 0x10

/* --- helpers de contexto --- */

.macro CARL_SAVE_CONTEXT
    pushl   %ebx
    pushl   %ecx
    pushl   %edx
    pushl   %edi
    pushl   %esi
    pushl   %ebp
    push    %ds
    push    %es
    push    %fs
.endm

.macro CARL_RESTORE_CONTEXT
    pop     %fs
    pop     %es
    pop     %ds
    popl    %ebp
    popl    %esi
    popl    %edi
    popl    %edx
    popl    %ecx
    popl    %ebx
    popl    %eax
    iret
.endm

/* --- traps sin error code --- */

carl_divide_error:
    pushl   $carl_do_divide_error
carl_no_error_code:
    xchgl   %eax,(%esp)        /* eax = handler C, [esp] = eax viejo */
    CARL_SAVE_CONTEXT
    pushl   $0                 /* error code = 0 */
    lea     44(%esp),%edx      /* puntero a carl_trap_frame */
    pushl   %edx               /* arg0: tf */
    movl    $CARL_DS,%edx
    mov     %dx,%ds
    mov     %dx,%es
    mov     %dx,%fs
    call    *%eax              /* handler C(tf, err=0) */
    addl    $8,%esp            /* limpia args */
    CARL_RESTORE_CONTEXT

carl_debug:
    pushl   $carl_do_debug
    jmp     carl_no_error_code

carl_nmi:
    pushl   $carl_do_nmi
    jmp     carl_no_error_code

carl_int3:
    pushl   $carl_do_int3
    jmp     carl_no_error_code

carl_overflow:
    pushl   $carl_do_overflow
    jmp     carl_no_error_code

carl_bounds:
    pushl   $carl_do_bounds
    jmp     carl_no_error_code

carl_invalid_op:
    pushl   $carl_do_invalid_op
    jmp     carl_no_error_code

/* --- FPU / dispositivo no disponible --- */

carl_math_emulate:
    popl    %eax
    pushl   $carl_do_device_not_available
    jmp     carl_no_error_code

carl_device_not_available:
    pushl   %eax
    movl    %cr0,%eax
    bt      $2,%eax            /* EM bit: emulación de FPU */
    jc      carl_math_emulate
    clts                        /* limpia TS para usar FPU */
    movl    carl_current,%eax
    cmpl    carl_last_task_used_math,%eax
    je      1f
    pushl   %ecx
    pushl   %edx
    push    %ds
    movl    $CARL_DS,%eax
    mov     %ax,%ds
    call    carl_math_state_restore
    pop     %ds
    popl    %edx
    popl    %ecx
1:  popl    %eax
    iret

/* --- otros traps sin error code --- */

carl_coprocessor_segment_overrun:
    pushl   $carl_do_coprocessor_segment_overrun
    jmp     carl_no_error_code

carl_reserved:
    pushl   $carl_do_reserved
    jmp     carl_no_error_code

carl_coprocessor_error:
    pushl   $carl_do_coprocessor_error
    jmp     carl_no_error_code

/* --- traps con error code --- */

carl_double_fault:
    pushl   $carl_do_double_fault
carl_error_code:
    xchgl   %eax,4(%esp)       /* error code <-> eax */
    xchgl   %ebx,(%esp)        /* &handler C <-> ebx */
    CARL_SAVE_CONTEXT
    pushl   %eax               /* error code */
    lea     44(%esp),%eax      /* puntero a carl_trap_frame */
    pushl   %eax               /* arg0: tf */
    movl    $CARL_DS,%eax
    mov     %ax,%ds
    mov     %ax,%es
    mov     %ax,%fs
    call    *%ebx              /* handler C(tf, err) */
    addl    $8,%esp
    CARL_RESTORE_CONTEXT

carl_invalid_tss:
    pushl   $carl_do_invalid_tss
    jmp     carl_error_code

carl_segment_not_present:
    pushl   $carl_do_segment_not_present
    jmp     carl_error_code

carl_stack_segment:
    pushl   $carl_do_stack_segment
    jmp     carl_error_code

carl_general_protection:
    pushl   $carl_do_general_protection
    jmp     carl_error_code
