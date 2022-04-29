#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "../libc/string.h"

void main()
{
    clear_screen();
    isr_install();
    irq_install();

    kprint("Type HALT to halt the cpu and kill the os\n> ");
}

void user_input(char *input) {
    if(!strcmp(input, "HALT")) {
        kprint("CPU HALTED!\n");
        asm volatile("hlt");
    }

    kprint("User Input: ");
    kprint(input);
    kprint("\n> ");
}