#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
    s21_size_t count = 0;
    s21_size_t k = 0;
    s21_size_t i = 0;
    if (str1 != s21_NULL || s21_strlen(str2) != 0) {
        for (i = 0; i < s21_strlen(str1); i++) {
            for (s21_size_t j = 0; j < s21_strlen(str2); j++) {
                if (str1[i] == str2[j]) {
                    count++;
                }
            }
            if (count == 0) {
                break;
            } else {
                k++;
            }
            count = 0;
        }
    }
    return k;
}
