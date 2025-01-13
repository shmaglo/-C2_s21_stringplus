#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    if ((dest != s21_NULL && src != s21_NULL) || (n != 0)) {
        char *res = dest + s21_strlen(dest);
        s21_strncpy(res, src, n);
    }
    return dest;
}
