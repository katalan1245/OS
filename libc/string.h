#ifndef STRING_H
#define STRING_H

#include <stddef.h>

size_t strlen(char *str);
void strcpy(char *str1, char *str2);
void strrev(char *str);
void memcpy(void *destination, void *source, size_t n);
int memcmp(void *mem1, void *mem2, size_t n);
void memrev(void *mem, size_t n);

#endif