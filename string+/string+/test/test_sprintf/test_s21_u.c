#include "../test.h"

// Спецификатор u
START_TEST(sprintf_u_1) {
  char str1[20];
  char str2[20];
  s21_sprintf(str1, "%u", 200);
  sprintf(str2, "%u", 200);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_u_2) {
  char str1[20];
  char str2[20];
  s21_sprintf(str1, "  %u %u %u  ", 1, 2, 3);
  sprintf(str2, "  %u %u %u  ", 1, 2, 3);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_u_3) {
  char str1[40];
  char str2[40];
  s21_sprintf(str1, "%-1u %-5u %u %-2u %u", 100, 2, 3, 4000, 5);
  sprintf(str2, "%-1u %-5u %u %-2u %u", 100, 2, 3, 4000, 5);
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite *test_s21_u(void) {
  Suite *s = suite_create("s21_sprintf_u");
  TCase *tc = tcase_create("s21_sprintf_u_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, sprintf_u_1);
  tcase_add_test(tc, sprintf_u_2);
  tcase_add_test(tc, sprintf_u_3);
  suite_add_tcase(s, tc);
  return s;
}