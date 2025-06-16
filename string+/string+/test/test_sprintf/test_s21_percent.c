#include "../test.h"

// Спецификатор %

START_TEST(sprintf_percent_test) {
  char str1[20];
  char str2[20];
  s21_sprintf(str1, "%%as;dmas%%");
  sprintf(str2, "%%as;dmas%%");
  ck_assert_str_eq(str1, str2);
}
END_TEST
Suite *test_s21_percent(void) {
  Suite *s = suite_create("s21_sprintf_u");
  TCase *tc = tcase_create("s21_sprintf_u_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, sprintf_percent_test);
  suite_add_tcase(s, tc);
  return s;
}