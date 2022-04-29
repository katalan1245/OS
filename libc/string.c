#include "string.h"
#include "mem.h"

uint32 strlen(char *str)
{
    uint32 len = 0;
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

void append(char *str, char n) {
    uint32 len = strlen(str);
    str[len] = n;
    str[len+1] = '\0';
}

void backspace(char *str) {
    uint32 len = strlen(str);
    if(len == 0)
        return;
    str[len-1] = '\0';
}

/**
 * convert number `n` to string of the number
 */
void itoa(int n, char str[])
{
    int i, sign;
    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do
        str[i++] = n % 10 + '0';
    while ((n /= 10) > 0);

    if (sign < 0)
        str[i++] = '-';
    str[i] = '\0';

    /* reverse the string */
    strrev(str);
}