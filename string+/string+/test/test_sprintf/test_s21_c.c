// #include "../../s21_string.h"
#include "../test.h"
// Спецификатор с
START_TEST(sprintf_c_1) {
  char str1[20];
  char str2[20];
  s21_sprintf(str1, "%c", 'q');
  sprintf(str2, "%c", 'q');
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_c_2) {
  char str1[20];
  char str2[20];
  s21_sprintf(str1, "  %c  ", 'q');
  sprintf(str2, "  %c  ", 'q');
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_c_3) {
  char str1[20];
  char str2[20];
  s21_sprintf(str1, "%c %c%c ", 'q', ' ', '\n');
  sprintf(str2, "%c %c%c ", 'q', ' ', '\n');
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_c_4) {
  char str1[20];
  char str2[20];
  s21_sprintf(str1, "%c  ", '\0');
  sprintf(str2, "%c  ", '\0');
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite *test_s21_c(void) {
  Suite *s = suite_create("s21_sprintf_c");
  TCase *tc = tcase_create("s21_sprintf_c_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, sprintf_c_1);
  tcase_add_test(tc, sprintf_c_2);
  tcase_add_test(tc, sprintf_c_3);
  tcase_add_test(tc, sprintf_c_4);

  suite_add_tcase(s, tc);
  return s;
}