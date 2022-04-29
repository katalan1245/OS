#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define KERNEL_CS 0x08
#define IDT_ENTRIES 256

/* interrupt gate (hadnler) structure */
typedef struct
{
    uint16_t low_offset;
    uint16_t segement_selector;
    uint8_t zero_byte;
    /*
        [ 15 | 14 13 | 12 | 11 | 10 9 8 ]
        [ P  | DPl   | 0  | D  |  1 1 0 ]
        P- If the handler is present in memory (1 = present, 0 = not present)
        DPL- Descriptor Privilige Level, the privilige level the handler can be called from (0,1,2,3)
        D- Size of gate (1 = 32bits, 0 = 16bits)
    */
    uint8_t flags;
    uint16_t high_offset;
} __attribute__((packed)) idt_gate_t;

/* A pointer to the array of interrupt gates
 * Assembly instruction `lidt` will read it */
typedef struct
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_register_t;

extern idt_gate_t idt[IDT_ENTRIES];
extern idt_register_t idt_reg;

void set_idt_gate(int n, uint32_t handler);
void set_idt();

#endif