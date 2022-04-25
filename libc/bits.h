#ifndef BITS_H
#define BITS_H

#include <stdint.h>

uint16_t low_two_bytes(uint32_t address);
uint16_t high_two_bytes(uint32_t address);

#endif