#include "../test.h"
START_TEST(memcpy_1) {
  char s1[] = "popa jopa";
  char s2[] = "popa jopa";
  char s3[] = "BOB";
  s21_size_t n = 4;
  ck_assert_str_eq(memcpy(s1, s3, n), s21_memcpy(s2, s3, n));
}
END_TEST

START_TEST(memcpy_2) {
  char s1[] = "popa jopa";
  char s2[] = "popa jopa";
  char s3[] = "\0";
  s21_size_t n = 1;
  ck_assert_str_eq(memcpy(s1, s3, n), s21_memcpy(s2, s3, n));
}
END_TEST

START_TEST(memcpy_3) {
  char s1[] = "popa jopa";
  char s2[] = "popa jopa";
  char s3[] = "FFFFFFFFFFFFFFFFF";
  s21_size_t n = 0;
  ck_assert_str_eq(memcpy(s1, s3, n), s21_memcpy(s2, s3, n));
}
END_TEST

START_TEST(memcpy_4) {
  char s1[] = "";
  char s2[] = "";
  char s3[] = "BOBER";
  s21_size_t n = 0;
  ck_assert_str_eq(memcpy(s1, s3, n), s21_memcpy(s2, s3, n));
}
END_TEST

START_TEST(memcpy_5) {
  char s1[] = "popa\0jopa";
  char s2[] = "popa\0jopa";
  char s3[] = "mini";
  s21_size_t n = 3;
  ck_assert_str_eq(memcpy(s1, s3, n), s21_memcpy(s2, s3, n));
}
END_TEST

START_TEST(memcpy_6) {
  char s1[] = "popa jopa";
  char s2[] = "popa jopa";
  char s3[] = "";
  s21_size_t n = 1;
  ck_assert_str_eq(memcpy(s1, s3, n), s21_memcpy(s2, s3, n));
}
END_TEST

Suite *test_s21_memcpy(void) {
  Suite *s = suite_create("s21_memcpy");
  TCase *tc = tcase_create("s21_memcpy_tc");

  tcase_add_test(tc, memcpy_1);
  tcase_add_test(tc, memcpy_2);
  tcase_add_test(tc, memcpy_3);
  tcase_add_test(tc, memcpy_4);
  tcase_add_test(tc, memcpy_5);
  tcase_add_test(tc, memcpy_6);

  suite_add_tcase(s, tc);
  return s;
}