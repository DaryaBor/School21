#include "../s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *result = S21_NULL;
  while (*str) {
    if (*str == (char)c) {
      result = (char *)str;
      break;
    }
    str++;
  }
  if (result == S21_NULL && (char)c == '\0') {
    result = (char *)str;
  }
  return result;
}