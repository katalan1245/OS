#include "timer.h"
#include "ports.h"
#include "isr.h"
#include "../drivers/screen.h"
#include "../libc/unused.h"


uint32 tick = 0;

static void timer_callback(registers_t regs)
{
    tick++;
    UNUSED(regs);
}

void init_timer(uint32 frequency)
{
    if (frequency == 0)
        frequency = MAX_FREQUENCY;
    /* add timer callback */
    add_interrupt_handler(IRQ0, timer_callback);

    uint32 divisor = PIT_FREQUENCY / frequency;
    uint8 low = (uint8)(divisor & 0xff);
    uint8 high = (uint8)((divisor >> 8) & 0xff);

    port_byte_out(TIMER_COMMAND_PORT, TIMER_COMMAND_BYTE); /* Send the command byte */
    port_byte_out(FREQUENCY_DIVISOR_PORT, low);
    port_byte_out(FREQUENCY_DIVISOR_PORT, high);
}