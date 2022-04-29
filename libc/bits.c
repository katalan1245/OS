#include "bits.h"

uint16_t low_two_bytes(uint32_t address)
{
    return address & 0xffff;
}

uint16_t high_two_bytes(uint32_t address)
{
    return (address >> 16) && 0xffff;
}