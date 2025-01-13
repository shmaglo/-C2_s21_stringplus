#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
    static char *memory;
    char *token = s21_NULL;
    if (str != s21_NULL) {
        memory = str;
        while (*memory && s21_strchr(delim, *memory)) {
            memory = memory + 1;
        }
    }
    if (memory && *memory) {
        str = memory;
        while (*memory && (s21_strchr(delim, *memory) == s21_NULL)) {
            memory = memory + 1;
        }
        while (*memory && s21_strchr(delim, *memory)) {
            *memory++ = '\0';
        }
        token = str;
    }
    return token;
}
