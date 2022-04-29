#ifndef MEM_H
#define MEM_H

#include "../cpu/types.h"

void memcpy(void *destination, void *source, uint32 n);
void memset(void *mem, uint8 data, uint32 n);
int memcmp(void *mem1, void *mem2, uint32 n);
void memrev(void *mem, uint32 n);

#endif