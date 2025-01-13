#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
    s21_size_t k, i;
    k = 0;
    for (i = 0; i < s21_strlen(str1); i++) {
        for (s21_size_t j = 0; j < s21_strlen(str2); j++) {
            if (str1[i] == str2[j]) k++;
        }
        if (k > 0) break;
    }
    return (i);
}
