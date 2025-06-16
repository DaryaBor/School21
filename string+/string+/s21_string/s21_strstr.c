#include "../s21_string.h"

int match(char const *a, char const *b) {
  while (*b)
    if (*a++ != *b++) return 0;
  return 1;
}

char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t len1 = s21_strlen(haystack);
  s21_size_t len2 = s21_strlen(needle);

  for (s21_size_t i = 0; i + len2 <= len1; i++)
    if (match(haystack + i, needle)) return (char *)haystack + i;
  return S21_NULL;
}
