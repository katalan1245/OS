#include "mem.h"

/**
 * copy the first n bytes from source to destination
 */
void memcpy(void *destination, void *source, uint32_t n)
{
    int i;
    char *tdestination = (char *)destination;
    char *tsource = (char *)source;
    for (i = 0; i < n; i++)
        *(tdestination + i) = *(tsource + i);
}

/**
 * set `n` bytes in `destination` with `data`
 */
void memset(void *destination, uint8_t data, uint32_t n)
{
    uint8_t *temp = (uint8_t *)destination;
    while (n--)
        *temp++ = data;
}

/**
 * compare the first n bytes of mem1 and mem2
 */
int memcmp(void *mem1, void *mem2, uint32_t n)
{
    uint8_t *tmem1 = (uint8_t *)mem1;
    uint8_t *tmem2 = (uint8_t *)mem2;

    while (n-- > 0)
        if (*tmem1++ != *tmem2++)
            return *(--tmem1) - *(--tmem2);

    return 0;
}

/**
 * reverse first n bytes of the memory
 */
void memrev(void *mem, uint32_t n)
{
    int i = 0, j = n - 1;
    uint8_t *tmem = (uint8_t *)mem;
    for (; i < j; i++, j--)
    {
        uint8_t temp = tmem[i];
        tmem[i] = tmem[j];
        tmem[j] = temp;
    }
}