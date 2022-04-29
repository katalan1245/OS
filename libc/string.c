#include "string.h"
#include "mem.h"

size_t strlen(char *str)
{
    uint32_t len = 0;
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
    int i;
    for (i = 0; str1[i] == str2[i]; i++)
        if (str1[i] == 0)
            return 0;
    return str1[i] - str2[i];
}

/**
 * reverse the string
 */
void strrev(char *str) { memrev(str, strlen(str)); }

void append(char *str, char n)
{
    size_t len = strlen(str);
    str[len] = n;
    str[len + 1] = '\0';
}

void backspace(char *str)
{
    size_t len = strlen(str);
    if (len == 0)
        return;
    str[len - 1] = '\0';
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