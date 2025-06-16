#include "../test.h"

START_TEST(sprintf_o_test) {
  char str1[30];
  char str2[30];
  s21_sprintf(str1, "%o %o", 1215, -123);
  sprintf(str2, "%o %o", 1215, -123);
  ck_assert_str_eq(str1, str2);
}
END_TEST
Suite *test_s21_o(void) {
  Suite *s = suite_create("s21_sprintf_o");
  TCase *tc = tcase_create("s21_sprintf_o_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, sprintf_o_test);
  suite_add_tcase(s, tc);
  return s;
}