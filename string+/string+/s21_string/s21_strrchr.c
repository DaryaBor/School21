#include "../s21_string.h"
char *s21_strrchr(const char *str, int c) {
  const char *pos = S21_NULL;
  s21_size_t len = s21_strlen(str);
  for (s21_size_t i = 0; i <= len; i++) {
    if (str[i] == c) {
      pos = &str[i];
    }
  }
  return (char *)pos;
}