#include "isr.h"
#include "idt.h"
#include "../drivers/screen.h"
#include "../drivers/ports.h"
#include "../libc/cast.h"

isr_t interrupt_handlers[256];

void isr_install()
{
    set_idt_gate(0, (uint32_t)isr0);
    set_idt_gate(1, (uint32_t)isr1);
    set_idt_gate(2, (uint32_t)isr2);
    set_idt_gate(3, (uint32_t)isr3);
    set_idt_gate(4, (uint32_t)isr4);
    set_idt_gate(5, (uint32_t)isr5);
    set_idt_gate(6, (uint32_t)isr6);
    set_idt_gate(7, (uint32_t)isr7);
    set_idt_gate(8, (uint32_t)isr8);
    set_idt_gate(9, (uint32_t)isr9);
    set_idt_gate(10, (uint32_t)isr10);
    set_idt_gate(11, (uint32_t)isr11);
    set_idt_gate(12, (uint32_t)isr12);
    set_idt_gate(13, (uint32_t)isr13);
    set_idt_gate(14, (uint32_t)isr14);
    set_idt_gate(15, (uint32_t)isr15);
    set_idt_gate(16, (uint32_t)isr16);
    set_idt_gate(17, (uint32_t)isr17);
    set_idt_gate(18, (uint32_t)isr18);
    set_idt_gate(19, (uint32_t)isr19);
    set_idt_gate(20, (uint32_t)isr20);
    set_idt_gate(21, (uint32_t)isr21);
    set_idt_gate(22, (uint32_t)isr22);
    set_idt_gate(23, (uint32_t)isr23);
    set_idt_gate(24, (uint32_t)isr24);
    set_idt_gate(25, (uint32_t)isr25);
    set_idt_gate(26, (uint32_t)isr26);
    set_idt_gate(27, (uint32_t)isr27);
    set_idt_gate(28, (uint32_t)isr28);
    set_idt_gate(29, (uint32_t)isr29);
    set_idt_gate(30, (uint32_t)isr30);
    set_idt_gate(31, (uint32_t)isr31);

    /* Remap the PIC */
    uint8_t m1, m2;

    /* save masks */
    m1 = port_byte_in(PIC1_DATA);
    m2 = port_byte_in(PIC2_DATA);

    port_byte_out(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4); /* starts the initialization sequence (in cascade mode) */
    io_wait();
    port_byte_out(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    port_byte_out(PIC1_DATA, MASTER_PIC_OFFSET); /* ICW2: Master PIC vector offset */
    io_wait();
    port_byte_out(PIC2_DATA, SLAVE_PIC_OFFSET); /* ICW2: Slave PIC vector offset */
    io_wait();
    port_byte_out(PIC1_DATA, ICW3_MASTER_PIC);
    io_wait();
    port_byte_out(PIC2_DATA, ICW3_SLAVE_PIC);
    io_wait();

    /* restore masks */
    port_byte_out(PIC1_DATA, m1);
    port_byte_out(PIC2_DATA, m2);

    /* install the IRQs */
    set_idt_gate(IRQ0, (uint32_t)irq0);
    set_idt_gate(IRQ1, (uint32_t)irq1);
    set_idt_gate(IRQ2, (uint32_t)irq2);
    set_idt_gate(IRQ3, (uint32_t)irq3);
    set_idt_gate(IRQ4, (uint32_t)irq4);
    set_idt_gate(IRQ5, (uint32_t)irq5);
    set_idt_gate(IRQ6, (uint32_t)irq6);
    set_idt_gate(IRQ7, (uint32_t)irq7);
    set_idt_gate(IRQ8, (uint32_t)irq8);
    set_idt_gate(IRQ9, (uint32_t)irq9);
    set_idt_gate(IRQ10, (uint32_t)irq10);
    set_idt_gate(IRQ11, (uint32_t)irq11);
    set_idt_gate(IRQ12, (uint32_t)irq12);
    set_idt_gate(IRQ13, (uint32_t)irq13);
    set_idt_gate(IRQ14, (uint32_t)irq14);
    set_idt_gate(IRQ15, (uint32_t)irq15);

    set_idt(); /* Load with ASM */
}

/* To print the message which defines every exception */
char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"};

void isr_handler(registers_t r)
{
    kprint("received interrupt: ");
    char s[3];
    itoa(r.int_no, s);
    kprint(s);
    kprint("\n");
    kprint(exception_messages[r.int_no]);
    kprint("\n");
}

void add_interrupt_handler(uint8_t n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}

void irq_handler(registers_t r)
{
    /* After every interrupt we need to send an EOI to the PICs or they will not send another interrupt again */
    if (r.int_no >= SLAVE_PIC_OFFSET)
        port_byte_out(PIC2_COMMAND, PIC_EOI); /* Slave */
    port_byte_out(PIC1_COMMAND, PIC_EOI);     /* Master */

    /* Handle the interrupt in a modular way */
    if (interrupt_handlers[r.int_no] != 0)
    {
        isr_t handler = interrupt_handlers[r.int_no];
        handler(r);
    }
}