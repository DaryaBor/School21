#ifndef S21_STRING_H
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define s21_size_t unsigned long
#define S21_NULL ((void *)0)  // 0 привели к void*

#define SUITE_NAME "Unit"
#define TCASE_NAME "Tests"
/*stirng*/
// me
s21_size_t s21_strlen(const char *str);
s21_size_t s21_strcspn(char *str1, char *str2);
char *s21_strtok(char *str, const char *delims);
char *s21_strerror(int num_err);
// Dasha
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
// Artem
char *s21_strncat(char *dest, const char *src, s21_size_t n);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strchr(const char *str, int c);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);

// Diana
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);

/*sprintf*/
typedef struct {
  int minus;       // 0 или 1
  int plus;        // 0 или 1
  int hash;        // 0 или 1
  int zero;        // 0 или 1
  int space;       // 0 или 1
  char length;     // значение длины
  int percent;     // 0 или 1
  int width;       // 0 или 1
  int accuracy;    // точность  0 или 1
  char specifier;  // значение спецификатора
} opts;

int match(char const *a, char const *b);

int s21_sprintf(char *str, const char *format, ...);

void specifier_c(int *str_i, char *str, va_list *pointer);
void specifier_s(int *str_i, char *str, opts *opt, va_list *pointer);
void specifier_d(int *str_i, char *str, opts *opt, va_list *pointer);
void specifier_u(int *str_i, char *str, opts *opt, va_list *pointer);
void specifier_o(int *str_i, char *str, opts *opt, va_list *pointer);
void specifier_x(int *str_i, char *str, opts *opt, va_list *pointer, int upper);
void specifier_e(int *str_i, char *str, opts *opt, int upper, long double d);
void specifier_f(int *str_i, char *str, opts *opt, long double d);
void specifier_n(int *str_i, va_list *pointer);
void specifier_p(int *str_i, char *str, opts *opt, va_list *pointer);
void specifier_percent(int *str_i, char *str);

void init_length(void *d, opts *opt, va_list *pointer);

#endif  // S21_STRING_H