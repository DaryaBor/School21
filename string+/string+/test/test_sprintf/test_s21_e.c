#include "../test.h"
// Спецификатор e
START_TEST(sprintf_e_test) {
  char str1[300];
  char str2[300];
  s21_sprintf(str1, "%.e %.5e %10.3e %.10e", 1215.45, -123.55, 0., 4125.12);
  sprintf(str2, "%.e %.5e %10.3e %.10e", 1215.45, -123.55, 0., 4125.12);
  ck_assert_str_eq(str1, str2);
}
END_TEST
Suite *test_e21_e(void) {
  Suite *s = suite_create("s21_printf_e");
  TCase *tc = tcase_create("s21_printf_e_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, sprintf_e_test);
  suite_add_tcase(s, tc);
  return s;
}