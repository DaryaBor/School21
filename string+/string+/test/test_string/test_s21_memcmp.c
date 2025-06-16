#include "../test.h"

START_TEST(memcmp_1) {
  char s1[] = "popa jopa";
  char s2[] = "popa jopa";
  s21_size_t n = 0;
  int n1 = memcmp(s1, s2, n);
  int n2 = s21_memcmp(s1, s2, n);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(memcmp_2) {
  char s1[] = "popa jopa";
  char s2[] = "\0";
  s21_size_t n = 1;
  int n1 = memcmp(s1, s2, n);
  int n2 = s21_memcmp(s1, s2, n);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(memcmp_3) {
  char s1[] = "popa jopa";
  char s2[] = "popa jopa";
  s21_size_t n = 9;
  int n1 = memcmp(s1, s2, n);
  int n2 = s21_memcmp(s1, s2, n);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(memcmp_5) {
  char s1[] = "popka  jopa";
  char s2[] = "popa jopa";
  s21_size_t n = 5;
  int n1 = memcmp(s1, s2, n);
  int n2 = s21_memcmp(s1, s2, n);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(memcmp_7) {
  char s1[] = "Сравнивает первые n байтов str1\0 и str2.";
  char s2[] = "Сравнивает первые n байтов str1\0 и str2.";
  s21_size_t n = 32;
  int n1 = memcmp(s1, s2, n);
  int n2 = s21_memcmp(s1, s2, n);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(memcmp_8) {
  char s1[] = "";
  char s2[] = "";
  s21_size_t n = 0;
  int n1 = memcmp(s1, s2, n);
  int n2 = s21_memcmp(s1, s2, n);
  ck_assert_int_eq(n1, n2);
}
END_TEST

Suite *test_s21_memcmp(void) {
  Suite *s = suite_create("s21_memcmp");
  TCase *tc = tcase_create("s21_memcmp_tc");

  tcase_add_test(tc, memcmp_1);
  tcase_add_test(tc, memcmp_2);
  tcase_add_test(tc, memcmp_3);
  tcase_add_test(tc, memcmp_5);
  tcase_add_test(tc, memcmp_7);
  tcase_add_test(tc, memcmp_8);

  suite_add_tcase(s, tc);
  return s;
}