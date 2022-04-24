#ifndef MEM_H
#define MEM_H

#include <stddef.h>
#include <stdint.h>

void memcpy(void *destination, void *source, uint32_t n);
void memset(void *mem, uint8_t data, uint32_t n);
int memcmp(void *mem1, void *mem2, uint32_t n);
void memrev(void *mem, uint32_t n);

#endif