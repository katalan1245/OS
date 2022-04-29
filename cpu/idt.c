#include "idt.h"
#include "../libc/bits.h"

idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

void set_idt_gate(int n, uint32_t handler)
{
    idt[n].low_offset = low_two_bytes(handler);
    idt[n].segement_selector = KERNEL_CS;
    idt[n].zero_byte = 0;
    idt[n].flags = 0x8E;
    idt[n].high_offset = high_two_bytes(handler);
}

void set_idt()
{
    idt_reg.base = (uint32_t)&idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
    __asm__ __volatile__("lidt (%0)"
                         :
                         : "r"(&idt_reg));
}