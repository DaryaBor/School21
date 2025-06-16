#include "../s21_string.h"
char *s21_strpbrk(const char *str1, const char *str2) {
  int flag = 0;
  const char *pos = S21_NULL;
  for (int i = 0; str1[i] != '\0'; i++) {
    for (int j = 0; str2[j] != '\0'; j++) {
      if (str1[i] == str2[j]) {
        pos = &str1[i];
        flag = 1;
        break;
      }
    }
    if (flag) {
      break;
    }
  }
  return (char *)pos;
}