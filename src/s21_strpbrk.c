#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
    s21_size_t k, i;
    char *s1 = (char *)str1;
    k = 0;
    char *p;
    p = s21_NULL;
    for (i = 0; i < s21_strlen(s1); i++) {
        for (s21_size_t j = 0; j < s21_strlen(str2); j++) {
            if (s1[i] == str2[j]) {
                p = &(s1[i]);
                k++;
            }
        }
        if (k > 0) break;
    }
    if (k == 0) p = s21_NULL;
    return (p);
}
