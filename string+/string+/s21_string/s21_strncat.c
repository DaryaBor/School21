#include "../s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *result = dest;
  char *dest_ptr = dest;
  while (*dest_ptr) dest_ptr++;  // Перемещаемся в конец строки dest

  for (s21_size_t i = 0; i < n && src[i] != '\0'; i++) {
    *dest_ptr++ = src[i];
  }
  *dest_ptr = '\0';  // Завершаем строку нулевым символом
  return result;
}