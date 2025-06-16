#include "../test.h"

START_TEST(strpbrk_1) {
  char s1[] = "Hello";
  char s2[] = "Hello";
  ck_assert_pstr_eq(strpbrk(s1, s2), s21_strpbrk(s1, s2));
}
END_TEST
START_TEST(strpbrk_2) {
  char s1[] = "Hello!";
  char s2[] = "!";
  ck_assert_pstr_eq(strpbrk(s1, s2), s21_strpbrk(s1, s2));
}
END_TEST

START_TEST(strpbrk_3) {
  char s1[] = "";
  char s2[] = "He";
  ck_assert_pstr_eq(strpbrk(s1, s2), s21_strpbrk(s1, s2));
}
END_TEST

START_TEST(strpbrk_4) {
  char s1[] = "\0";
  char s2[] = "";
  ck_assert_pstr_eq(strpbrk(s1, s2), s21_strpbrk(s1, s2));
}
END_TEST

START_TEST(strpbrk_5) {
  char s1[] = "12345678901234567890123242655300000";
  char s2[] = "098765098765";
  ck_assert_pstr_eq(strpbrk(s1, s2), s21_strpbrk(s1, s2));
}
END_TEST

Suite *test_s21_strpbrk(void) {
  Suite *s = suite_create(" S21_STRPBRK ");
  TCase *tc = tcase_create("strpbrk_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, strpbrk_1);
  tcase_add_test(tc, strpbrk_2);
  tcase_add_test(tc, strpbrk_3);
  tcase_add_test(tc, strpbrk_4);
  tcase_add_test(tc, strpbrk_5);

  suite_add_tcase(s, tc);
  return s;
}