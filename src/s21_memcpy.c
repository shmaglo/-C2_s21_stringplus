#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    void *res = dest;
    while (n > 0) {
        *(char *)dest = *(char *)src;
        dest = dest + 1;
        src = src + 1;
        n--;
    }
    return res;
}
