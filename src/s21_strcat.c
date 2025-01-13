#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

char *s21_strcat(char *dest, const char *src) {
    if (!(dest == s21_NULL) || !(src == s21_NULL)) {
        char *pt = dest;
        while (*pt != '\0') pt++;
        while (*src != '\0') {
            *pt++ = *src;
            src++;
        }
        *pt = '\0';
    }
    return dest;
}
