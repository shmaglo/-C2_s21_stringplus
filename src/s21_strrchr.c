#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
    char *output = s21_NULL;
    if (str[0] != '\0') {
        s21_size_t i = 0;
        int flag = 0;
        i = s21_strlen(str);
        while (flag == 0) {
            if (c == '\0') {
                output = (char*)&str[i];
                flag = 1;
            } else {
                for (s21_size_t j = 0; j < s21_strlen(str); j++) {
                    if (str[j] == c) {
                        i = j;
                    }
                }
                if (str[i] == '\0') {
                    flag = 1;
                } else {
                    output = (char*)&str[i];
                    flag = 1;
                }
            }
        }
    } else {
        if (c == '\0') {
            output = (char*)&str[0];
        }
    }
    return output;
}
