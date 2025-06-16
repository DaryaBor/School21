#include "../test.h"
START_TEST(strncpy_1) {
  char s1[20] = "Hello, world!";
  char s2[20] = "Hello, world!";
  char s3[] = "sru day";
  s21_size_t n = 5;
  ck_assert_pstr_eq(strncpy(s1, s3, n), s21_strncpy(s2, s3, n));
}
END_TEST

START_TEST(strncpy_2) {
  char s1[5] = "";
  char s2[5] = "";
  char s3[] = "";
  s21_size_t n = 0;
  ck_assert_pstr_eq(strncpy(s1, s3, n), s21_strncpy(s2, s3, n));
}
END_TEST

START_TEST(strncpy_3) {
  char s1[128] = "";
  char s2[128] = "";
  char s3[] =
      "\n\tSidim s bobrom za stolom"
      "\n\tVdvoyom, na uzhin gotovim poleno"
      "\n\tDavaj pogovorim, bobyor"
      "\n\tO tom, chto nabolelo";
  s21_size_t n = strlen(s3);
  ck_assert_pstr_eq(strncpy(s1, s3, n), s21_strncpy(s2, s3, n));
}
END_TEST

START_TEST(strncpy_4) {
  char s1[5] = "";
  char s2[5] = "";
  char s3[] = "\0";
  s21_size_t n = 1;
  ck_assert_pstr_eq(strncpy(s1, s3, n), s21_strncpy(s2, s3, n));
}
END_TEST

Suite *test_s21_strncpy(void) {
  Suite *s = suite_create("s21_strncpy");
  TCase *tc = tcase_create("s21_strncpy_tc");

  tcase_add_test(tc, strncpy_1);
  tcase_add_test(tc, strncpy_2);
  tcase_add_test(tc, strncpy_3);
  tcase_add_test(tc, strncpy_4);
  suite_add_tcase(s, tc);
  return s;
}