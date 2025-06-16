#include "../test.h"
// Спецификатор s
START_TEST(sprintf_s_1) {
  char str1[20];
  char str2[20];
  s21_sprintf(str1, " %s", "hello world");
  sprintf(str2, " %s", "hello world");
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_s_2) {
  char str1[20];
  char str2[20];
  s21_sprintf(str1, "  %s  ", "hello \0world");
  sprintf(str2, "  %s  ", "hello \0world");
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_s_3) {
  char str1[20];
  char str2[20];
  s21_sprintf(str1, " %s %s%s ", "hello", "", "world\n");
  sprintf(str2, " %s %s%s ", "hello", "", "world\n");
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_s_4) {
  char str1[20];
  char str2[20];
  s21_sprintf(str1, "%s%s", "", " ");
  sprintf(str2, "%s%s", "", " ");
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_s_5) {
  char str1[20];
  char str2[20];
  s21_sprintf(str1, " %s world", "hello");
  sprintf(str2, " %s world", "hello");
  ck_assert_str_eq(str1, str2);
}
END_TEST
Suite *test_s21_s(void) {
  Suite *s = suite_create("s21_sprintf_s");
  TCase *tc = tcase_create("s21_sprintf_s_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, sprintf_s_1);
  tcase_add_test(tc, sprintf_s_2);
  tcase_add_test(tc, sprintf_s_3);
  tcase_add_test(tc, sprintf_s_4);
  tcase_add_test(tc, sprintf_s_5);
  suite_add_tcase(s, tc);
  return s;
}