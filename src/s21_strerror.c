#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

char *int_to_char(int errnum, char* err_num_str);

char *s21_strerror(int errnum) {
    const char *error_message[] = ERROR_NAMES;
    static char buf[1024] = {'\0'};
    #if defined(__APPLE__)
       if (errnum < 0 || errnum > EMAX_NUM) {
            char err_mess[100] = "Unknown error: ";
            char *err_num_str = s21_NULL;
            err_num_str = (char *)malloc(100 * sizeof(char));
            int_to_char(errnum, err_num_str);
            s21_strcpy(buf, s21_strcat(err_mess, err_num_str));
            free(err_num_str);
        } else {
            s21_strcpy(buf, error_message[errnum]);
        }
    #elif defined(__linux__)
        if (errnum < 0 || errnum > EMAX_NUM) {
            char err_mess[100] = "Unknown error ";
            char *err_num_str = s21_NULL;
            err_num_str = (char *)malloc(100 * sizeof(char));
            int_to_char(errnum, err_num_str);
            s21_strcpy(buf, s21_strcat(err_mess, err_num_str));
            free(err_num_str);
        } else {
            s21_strcpy(buf, error_message[errnum]);
        }
    #endif
    return buf;
}

char *int_to_char(int errnum, char* err_num_str) {
    char *err_num = s21_NULL;
    err_num = (char *)malloc(100 * sizeof(char));
    int i = 0;
    int buf = errnum;
    if (buf < 0) buf = buf * (-1);
    while (buf > 9) {
        err_num[i] = (buf % 10) + '0';
        buf = buf/10;
        i++;
    }
    err_num[i] = buf + '0';
    if (errnum < 0) {
        err_num[i+1] = '-';
        i++;
    }
    int k = i + 1;
     err_num_str[k] = '\0';
     i = 0;
    while (k > k / 2) {
        err_num_str[i] = err_num[k-1];
        i++;
        k--;
    }
    free(err_num);
    return (err_num_str);
}
