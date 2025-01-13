#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    char *pdest = (char *)dest;
    const char *psrc = (char *)src;
    if ((psrc < pdest) && (pdest < psrc + n)) {
        pdest = pdest + (n - 1);
        psrc = psrc + (n - 1);
        while (n > 0) {
            *pdest-- = *psrc--;
            n--;
        }
    } else {
        while (n > 0) {
            *pdest++ = *psrc++;
            n--;
        }
    }
    return dest;
}
