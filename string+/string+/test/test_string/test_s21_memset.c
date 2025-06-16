#include "../test.h"
START_TEST(memset_1) {
  char s1[] = "popa jopa";
  char s2[] = "popa jopa";
  int ch = ' ';
  s21_size_t n = strlen(s1);
  ck_assert_str_eq(memset(s1, ch, n), s21_memset(s2, ch, n));
}
END_TEST

START_TEST(memset_2) {
  char s1[] = "popa jopa";
  char s2[] = "popa jopa";
  int ch = ' ';
  s21_size_t n = 5;
  ck_assert_str_eq(memset(s1, ch, n), s21_memset(s2, ch, n));
}
END_TEST

START_TEST(memset_3) {
  char s1[] = "";
  char s2[] = "";
  int ch = '\0';
  s21_size_t n = 0;
  ck_assert_str_eq(memset(s1, ch, n), s21_memset(s2, ch, n));
}
END_TEST

START_TEST(memset_4) {
  char s1[] = "popa jopa";
  char s2[] = "popa jopa";
  int ch = '\0';
  s21_size_t n = 4;
  ck_assert_str_eq(memset(s1, ch, n), s21_memset(s2, ch, n));
}
END_TEST

Suite *test_s21_memset(void) {
  Suite *s = suite_create("s21_memset");
  TCase *tc = tcase_create("s21_memset_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, memset_1);
  tcase_add_test(tc, memset_2);
  tcase_add_test(tc, memset_3);
  tcase_add_test(tc, memset_4);

  suite_add_tcase(s, tc);
  return s;
}