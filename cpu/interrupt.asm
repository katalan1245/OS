; Defined in isr.c
[extern isr_handler]
[extern irq_handler]

; This is our common ISR stub. It saves the processor state, sets
; up for kernel mode segments, calls the C-level fault handler,
; and finally restores the stack frame.
isr_common_stub:
    ; Save CPU state
    pushad
    mov ax, ds
    push eax    ; Save the data segment descriptor

    mov ax, 0x10 ; load the kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Call C handler
    call isr_handler

    ; Restore state
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popad
    add esp, 8 ; Cleans up the pushed error code and ISR number
    sti
    iret    ; Pops 5 things at once: CS, EIP, EFLAGS, SS and ESP

; Identical to ISR code except for the 'call' and the 'pop ebx'
irq_common_stub:
    pusha
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    ; Call C handler
    call irq_handler
    pop ebx ; Different than the ISR code
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx
    popa
    add esp, 8
    sti
    iret
 
; We don't get information about which interrupt was caller
; when the handler is run, so we will need to have a different handler
; for every interrupt.
; Furthermore, some interrupts push an error code onto the stack but others
; don't, so we will push a dummy error code for those which don't, so that
; we have a consistent stack for all of them.

%macro ISR_NOERRORCODE 1 ; Define a macro taking one parameter
    [global isr%1] ; %1 accesses the first parameter
    isr%1:
        cli ; Disable interrupts
        push byte 0 ; Push a dummy error code (if isr doesn't push it's own error code)
        push byte %1 ; Push the interrupt number
        jmp isr_common_stub
%endmacro

%macro ISR_ERRORCODE 1
    [global isr%1]
    isr%1:
        cli
        push byte %1
        jmp isr_common_stub
%endmacro

%macro IRQ 2
    [global irq%1]
    irq%1:
        cli
        push byte 0
        push byte %2
        jmp irq_common_stub
%endmacro

ISR_NOERRORCODE 0
ISR_NOERRORCODE 1
ISR_NOERRORCODE 2
ISR_NOERRORCODE 3
ISR_NOERRORCODE 4
ISR_NOERRORCODE 5
ISR_NOERRORCODE 6
ISR_NOERRORCODE 7
ISR_ERRORCODE 8
ISR_NOERRORCODE 9
ISR_ERRORCODE 10
ISR_ERRORCODE 11
ISR_ERRORCODE 12
ISR_ERRORCODE 13
ISR_ERRORCODE 14
ISR_NOERRORCODE 15
ISR_NOERRORCODE 16
ISR_NOERRORCODE 17
ISR_NOERRORCODE 18
ISR_NOERRORCODE 19
ISR_NOERRORCODE 20
ISR_NOERRORCODE 21
ISR_NOERRORCODE 22
ISR_NOERRORCODE 23
ISR_NOERRORCODE 24
ISR_NOERRORCODE 25
ISR_NOERRORCODE 26
ISR_NOERRORCODE 27
ISR_NOERRORCODE 28
ISR_NOERRORCODE 29
ISR_NOERRORCODE 30
ISR_NOERRORCODE 31

IRQ   0,  32
IRQ   1,  33
IRQ   2,  34
IRQ   3,  35
IRQ   4,  36
IRQ   5,  37
IRQ   6,  38
IRQ   7,  39
IRQ   8,  40
IRQ   9,  41
IRQ  10,  42
IRQ  11,  43
IRQ  12,  44
IRQ  13,  45
IRQ  14,  46
IRQ  15,  47