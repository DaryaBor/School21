
#include "../test.h"
START_TEST(memchr_1) {
  char str[] = "POPA JOPA";
  int ch = ' ';
  s21_size_t len = strlen(str);
  ck_assert_ptr_eq(memchr(str, ch, len), s21_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_2) {
  char str[] = "POPA JOPA";
  int ch = 65;
  s21_size_t len = strlen(str);
  ck_assert_ptr_eq(memchr(str, ch, len), s21_memchr(str, ch, len));
}

END_TEST
START_TEST(memchr_3) {
  char str[] = "POPA JOPA";
  int ch = 'G';
  s21_size_t len = strlen(str);
  ck_assert_ptr_eq(memchr(str, ch, len), s21_memchr(str, ch, len));
}

END_TEST
START_TEST(memchr_4) {
  char str[] = "POPA JOPA";
  int ch = '\0';
  s21_size_t len = 5;
  ck_assert_ptr_eq(memchr(str, ch, len), s21_memchr(str, ch, len));
}
END_TEST

Suite *test_s21_memchr(void) {
  Suite *s = suite_create("s21_memchr");
  TCase *tc = tcase_create("s21_memchr_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, memchr_1);
  tcase_add_test(tc, memchr_2);
  tcase_add_test(tc, memchr_3);
  tcase_add_test(tc, memchr_4);

  suite_add_tcase(s, tc);
  return s;
}