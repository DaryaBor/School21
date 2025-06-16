#include "../test.h"

START_TEST(strncmp_1) {
  char s1[] = "Hello, world!";
  char s2[] = "Hello, worldj";
  s21_size_t n = 14;
  int n1 = strncmp(s1, s2, n);
  int n2 = s21_strncmp(s1, s2, n);

  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strncmp_2) {
  char s1[] = "f";
  char s2[] = "";
  s21_size_t n = 1;
  int n1 = strncmp(s1, s2, n);
  int n2 = s21_strncmp(s1, s2, n);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strncmp_3) {
  char s1[] = "";
  char s2[] = "j";
  s21_size_t n = 1;
  int n1 = strncmp(s1, s2, n);
  int n2 = s21_strncmp(s1, s2, n);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strncmp_4) {
  char s1[] = "popa jopa";
  char s2[] = "popa jopa";
  s21_size_t n = 9;
  int n1 = strncmp(s1, s2, n);
  int n2 = s21_strncmp(s1, s2, n);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strncmp_5) {
  char s1[] = "popa jopa";
  char s2[] = "popa jopa";
  s21_size_t n = 2;
  int n1 = strncmp(s1, s2, n);
  int n2 = s21_strncmp(s1, s2, n);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strncmp_6) {
  char s1[] = "g124243425";
  char s2[] = "124243424";
  s21_size_t n = 0;
  int n1 = strncmp(s1, s2, n);
  int n2 = s21_strncmp(s1, s2, n);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strncmp_7) {
  char s1[] = "";
  char s2[] = "";
  s21_size_t n = 1;
  int n1 = strncmp(s1, s2, n);
  int n2 = s21_strncmp(s1, s2, n);
  ck_assert_int_eq(n1, n2);
}
END_TEST

Suite *test_s21_strncmp(void) {
  Suite *s = suite_create("s21_strncmp");
  TCase *tc = tcase_create("s21_strncmp_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, strncmp_1);
  tcase_add_test(tc, strncmp_2);
  tcase_add_test(tc, strncmp_3);
  tcase_add_test(tc, strncmp_4);
  tcase_add_test(tc, strncmp_5);
  tcase_add_test(tc, strncmp_6);
  tcase_add_test(tc, strncmp_7);

  suite_add_tcase(s, tc);
  return s;
}