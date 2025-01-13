#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

int s21_strcmp(const char *str1, const char *str2) {
    int result = 0;
    if (str1 != s21_NULL || str2 != s21_NULL) {
        while (*str1 && (*str1 == *str2)) {
            str1++;
            str2++;
        }
        result = *str1 - *str2;
    }
    return result;
}
