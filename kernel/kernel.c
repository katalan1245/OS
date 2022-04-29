#include "../cpu/timer.h"
#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"

void main()
{
    clear_screen();
    isr_install();
    asm volatile("sti");

    //init_timer(10); /* 100hz- 10ms */
    init_keyboard();
}