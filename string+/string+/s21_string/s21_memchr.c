#include <string.h>

#include "../s21_string.h"
void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *s = (unsigned char *)str;
  unsigned char chr = (unsigned char)c;

  char *result = S21_NULL;

  for (s21_size_t i = 0; i < n; ++i) {
    if (s[i] == chr) {
      result = (void *)(s + i);
      break;
    }
  }
  return result;
}