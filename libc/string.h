#ifndef STRING_H
#define STRING_H

#include <stdint.h>
#include <stddef.h>

size_t strlen(char *str);
void strcpy(char *str1, char *str2);
void strrev(char *str);
void backspace(char *str);
void append(char *s, char c);
int strcmp(char *str1, char *str2);
void itoa(int n, char str[]);

#endif