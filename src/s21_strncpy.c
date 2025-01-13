#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    s21_size_t i;
    i = 0;
    if (((dest != s21_NULL || src != s21_NULL) && (n != 0)) || (n != 0)) {
        while (src[i] != '\0' && i < n) {
            dest[i] = src[i];
            i++;
        }
        if (s21_strlen(src) < n) dest[i] = '\0';
    }
    return (dest);
}
