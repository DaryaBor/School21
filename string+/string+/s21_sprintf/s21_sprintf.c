#include "../s21_string.h"
#define ACCURACY 0
#define WIDTH 1

void width(int *str_i, char *str, opts *opt, int persent_index) {
  int count = opt->width - ((*str_i) - persent_index);
  char width_ch = (opt->zero ? '0' : ' ');
  if (count > 0) {
    if (opt->minus) {  // Если по левому краю
      for (int i = 0; i < count; i++) str[(*str_i) + i] = width_ch;
      (*str_i) += count;
    } else {  // Если по правому краю
      for (int i = 0; i < (*str_i) - persent_index; i++)
        str[(*str_i) - 1 - i + count] = str[(*str_i) - 1 - i];
      // Подстановка пробелов
      for (int i = 0; i < count; i++) str[persent_index + i] = width_ch;
      (*str_i) += count;

      // ' ', '+' и '-' стоят перед отступами когда отcтупы - '0',
      // Меняем 0 и {'-', '+', ' '} местами для чисел c флагами + ' ', и
      // отрицательных чисел
      if (width_ch == '0' && s21_strrchr("fd", opt->specifier) &&
          s21_strrchr("-+ ", str[persent_index + count])) {
        str[persent_index] = str[persent_index + count];
        str[persent_index + count] = width_ch;
      }
    }
  }
}

void flags(int *i, opts *opt, const char *format) {
  while (1) {
    (*i)++;
    if (format[*i] == '-')
      opt->minus = 1;
    else if (format[*i] == '+')
      opt->plus = 1;
    else if (format[*i] == ' ')
      opt->space = 1;
    else if (format[*i] == '#')
      opt->hash = 1;
    else if (format[*i] == '0')
      opt->zero = 1;
    else
      break;
  }
}

int get_number(int *i,
               const char *format) {  // обработка числа в строке форматирования
  int number = 0;
  int num_len = 0;
  int digit = 1;
  for (; '0' <= format[(*i) + num_len] && format[(*i) + num_len] <= '9';
       num_len++) {
    number = number * digit;
    number += format[(*i) + num_len] - '0';
    digit = 10;
    // printf("%c num\n",format[(*i)]);
  }
  (*i) += num_len;
  return number;
}

void width_or_accuracy(int *i, opts *opt, const char *format, va_list *pointer,
                       int flag) {  // обработка точности и ширины по флагу
  if (format[*i] >= '0' && format[*i] <= '9') {
    if (flag == 1) {
      opt->width = get_number(i, format);
    } else {
      opt->accuracy = get_number(i, format);
    }

  } else if (format[*i] == '*') {
    if (flag == 1) {
      opt->width = va_arg(*pointer, int);
    } else {
      opt->accuracy = va_arg(*pointer, int);
    }
    (*i)++;
  }
}

void get_accuracy(int *i, opts *opt, const char *format,
                  va_list *pointer) {  // обработка точности
  if (format[*i] == '.') {
    opt->accuracy = 0;
    (*i)++;
    width_or_accuracy(i, opt, format, pointer, ACCURACY);
  }
}

void get_length(int *i, opts *opt, const char *format) {  // обработка длины
  while (1) {
    if (format[*i] == 'h')
      opt->length = 'h';
    else if (format[*i] == 'l')
      opt->length = 'l';
    else if (format[*i] == 'L')
      opt->length = 'L';
    else
      break;
    (*i)++;
  }
}

void get_specifier(int *i, opts *opt,
                   const char *format) {  // обработка спецификатора
  if (s21_strrchr("cdieEfFgGosuxXpn%", format[*i])) {
    opt->specifier = format[*i];
    (*i)++;
  }
}

void parce(int *i, opts *opt, const char *format, va_list *pointer) {
  flags(i, opt, format);
  width_or_accuracy(i, opt, format, pointer, WIDTH);
  get_accuracy(i, opt, format, pointer);
  get_length(i, opt, format);
  get_specifier(i, opt, format);
  (*i)--;
}

void push_specifier(int *str_i, char *str, opts *opt, va_list *pointer) {
  int present_index = *str_i;
  if (opt->specifier == 'c') {
    specifier_c(str_i, str, pointer);
  } else if (opt->specifier == 's') {
    specifier_s(str_i, str, opt, pointer);
  } else if (opt->specifier == 'd' || opt->specifier == 'i') {
    specifier_d(str_i, str, opt, pointer);
  } else if (opt->specifier == 'e' || opt->specifier == 'E' ||
             opt->specifier == 'f' || opt->specifier == 'g' ||
             opt->specifier == 'G') {
    long double d;
    init_length(&d, opt, pointer);
    if (opt->specifier == 'e' || opt->specifier == 'g')
      specifier_e(str_i, str, opt, 0, d);
    else if (opt->specifier == 'E' || opt->specifier == 'G')
      specifier_e(str_i, str, opt, 1, d);
    else if (opt->specifier == 'f')
      specifier_f(str_i, str, opt, d);
  } else if (opt->specifier == 'o') {
    specifier_o(str_i, str, opt, pointer);
  } else if (opt->specifier == 'u') {
    specifier_u(str_i, str, opt, pointer);
  } else if (opt->specifier == 'x') {
    specifier_x(str_i, str, opt, pointer, 0);
  } else if (opt->specifier == 'X') {
    specifier_x(str_i, str, opt, pointer, 1);
  } else if (opt->specifier == 'p')
    specifier_p(str_i, str, opt, pointer);
  else if (opt->specifier == 'n')
    specifier_n(str_i, pointer);
  else if (opt->specifier == '%')
    specifier_percent(str_i, str);
  ;
  width(str_i, str, opt, present_index);
}

int s21_sprintf(char *str, const char *format, ...) {
  int str_len = 0;
  va_list pointer;
  va_start(pointer, format);
  for (int i = 0; i < (int)s21_strlen(format); i++) {
    opts opt = {0, 0, 0, 0, 0, 0, 0, 0, -1, 0};
    if (format[i] == '%') {
      parce(&i, &opt, format, &pointer);
      push_specifier(&str_len, str, &opt,
                     &pointer);  // тут функция для обработки спецификаторов
    } else {
      str[str_len] = format[i];  // Запись в буфер
      str_len++;
    }
    str[str_len] = '\0';
  }
  va_end(pointer);
  return str_len;
}

// int main(){
//     char str[60];
//     //char lk[10]="kelloup";
//    //int f=12345;
//     //char line='v';
//     //int count;
//     s21_sprintf(str,"%.e", 1215.45);
//     printf("%s\n", str);
//     return 0;
// }