#include "../drivers/screen.h"
#include "../libc/cast.h"
#include "../cpu/isr.h"

void main()
{
    clear_screen();
    isr_install();
    kprint("Checking Interrupts...\n");
    __asm__ __volatile__("int $15");
}