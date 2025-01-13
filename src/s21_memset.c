#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
    char *tmp_mem = (char *)str;
    while (n > 0) {
        *tmp_mem = c;
        tmp_mem++;
        n--;
        }
    return str;
}
