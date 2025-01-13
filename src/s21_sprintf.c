#include <float.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"
#define s21_NULL ((void *)0)
typedef unsigned long s21_size_t;

struct identificator {
  char flag1;
  char flag2;
  int width;
  int precision;
  char length;
  char spec;
  char string[4000];
  char prec_val[4000];
};

void ft_itoa(int n, char s[]);
void reverse(char s[]);
void ft_unitoa(unsigned int n, char s[]);
int ft_atoi(char *str);
char *ft_ftoa(char *s, double n, int prec);
int get_identificator(char *str, struct identificator *init);
int set_identificator(char *str, struct identificator *segment);
int string_from_chart(struct identificator *init, char ch);
int string_from_string(struct identificator *init, char *string);
int ft_str_from_int(struct identificator *init, long int nb);
int ft_double_from_string(struct identificator *init, double ld);
int ft_str_from_unint(struct identificator *init, unsigned int nb);
int ft_get_precision_value(struct identificator *init, char *str);
int ft_first_symbol(struct identificator *init);
char *s21_strcpy(char *dest, const char *src);
s21_size_t s21_strlen(const char *str);
char *s21_strcat(char *dest, const char *src);
s21_size_t s21_strcspn(const char *str1, const char *str2);
s21_size_t s21_strspn(const char *str1, const char *str2);
int s21_sprintf(char *str, const char *format, ...);

int s21_sprintf(char *str, const char *format, ...) {
  struct identificator init = {
      -1, -1, -1,   -1,
      -1, -1, "\0", "\0"};
  struct identificator *p_init = &init;
  str[0] = '\0';
  int i = 0;
  char ch;
  char *string;
  long int d;
  double f;
  unsigned int u;
  char draft_segment[1024] = "\0";
  va_list input;
  va_start(input, format);
  while (*format) {
    if (*format == '%') {
      format++;
      s21_strcpy(draft_segment, format);
      format += get_identificator(draft_segment, p_init);
      switch (init.spec) {
        case 'c':
          ch = va_arg(input, int);
          i += string_from_chart(p_init, ch);
          break;
        case 'd':
          d = va_arg(input, long int);
          i += ft_str_from_int(p_init, d);
          break;
        case 'i':
          d = va_arg(input, long int);
          i += ft_str_from_int(p_init, d);
          break;
        case 's':
          string = va_arg(input, char *);
          i += string_from_string(p_init, string);
          break;
        case 'f':
          f = va_arg(input, double);
          i += ft_double_from_string(p_init, f);
          break;
        case 'u':
          u = va_arg(input, unsigned int);
          i += ft_str_from_unint(p_init, u);
          break;
        case '%':
          ch = '%';
          i += string_from_chart(p_init, ch);
          break;
      }
      s21_strcat(str, p_init->string);
    } else {
      str[i] = *format++;
      str[++i] = '\0';
    }
  }
  va_end(input);
  str[i] = '\0';
  return (i);
}
int ft_str_from_unint(struct identificator *init, unsigned int nb) {
  char str_nb[100] = "";
  char *buf = s21_NULL;
  unsigned short int sh_nb;
  int width = 0;
  int i = 0;
  if (init->length == 'h') {
    sh_nb = nb;
    ft_unitoa(sh_nb, str_nb);
  } else {
    ft_unitoa(nb, str_nb);
  }
  int leng_prec = ft_get_precision_value(init, str_nb);
  if (init->width > leng_prec) {
    width = init->width;
    buf = malloc(width * sizeof(char) + 2);
    if (init->flag1 == '-' || init->flag2 == '-') {
      while (i < width) {
        if (i < leng_prec) {
          buf[i] = init->prec_val[i];
          i++;
        } else {
          buf[i++] = ' ';
        }
      }
    } else {
      while (i < width) {
        if (i < width - leng_prec) {
          buf[i++] = ' ';
        } else {
          buf[i] = init->prec_val[i - width + leng_prec];
          i++;
        }
      }
    }
  } else {
    buf = malloc(leng_prec * sizeof(char) + 2);
    while (i < leng_prec) {
      buf[i] = init->prec_val[i];
      i++;
    }
  }
  buf[i] = '\0';
  s21_strcpy(init->string, buf);
  free(buf);
  return i;
}

int ft_double_from_string(struct identificator *init, double ld) {
  char *temp_str = malloc(32 * sizeof(char));
  int width = 0;
  int i = 0;
  ft_ftoa(temp_str, ld, init->precision);
  int leng_prec = ft_get_precision_value(init, temp_str);
  leng_prec = ft_first_symbol(init);
  char *buf;
  if (init->width > leng_prec) {
    width = init->width;
    buf = malloc(width * sizeof(char) + 2);
    if (init->flag1 == '-' || init->flag2 == '-') {
      while (i < width) {
        if (i < leng_prec) {
          buf[i] = init->prec_val[i];
          i++;
        } else {
          buf[i++] = ' ';
        }
      }
    } else {
      while (i < width) {
        if (i < width - leng_prec) {
          buf[i++] = ' ';
        } else {
          buf[i] = init->prec_val[i - width + leng_prec];
          i++;
        }
      }
    }
  } else {
    buf = malloc(leng_prec * sizeof(char) + 2);
    while (i < leng_prec) {
      buf[i] = init->prec_val[i];
      i++;
    }
  }
  buf[i] = '\0';
  s21_strcpy(init->string, buf);
  free(buf);
  free(temp_str);
  return i;
}

int ft_str_from_int(struct identificator *init, long int nb) {
  char str_nb[32] = "";
  short int sh_nb = 0;
  int width = 0;
  int i = 0;
  if (init->length == 'h') {
    sh_nb = nb;
    ft_itoa(sh_nb, str_nb);
  } else {
    ft_itoa(nb, str_nb);
  }
  char *buf;
  int leng_prec = ft_get_precision_value(init, str_nb);
  leng_prec = ft_first_symbol(init);
  if (init->width > leng_prec) {
    width = init->width;
    buf = malloc(width + 2);
    if (init->flag1 == '-' || init->flag2 == '-') {
      while (i < width) {
        if (i < leng_prec) {
          buf[i] = init->prec_val[i];
          i++;
        } else {
          buf[i++] = ' ';
        }
      }
    } else {
      while (i < width) {
        if (i < width - leng_prec) {
          buf[i++] = ' ';
        } else {
          buf[i] = init->prec_val[i - width + leng_prec];
          i++;
        }
      }
    }
  } else {
    buf = malloc(leng_prec + 2);
    while (i < leng_prec) {
      buf[i] = init->prec_val[i];
      i++;
    }
  }
  buf[i] = '\0';
  s21_strcpy(init->string, buf);
  free(buf);
  return i;
}

int ft_get_precision_value(struct identificator *init, char *str) {
  int length = s21_strlen(str);
  int length_res = 0;
  int length_int = 0;
  int leng_float = 0;
  int k = 0;
  if (init->precision > length) {
    length_res = init->precision;
  } else {
    length_res = length;
  }
  char *buf = malloc(length_res * sizeof(char) + 1000);
  int i = 0;
  int j = 0;
  switch (init->spec) {
    case 's':
      length_res = length;
      if (init->precision > -1) {
        if (init->precision < length) {
          length_res = init->precision;
        }
      }
      while (i < length_res) {
        buf[i] = str[i];
        i++;
      }
      buf[i] = '\0';
      break;
    case 'd':
      if (init->precision > -1) {
        if (init->precision == 0 && str[i] == '0') {
          buf[i] = '\0';
          break;
        }
        if (init->precision > length) {
          length_res = init->precision;
        } else {
          length_res = length;
        }
        if (str[i] == '-') {
          if (init->precision >= length) {
            length_res++;
          }
          buf[i++] = '-';
          j++;
        }
        while (k < length_res) {
          if (k < length_res - length) {
            buf[i] = '0';
          } else {
            buf[i] = str[j++];
          }
          i++;
          k++;
        }
      } else {
        while (i < length) {
          buf[i] = str[i];
          i++;
        }
      }
      buf[i] = '\0';
      break;
    case 'i':
      if (init->precision > -1) {
        if (init->precision == 0 && str[i] == '0') {
          buf[i] = '\0';
          break;
        }
        if (init->precision > length) {
          length_res = init->precision;
        } else {
          length_res = length;
        }
        if (str[i] == '-') {
          if (init->precision >= length) {
            length_res++;
          }
          buf[i++] = '-';
          j++;
        }
        while (k < length_res) {
          if (k < length_res - length) {
            buf[i] = '0';
          } else {
            buf[i] = str[j++];
          }
          i++;
          k++;
        }
      } else {
        while (i < length) {
          buf[i] = str[i];
          i++;
        }
      }
      buf[i] = '\0';
      break;
    case 'f':
      length_int = s21_strcspn(str, ".");
      if (init->precision < 0) {
        init->precision = 6;
      }
      if (init->precision == 0) {
        length = length_int;
      } else {
        leng_float = length - length_int - 1;
      }
      if (init->precision > leng_float) {
        length = init->precision + length_int + 1;
        while (i < length) {
          if (i < length_int + leng_float + 1) {
            buf[i] = str[i];
          } else {
            buf[i] = '0';
          }
          i++;
        }
      } else {
        while (i < length) {
          buf[i] = str[i];
          i++;
        }
      }
      buf[i] = '\0';
      break;
    case 'u':
      if (init->precision > -1) {
        if (init->precision == 0 && str[i] == '0') {
          buf[i] = '\0';
          break;
        }
        if (init->precision > length) {
          length_res = init->precision;
        } else {
          length_res = length;
        }
        while (k < length_res) {
          if (k < length_res - length) {
            buf[i] = '0';
          } else {
            buf[i] = str[j++];
          }
          i++;
          k++;
        }
      } else {
        while (i < length) {
          buf[i] = str[i];
          i++;
        }
      }
      buf[i] = '\0';
      break;
  }
  s21_strcpy(init->prec_val, buf);
  free(buf);
  return i;
}

int string_from_string(struct identificator *init, char *string) {
  char str[1000];
  int width = 0;
  int leng_prec = ft_get_precision_value(init, string);
  int i = 0;
  if (init->width > leng_prec) {
    width = init->width;
    if (init->flag1 == '-' || init->flag2 == '-') {
      while (i < width) {
        if (i < leng_prec) {
          str[i] = init->prec_val[i];
          i++;
        } else {
          str[i++] = ' ';
        }
      }
    } else {
      while (i < width) {
        if (i < width - leng_prec) {
          str[i++] = ' ';
        } else {
          str[i] = init->prec_val[i - width + leng_prec];
          i++;
        }
      }
    }
  } else {
    while (i < leng_prec) {
      str[i] = init->prec_val[i];
      i++;
    }
  }
  str[i] = '\0';
  s21_strcpy(init->string, str);
  return i;
}

int string_from_chart(struct identificator *init, char ch) {
  char str[1000];
  int width = 0;
  int i = 0;
  if (init->width > 1) {
    width = init->width;
    if (init->flag1 == '-' || init->flag2 == '-') {
      str[i] = ch;
      i++;
      while (i < width) {
        str[i] = ' ';
        i++;
      }
    } else {
      while (i < width - 1) {
        str[i] = ' ';
        i++;
      }
      str[i++] = ch;
    }
  } else {
    str[i] = ch;
    i++;
  }
  str[i] = '\0';
  s21_strcpy(init->string, str);
  return i;
}

int get_identificator(char *str, struct identificator *init) {
  s21_size_t i = 0;
  s21_size_t len = s21_strlen(str);
  s21_size_t len_segment =
      s21_strcspn(str, "cdsfui%");
  char *segment = malloc(len_segment * sizeof(char) + 1000);
  init->flag1 = -1;
  init->flag2 = -1;
  init->width = -1;
  init->precision = -1;
  init->length = -1;
  if (len_segment == s21_strspn(str, "-+. lh1234567890")) {
    init->spec = str[len_segment];
    if (s21_strcspn(str, "lh") == len_segment - 1) {
      init->length = str[len_segment - 1];
    }
    if (len_segment < len) {
      while (i <= len_segment) {
        segment[i] = str[i];
        i++;
      }
      segment[i] = '\0';
      set_identificator(
          segment,
          init);
    }
  }
  free(segment);
  return i;
}

int set_identificator(char *str, struct identificator *segment) {
  int i = 0;
  int point_length;
  char width[1000] = "\0";
  char precision[1000] = "\0";
  int str_len;
  str_len = s21_strlen(str);
  point_length = s21_strcspn(str, ".");
  if (str_len > 1) {
    if (*str == '-' || *str == '+' || *str == ' ' || *str == '0') {
      segment->flag1 = *str;
      str++;
    }
    if (*str == '-' || *str == '+' || *str == ' ' || *str == '0') {
      segment->flag2 = *str;
      str++;
    }
    if (point_length < str_len) {
      while (*str != '.') {
        width[i] = *str++;
        i++;
      }
      str++;
      segment->width = ft_atoi(width);
      i = 0;
      while (*str) {
        precision[i] = *str++;
        i++;
      }
      segment->precision = ft_atoi(precision);
    } else {
      while (i < str_len - 1) {
        width[i] = *str++;
        i++;
      }
      segment->width = ft_atoi(width);
    }
  }
  return 0;
}

int ft_first_symbol(struct identificator *init) {
  int length = 0;
  char buf[32] = "";
  if (init->flag1 == '+' || init->flag2 == '+') {
    if (init->prec_val[0] != '-') {
      buf[0] = '+';
    }
  } else {
    if (init->flag1 == ' ' || init->flag2 == ' ') {
      if (init->prec_val[0] != '-') {
        buf[0] = ' ';
      }
    }
  }
  s21_strcat(buf, init->prec_val);
  s21_strcpy(init->prec_val, buf);
  length = s21_strlen(init->prec_val);
  return (length);
}

void ft_itoa(int n, char s[]) {
  long int sign = 0;
  int i = 0;
  if (n == -2147483648) {
    n += 1;
    if ((sign = n) < 0)
      n = -n;
    do {
      s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    s[0] = '8';
  } else {
    if ((sign = n) < 0) n = -n;
    do {
      s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
  }
  if (sign < 0) s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}

void reverse(char s[]) {
  int i, j;
  char c;

  for (i = 0, j = s21_strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

void ft_unitoa(unsigned int n, char s[]) {
  int i = 0;
  do {
    s[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);
  s[i] = '\0';
  reverse(s);
}

int ft_atoi(char *str) {
  int sign;
  int num;

  sign = 1;
  num = 0;
  while ((*str == ' ') || (*str == '\t') || (*str == '\n') || (*str == '\v') ||
         (*str == '\f') || (*str == '\r'))
    str++;
  if (*str == '-') sign = -1;
  while ((*str == '-') || (*str == '+')) str++;
  while (*str >= '0' && *str <= '9') {
    num = (num * 10) + ((int)*str - '0');
    str++;
  }
  return (num * sign);
}

char *ft_ftoa(char *s, double n, int prec) {
  double precision = 0.00000000000001;
  if (n == 0.0 || n == 0) {
    s21_strcpy(s, "0.0");
  } else {
    int digit, m, check_int;
    check_int = n;
    double check_res = n / check_int;
    if (check_res == 1) {
      precision = 0;
    } else {
      if (prec < 0) {
        prec = 6;
      }
      precision = 1 / (pow(10.0, prec));
    }
    char *c = s;
    int neg = (n < 0);
    if (neg) n = -n;
    m = log10(n);

    if (neg) *(c++) = '-';
    while (n > precision || m >= 0) {
      double weight = pow(10.0, m);
      if (weight > 0) {
        if (log10(n) < -(prec - 1)) {
          digit = round(n / weight);
        } else {
          digit = floorf(n / weight);
        }
        n -= (digit * weight);
        *(c++) = '0' + digit;
      }
      if (m == 0 && n > 0) {
        *(c++) = '.';
      }
      m--;
    }
    if (precision == 0) {
      *(c++) = '.';
      *(c++) = '0';
    }
    *(c) = '\0';
  }
  return s;
}
