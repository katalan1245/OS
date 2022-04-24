#include "string.h"

size_t strlen(char *str)
{
    size_t len = 0;
    while (*(str + len++))
        ;
    return len - 1;
}

/**
 * copy the string source to destination
 */
void strcpy(char *destination, char *source) { memcpy(destination, source, strlen(source)); }

int strcmp(char *str1, char *str2)
{
    while (*str1 && (*str1++ == *str2++))
        ;
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

/**
 * reverse the string
 */
void strrev(char *str) { memrev(str, strlen(str)); }