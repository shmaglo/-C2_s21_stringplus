#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    s21_size_t i = 0;
    int result = 0;
    if (((str1 != s21_NULL || str2 != s21_NULL) && (n != 0)) || (n != 0)) {
        while (*str1 && (*str1 == *str2) && (i < n)) {
            i++;
            if (i < n) {
            str1++;
            str2++;
            }
        }
        result = *str1 - *str2;
    }
    return result;
}
