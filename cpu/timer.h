#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

#define SYSTEM_TIMER_FREQUENCY 100
#define TIMER_COMMAND_PORT 0x43
#define TIMER_COMMAND_BYTE 0x36
#define PIT_FREQUENCY 1193180
#define FREQUENCY_DIVISOR_PORT 0x40
#define MAX_FREQUENCY 65536
/* Bits 6-7: 00 = channel 0
 * Bits 4-5: 11 = Access mode: lobyte/hibyte
 * Bits 1-3: 110 = Operating mode: mode 2 (rate generator)
 * Bit 0: 0 = 16-bit binary
 * 0x36 = 0011 1100
 */
#define COMMAND_BYTE 0x36

void init_timer(uint32_t frequency);

#endif