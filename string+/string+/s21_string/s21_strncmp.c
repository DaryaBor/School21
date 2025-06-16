#include "../s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (str1[i] != str2[i] || str1[i] == '\0' || str2[i] == '\0') {
      result = (unsigned char)str1[i] - (unsigned char)str2[i];
      break;
    }
  }
  // if (result != 0) {
  //   result = (result < 0) ? -1 : 1;
  // }
  return result;
}
