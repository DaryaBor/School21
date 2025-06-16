#include "../test.h"

// Спецификатор d
START_TEST(sprintf_d_1) {
  char str1[20];
  char str2[20];
  s21_sprintf(str1, "%d", 123);
  sprintf(str2, "%d", 123);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_d_2) {
  char str1[20];
  char str2[20];
  s21_sprintf(str1, "%d", -200);
  sprintf(str2, "%d", -200);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_d_3) {
  char str1[20];
  char str2[20];
  s21_sprintf(str1, "%d %d %d", 1, -2, 3);
  sprintf(str2, "%d %d %d", 1, -2, 3);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_d_4) {
  char str1[40];
  char str2[40];
  s21_sprintf(str1, "%-1d %-5d %+d %-2d %+d", 100, -2, 3, 4000, -5);
  sprintf(str2, "%-1d %-5d %+d %-2d %+d", 100, -2, 3, 4000, -5);
  ck_assert_str_eq(str1, str2);
}
END_TEST
Suite *test_s21_d(void) {
  Suite *s = suite_create("s21_sprintf_d");
  TCase *tc = tcase_create("s21_sprintf_d_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, sprintf_d_1);
  tcase_add_test(tc, sprintf_d_2);
  tcase_add_test(tc, sprintf_d_3);
  tcase_add_test(tc, sprintf_d_4);

  suite_add_tcase(s, tc);
  return s;
}