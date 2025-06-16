#include "../s21_string.h"

/* вычисляет длину строки до первого вхождения символа, присутсвующего во второй
 * строке*/
s21_size_t s21_strcspn(char *str1, char *str2) {
  s21_size_t num = 0;
  int flag = 0;
  for (s21_size_t i = 0; !flag && i < s21_strlen(str1); ++i) {
    for (s21_size_t j = 0; !flag && j < s21_strlen(str2); ++j)
      if (str1[i] == str2[j]) flag = 1;
    if (!flag) num++;
  }
  return num;
}