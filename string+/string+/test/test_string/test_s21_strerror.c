#include "../test.h"

START_TEST(strerror_1) {
  int errno =
      -140 + rand() % (281);  // x = [a;b] => x = a + rand() % (b - a + 1);
  char *s21_res = s21_strerror(errno);
  char *res = strerror(errno);
  ck_assert_str_eq(s21_res, res);
}
END_TEST
// START_TEST(strerror_1) {
//   for (int i = -1; i < 136; i++) {
//     ck_assert_str_eq(strerror(i), s21_strerror(i));
//   }
// }
// END_TEST

Suite *test_s21_strerror(void) {
  Suite *s = suite_create("s21_strerror");
  TCase *tc = tcase_create("s21_strerror_tc");

  suite_add_tcase(s, tc);

  tcase_add_test(tc, strerror_1);
  // tcase_add_test(tc, s21_strerror_n1);
  // tcase_add_test(tc, s21_strerror_n1);
  suite_add_tcase(s, tc);
  return s;
}