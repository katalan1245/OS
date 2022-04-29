#include "mem.h"

/**
 * copy the first n bytes from source to destination
 */
void memcpy(void *destination, void *source, size_t n)
{
    size_t i;
    uint8_t *tdestination = (uint8_t *)destination;
    uint8_t *tsource = (uint8_t *)source;
    for (i = 0; i < n; i++)
        *(tdestination + i) = *(tsource + i);
}

/**
 * set `n` bytes in `destination` with `data`
 */
void memset(void *destination, uint8_t data, size_t n)
{
    uint8_t *temp = (uint8_t *)destination;
    while (n--)
        *temp++ = data;
}

/**
 * compare the first n bytes of mem1 and mem2
 */
int memcmp(void *mem1, void *mem2, size_t n)
{
    uint8_t *tmem1 = (uint8_t *)mem1;
    uint8_t *tmem2 = (uint8_t *)mem2;

    while (n-- > 0)
        if (*tmem1++ != *tmem2++)
            return *(--tmem1) - *(--tmem2);

    return 0;
}

/**
 * copy n bytes from src to dest, however it is safe approach if the addresses are overlapping
 */
void memmove(void *destination, void *source, size_t n) {
    uint8_t temp[n];
    memcpy(temp, source, n);
    memcpy(destination, temp, n);
}
/**
 * reverse first n bytes of the memory
 */
void memrev(void *mem, size_t n)
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