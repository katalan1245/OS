#ifndef MEM_H
#define MEM_H

#include <stdint.h>
#include <stddef.h>

void memcpy(void *destination, void *source, size_t n);
void memset(void *mem, uint8_t data, size_t n);
int memcmp(void *mem1, void *mem2, size_t n);
void memmove(void *destination, void *source, size_t n);
void memrev(void *mem, size_t n);

#endif