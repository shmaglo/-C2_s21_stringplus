#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
    s21_size_t length = s21_strlen(needle);
    s21_size_t i = 0;
    int flag = 0;
    if ((haystack != s21_NULL) || s21_strlen(needle) != 0) {
        for (i = 0; haystack[i] != '\0'; i++) {
            if (s21_strncmp((haystack + i), needle, length) == 0) {
                flag = 1;
                break;
            }
        }
    }
    return (flag == 0) ? s21_NULL : (char *)haystack + i;
}
