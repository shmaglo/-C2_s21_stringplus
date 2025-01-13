#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
    s21_size_t i;
    void *result = s21_NULL;
    char *s1 = (char *)str;
    for (i = 0; i < n; i++) {
        if (s1[i] == c) {
            result = &(s1[i]);
            break;
        }
    }
    return result;
}
