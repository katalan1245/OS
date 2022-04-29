#include "mem.h"

/**
 * copy the first n bytes from source to destination
 */
void memcpy(void *destination, void *source, uint32 n)
{
    uint32 i;
    char *tdestination = (char *)destination;
    char *tsource = (char *)source;
    for (i = 0; i < n; i++)
        *(tdestination + i) = *(tsource + i);
}

/**
 * set `n` bytes in `destination` with `data`
 */
void memset(void *destination, uint8 data, uint32 n)
{
    uint8 *temp = (uint8 *)destination;
    while (n--)
        *temp++ = data;
}

/**
 * compare the first n bytes of mem1 and mem2
 */
int memcmp(void *mem1, void *mem2, uint32 n)
{
    uint8 *tmem1 = (uint8 *)mem1;
    uint8 *tmem2 = (uint8 *)mem2;

    while (n-- > 0)
        if (*tmem1++ != *tmem2++)
            return *(--tmem1) - *(--tmem2);

    return 0;
}

/**
 * reverse first n bytes of the memory
 */
void memrev(void *mem, uint32 n)
{
    int i = 0, j = n - 1;
    uint8 *tmem = (uint8 *)mem;
    for (; i < j; i++, j--)
    {
        uint8 temp = tmem[i];
        tmem[i] = tmem[j];
        tmem[j] = temp;
    }
}