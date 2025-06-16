#include "../test.h"
// Спецификатор f
START_TEST(sprintf_f_1) {
  char str1[20];
  char str2[20];
  s21_sprintf(str1, "%f", 12.3);
  sprintf(str2, "%f", 12.3);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_f_2) {
  char str1[20];
  char str2[20];
  s21_sprintf(str1, "%f", -20.0);
  sprintf(str2, "%f", -20.0);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_f_3) {
  char str1[40];
  char str2[40];
  s21_sprintf(str1, "%f %f %f", 1.12345678, -2.12345678, 3.12345678);
  sprintf(str2, "%f %f %f", 1.12345678, -2.12345678, 3.12345678);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_f_4) {
  char str1[80];
  char str2[80];
  s21_sprintf(str1, "%-1f %-5f %+f %-2f %+f", 100.00000000, -21234.87654321,
              3.0, 4000.123456, -5.23456789);
  sprintf(str2, "%-1f %-5f %+f %-2f %+f", 100.00000000, -21234.87654321, 3.0,
          4000.123456, -5.23456789);
  ck_assert_str_eq(str1, str2);
}
END_TEST
Suite *test_s21_f(void) {
  Suite *s = suite_create("s21_sprintf_f");
  TCase *tc = tcase_create("s21_sprintf_f_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, sprintf_f_1);
  tcase_add_test(tc, sprintf_f_2);
  tcase_add_test(tc, sprintf_f_3);
  tcase_add_test(tc, sprintf_f_4);

  suite_add_tcase(s, tc);
  return s;
}