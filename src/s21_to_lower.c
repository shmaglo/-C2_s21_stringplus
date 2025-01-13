#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

void *s21_to_lower(const char *str) {
    char *temp = s21_NULL;
    int flag = 0;
    if (str == s21_NULL) flag++;
    if (!flag) {
        temp = malloc(sizeof(char) * s21_strlen(str) + 10);
        if (temp == s21_NULL) flag++;
        if (!flag) {
            s21_strcpy(temp, str);
            s21_size_t i = 0;
            while (temp[i] != '\0') {
                if (temp[i] >= 'A' && temp[i] <= 'Z') {
                    temp[i] = temp[i] + 32;
                }
                i++;
            }
        }
    }
    return (!flag) ? temp : s21_NULL;
}
