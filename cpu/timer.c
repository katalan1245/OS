#include "timer.h"
#include "ports.h"
#include "isr.h"
#include "../drivers/screen.h"
#include "../libc/unused.h"
#include "../libc/string.h"

uint32_t tick = 0;

static void timer_callback(registers_t *regs)
{
    tick++;
    UNUSED(regs);
}

void init_timer(uint32_t frequency)
{
    if (frequency == 0)
        frequency = MAX_FREQUENCY;
    /* add timer callback */
    add_interrupt_handler(IRQ0, timer_callback);

    uint32_t divisor = PIT_FREQUENCY / frequency;
    uint8_t low = (uint8_t)(divisor & 0xff);
    uint8_t high = (uint8_t)((divisor >> 8) & 0xff);

    port_byte_out(TIMER_COMMAND_PORT, TIMER_COMMAND_BYTE); /* Send the command byte */
    port_byte_out(FREQUENCY_DIVISOR_PORT, low);
    port_byte_out(FREQUENCY_DIVISOR_PORT, high);
}