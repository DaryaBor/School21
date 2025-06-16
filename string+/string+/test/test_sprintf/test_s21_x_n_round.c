#include "../test.h"

// Спецификатор round
START_TEST(sprintf_ceil_round) {
  char str1[50];
  char str2[50];
  s21_sprintf(str1, "%.0e %.f %.6f %.5e", 9999.9999, 1215.6, 123.1234567,
              -7.777777);
  sprintf(str2, "%.0e %.f %.6f %.5e", 9999.9999, 1215.6, 123.1234567,
          -7.777777);
  ck_assert_str_eq(str1, str2);
}
END_TEST
// Спецификатор x
START_TEST(sprintf_x_test) {
  char str1[50];
  char str2[50];
  s21_sprintf(str1, "%x %#X %*.*Lf %#o %hu %lu %010d", 123, 123, 10, 3,
              (long double)123.123, 1211, (short unsigned int)100,
              (long unsigned int)100, -10);
  sprintf(str2, "%x %#X %*.*Lf %#o %hu %lu %010d", 123, 123, 10, 3,
          (long double)123.123, 1211, (short unsigned int)100,
          (long unsigned int)100, -10);
  ck_assert_str_eq(str1, str2);
}
END_TEST
// Спецификатор n
START_TEST(sprintf_n_test) {
  char str1[50];
  char str2[50];
  int n1;
  int n2;
  s21_sprintf(str1, "%x %#X %*.*Lf %#o %hu %lu %010d %n", 123, 123, 10, 3,
              (long double)123.123, 1211, (short unsigned int)100,
              (long unsigned int)100, -10, &n1);
  sprintf(str2, "%x %#X %*.*Lf %#o %hu %lu %010d %n", 123, 123, 10, 3,
          (long double)123.123, 1211, (short unsigned int)100,
          (long unsigned int)100, -10, &n2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

Suite *test_s21_x_n_round(void) {
  Suite *s = suite_create("s21_sprintf_c");
  TCase *tc = tcase_create("s21_sprintf_c_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, sprintf_ceil_round);
  tcase_add_test(tc, sprintf_x_test);
  tcase_add_test(tc, sprintf_n_test);

  suite_add_tcase(s, tc);
  return s;
}