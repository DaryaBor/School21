#include "../test.h"

START_TEST(sprintf_p_test) {
  char str1[20];
  char str2[20];
  s21_sprintf(str1, "%p", str1);
  sprintf(str2, "%p", str1);
  ck_assert_str_eq(str1, str2);
}
END_TEST
Suite *test_s21_p(void) {
  Suite *s = suite_create("s21_sprintf_p");
  TCase *tc = tcase_create("s21_sprintf_p_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, sprintf_p_test);
  suite_add_tcase(s, tc);
  return s;
}