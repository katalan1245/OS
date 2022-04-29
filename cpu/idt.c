#include "idt.h"

idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

void set_idt_gate(int n, uint32_t handler)
{
    idt[n].low_offset = (uint16_t)((handler)&0xffff);
    idt[n].segement_selector = KERNEL_CS;
    idt[n].zero_byte = 0;
    idt[n].flags = 0x8E;
    idt[n].high_offset = (uint16_t)(((handler) >> 16) & 0xffff);
}

void set_idt()
{
    idt_reg.base = (uint32_t)&idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
    asm volatile("lidt (%0)"
                 :
                 : "m"(idt_reg));
}