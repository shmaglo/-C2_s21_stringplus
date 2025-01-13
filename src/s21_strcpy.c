#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

char *s21_strcpy(char *dest, const char *src) {
    s21_size_t i = 0;
    if (dest != s21_NULL || src != s21_NULL) {
        while (src[i] != '\0') {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }
  return (dest);
}
