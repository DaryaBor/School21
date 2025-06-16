#include "../test.h"

START_TEST(strchr_1) {
  char str_src[] = "Hello, world!";
  int ch = 'h';
  ck_assert_pstr_eq(strchr(str_src, ch), s21_strchr(str_src, ch));
}
END_TEST

START_TEST(strchr_2) {
  char str_src[] = "Hello, world!";
  int ch = '\0';
  ck_assert_pstr_eq(strchr(str_src, ch), s21_strchr(str_src, ch));
}
END_TEST

START_TEST(strchr_3) {
  char str_src[] = "Hello, world!";
  int ch = ',';
  ck_assert_pstr_eq(strchr(str_src, ch), s21_strchr(str_src, ch));
}
END_TEST

START_TEST(strchr_4) {
  char str_src[] = "Hello, world!";
  int ch = 33;
  ck_assert_pstr_eq(strchr(str_src, ch), s21_strchr(str_src, ch));
}
END_TEST

Suite *test_s21_strchr(void) {
  Suite *str_src = suite_create("s21_strchr");
  TCase *tc = tcase_create("s21_strchr_tc");

  suite_add_tcase(str_src, tc);
  tcase_add_test(tc, strchr_1);
  tcase_add_test(tc, strchr_2);
  tcase_add_test(tc, strchr_3);
  tcase_add_test(tc, strchr_4);

  suite_add_tcase(str_src, tc);
  return str_src;
}