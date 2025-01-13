#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
    char *result = "";
    if (c != '\0') {
        while (*str && *str != c) str++;
        result = *str ? (char *)str : s21_NULL;
    }
    return result;
}
