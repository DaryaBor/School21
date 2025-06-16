#include <math.h>
#include <stdarg.h>
#include <stdio.h>

#include "../s21_string.h"

void specifier_c(int *str_i, char *str, va_list *pointer) {
  str[*str_i] = (char)va_arg(*pointer, int);
  (*str_i)++;
}

void specifier_s(int *str_i, char *str, opts *opt, va_list *pointer) {
  char *p = va_arg(*pointer, char *);
  size_t len = s21_strlen(p);
  if (opt->accuracy != -1) {
    if (opt->accuracy < (int)len) {
      len = opt->accuracy;
    }
  }
  if ((int)len != '\0') {
    s21_strncat(str, p, len);
  }
  (*str_i) += len;
}

void init_length(void *d, opts *opt, va_list *pointer) {
  if (s21_strrchr("idoxX", opt->specifier)) {
    if (opt->length == 'h') {
      *((long int *)d) = (short int)va_arg(*pointer, int);
    } else if (opt->length == 'l') {
      *((long int *)d) = va_arg(*pointer, long int);
    } else {
      *((long int *)d) = va_arg(*pointer, int);
    }
  } else if (opt->specifier == 'p') {  // спецификатор p использует x
    *((long int *)d) = va_arg(*pointer, long int);
  } else if (opt->specifier == 'u') {
    if (opt->length == 'h') {
      *((unsigned long int *)d) =
          (unsigned short int)va_arg(*pointer, unsigned int);
    } else if (opt->length == 'l') {
      *((unsigned long int *)d) = va_arg(*pointer, unsigned long int);
    } else {
      *((unsigned long int *)d) = va_arg(*pointer, unsigned int);
    }
  }

  else if (s21_strrchr("eEfgG", opt->specifier)) {
    if (opt->length == 'L') {
      *((long double *)d) = va_arg(*pointer, long double);
    } else {
      *((long double *)d) = va_arg(*pointer, double);
    }
  }
}

void accuracy_int_len(int *str_i, char *str, opts *opt, int *num_len,
                      int d) {  // для целых чисел
  if (d == 0 && opt->accuracy == 0) (*num_len)--;
  int count = opt->accuracy - *num_len;
  for (int i = 0; i < count; i++) str[(*str_i) + i] = '0';
  if (count > 0) (*str_i) += opt->accuracy - *num_len;
}

void flag_hash_for_oxX(int *str_i, char *str, opts *opt) {
  if (opt->hash) {
    str[(*str_i)] = '0';
    (*str_i)++;
    if (opt->specifier == 'x')
      str[(*str_i)] = 'x';
    else if (opt->specifier == 'X')
      str[(*str_i)] = 'X';
    else
      (*str_i)--;
    (*str_i)++;
  }
}

void flag_plus_and_space(int *str_i, char *str, opts *opt) {
  if (opt->plus || opt->space) {
    str[*str_i] = (opt->plus ? '+' : ' ');  // + приорететнее чем ' '
    (*str_i)++;
  }
}

void delete_zeros(int *str_i, char *str) {
  int len = s21_strlen(str);
  for (int i = len - 1; i >= 0 && str[i] == '0';
       i--) {  // Удаление незначимых нулей
    str[i] = '\0';
    (*str_i)--;
  }
  if (str[(*str_i) - 1] == '.') {  // удаление точки если за ней нет символов
    str[(*str_i) - 1] = '\0';
    (*str_i)--;
  }
}

void specifier_d(int *str_i, char *str, opts *opt, va_list *pointer) {
  long int d;
  init_length(&d, opt, pointer);
  if (d < 0) {
    d *= -1;
    str[(*str_i)] = '-';
    (*str_i)++;
  } else {
    flag_plus_and_space(str_i, str, opt);
  }

  int num_len = 1;
  for (long long int step = 10; d >= step; step *= 10) num_len++;
  accuracy_int_len(str_i, str, opt, &num_len, d);
  for (int i = num_len - 1; i >= 0; i--) {
    str[i + (*str_i)] = d % 10 + '0';
    d /= 10;
  }
  (*str_i) += num_len;
}

void specifier_percent(int *str_i, char *str) {
  str[*str_i] = '%';
  (*str_i)++;
}

void specifier_u(int *str_i, char *str, opts *opt, va_list *pointer) {
  unsigned long int d;
  init_length(&d, opt, pointer);
  int num_len = 1;
  for (unsigned long long int step = 10; d >= step; step *= 10) num_len++;
  accuracy_int_len(str_i, str, opt, &num_len, d);
  for (int i = num_len - 1; i >= 0; i--) {
    str[i + (*str_i)] = d % 10 + '0';
    d /= 10;
  }
  (*str_i) += num_len;
}

void specifier_o(int *str_i, char *str, opts *opt, va_list *pointer) {
  long int d;
  init_length(&d, opt, pointer);
  if (d != 0) flag_hash_for_oxX(str_i, str, opt);  // hash для нуля
  if (d < 0)
    d = 4294967295 + 1 +
        d;  // максимальное значение 32-битного беззнакового целого числа
  int num_len = 1;  // число размером меньше одного ввести невозможно
  for (long long int step = 8; d >= step; step *= 8) num_len++;
  accuracy_int_len(str_i, str, opt, &num_len, d);
  for (int i = num_len - 1; i >= 0; i--) {
    str[i + (*str_i)] = d % 8 + '0';
    d /= 8;
  }
  (*str_i) += num_len;
}

void specifier_x(int *str_i, char *str, opts *opt, va_list *pointer,
                 int upper) {
  long int d;
  init_length(&d, opt, pointer);
  int flag_p = opt->specifier == 'p';
  if (opt->specifier == 'p') opt->specifier = 'x';
  if (d != 0 || flag_p)
    flag_hash_for_oxX(str_i, str, opt);  // hash для нуля не работает если не p
  if (d < 0) d = 4294967295 + 1 + d;  // Обработка отрицательных чисел
  int num_len = 1;
  for (long long int step = 16; d >= step; step *= 16) num_len++;
  accuracy_int_len(str_i, str, opt, &num_len, d);
  for (int i = num_len - 1; i >= 0; i--) {
    str[i + (*str_i)] =
        (d % 16 > 9 ? d % 16 + 'a' - upper * 32 - 10 : d % 16 + '0');
    d /= 16;
  }
  (*str_i) += num_len;
}

void specifier_f(int *str_i, char *str, opts *opt, long double d) {
  // Точность по умолчанию
  if (opt->accuracy == -1) opt->accuracy = 6;

  // Обрабоотка минуса
  if (1 / d < 0) {  // 1/d - чтобы отличить негативный ноль от обычного
    d *= -1;
    str[(*str_i)] = '-';
    (*str_i)++;
  } else
    flag_plus_and_space(str_i, str, opt);
  // Записываем целую часть числа
  long long int ceil_part_d = (long long int)d;
  int len_before_point = 1;  // число размером меньше одного ввести невозможно
  for (long long int step = 10; ceil_part_d >= step; step *= 10)
    len_before_point++;
  if (opt->specifier == 'g' || opt->specifier == 'G')
    opt->accuracy = 6 - len_before_point;  // для спецификатора g
  double fraction = d - (long long int)d;  // дробная часть
  // Округление до целого
  if (opt->accuracy == 0 && floor(fraction * 10 + 0.000000001) >= 5)
    ceil_part_d++;
  for (int i = len_before_point - 1; i >= 0; i--) {
    str[i + (*str_i)] = (long long int)ceil_part_d % 10 + '0';
    ceil_part_d /= 10;
  }

  (*str_i) += len_before_point;
  int was_point = 0;  // запоминаем была ли точка, чтобы для спецификатора g
                      // случайно не удалить значимые нули
  if (opt->accuracy || opt->hash) {
    str[(*str_i)] = '.';
    (*str_i)++;
    was_point = 1;
  }
  if (opt->accuracy) {  // если не округлилось до целого
    // Записываем дробную часть числа

    for (int i = 0; i < 6; i++) {
      int num =
          (int)(fraction * 10 + 0.000000001);  // Костыль (0.1*10 = 0.99999999)
      str[i + (*str_i)] = (num) + '0';
      fraction = 10 * fraction - num;  // Округление последнего знака
      if ((i == opt->accuracy - 1) && (floor(fraction * 10 + 0.000000001) >= 5))
        str[i + (*str_i)] += 1;
      if (i == opt->accuracy - 1) break;
    }
    (*str_i) +=
        (opt->accuracy >= 6 ? 6
                            : opt->accuracy);  // Если точность > 6 двигаем на 6

    // Дописываем нули если точность больше
    for (int i = 0; i < opt->accuracy - 6; i++) {
      str[*str_i] = '0';
      (*str_i)++;
    }
  }
  if (was_point && (opt->specifier == 'g' || opt->specifier == 'G'))
    delete_zeros(
        str_i,
        str);  // Для спецификаотра g (удаляем нули только если была точка)
}

void specifier_e(int *str_i, char *str, opts *opt, int big, long double d) {
  long double old_d = d;  // сохраняем старое значение если будет необходимо
                          // вызвать флаг f для спецификатора g
  // Точность по умолчанию
  if (opt->accuracy == -1) opt->accuracy = 6;
  if (opt->specifier == 'g' || opt->specifier == 'G')
    opt->accuracy = 5;  // для спецификатора g
  // Обрабоотка минуса
  if (1 / d < 0) {  // 1/d - чтобы отличить негативный ноль от обычного
    d *= -1;
    str[(*str_i)] = '-';
    (*str_i)++;
  } else {
    flag_plus_and_space(str_i, str, opt);
  }

  // Нормализация
  int exp = 0;
  while (d >= 10) {
    d /= 10;
    exp++;
  }
  while (d < 1 && d != 0.) {
    d *= 10;
    exp--;
  }
  // СПЕЦИФИКАТОР G
  if ((opt->specifier == 'g' || opt->specifier == 'G') && exp >= -4 &&
      exp <= 5) {
    specifier_f(
        str_i, str, opt,
        old_d);  // Используем f для g если экспонента в определенном диапазоне
  } else {
    // Записываем целую часть числа
    long long int ceil_part_d = (int)d;
    double fraction = d - (long long int)d;  // дробная часть
    // Округление до целого
    if (opt->accuracy == 0 && floor(fraction * 10 + 0.000000001) >= 5)
      ceil_part_d++;
    // Нормализация в случае например %.0e 999999.7
    while (ceil_part_d >= 10) {
      ceil_part_d /= 10;
      d /= 10;
      exp++;
    }
    str[(*str_i)] = (int)ceil_part_d % 10 + '0';
    (*str_i)++;
    if (opt->accuracy || opt->hash) {
      str[(*str_i)] = '.';
      (*str_i)++;
    }
    if (opt->accuracy) {  // если не округлилось до целого
      // Записываем дробную часть числа
      for (int i = 0; i < 6; i++) {
        int num = (int)(fraction * 10 +
                        0.000000001);  // Костыль (0.1*10 = 0.99999999)
        str[i + (*str_i)] = (num) + '0';
        fraction = 10 * fraction - num;
        // Округление последнего знака
        if ((i == opt->accuracy - 1) &&
            (floor(fraction * 10 + 0.000000001) >= 5))
          str[i + (*str_i)] += 1;
        if (i == opt->accuracy - 1) break;
      }
      (*str_i) += (opt->accuracy >= 6
                       ? 6
                       : opt->accuracy);  // Если точность > 6 двигаем на 6

      // Дописываем нули если точность больше
      for (int i = 0; i < opt->accuracy - 6; i++) {
        str[*str_i] = '0';
        (*str_i)++;
      }
      if (opt->specifier == 'g' || opt->specifier == 'G')
        delete_zeros(
            str_i,
            str);  // Для спецификаотра g (удаляем нули перед записи e+...)
    }
    str[*str_i] = 'e' - 32 * big;
    str[*str_i + 1] = exp >= 0 ? '+' : '-';  // знак
    if (exp < 0) exp *= -1;
    (*str_i) += 2;
    if (exp < 10) {
      str[*str_i] = '0';
      (*str_i)++;
    }
    // Записываем степень
    int exp_len = 1;
    for (long long int step = 10; exp >= step; step *= 10) exp_len++;
    for (int i = exp_len - 1; i >= 0; i--) {
      str[i + (*str_i)] = exp % 10 + '0';
      exp /= 10;
    }
    (*str_i) += exp_len;
  }
}

void specifier_p(int *str_i, char *str, opts *opt, va_list *pointer) {
  opt->hash = 1;
  specifier_x(str_i, str, opt, pointer, 0);
}

void specifier_n(int *str_i, va_list *pointer) {
  int *n = va_arg(*pointer, int *);
  *n = *str_i;
}