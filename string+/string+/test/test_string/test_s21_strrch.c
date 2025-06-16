#include "../test.h"
START_TEST(strrchr_1) {
  char s[] = "\npopa jopa";
  int ch = '\n';
  ck_assert_pstr_eq(strrchr(s, ch), s21_strrchr(s, ch));
}
END_TEST

START_TEST(strrchr_2) {
  char s[] = "popa jopa";
  int ch = '\0';
  ck_assert_pstr_eq(strrchr(s, ch), s21_strrchr(s, ch));
}
END_TEST

START_TEST(strrchr_3) {
  char s[] = "popa jopa";
  int ch = 'a';
  ck_assert_pstr_eq(strrchr(s, ch), s21_strrchr(s, ch));
}
END_TEST
START_TEST(strrchr_4) {
  char s[] = "popa jopa";
  int ch = 'j';
  ck_assert_pstr_eq(strrchr(s, ch), s21_strrchr(s, ch));
}
END_TEST
Suite *test_s21_strrchr(void) {
  Suite *s = suite_create("s21_strrchr");
  TCase *tc = tcase_create("s21_strrchr_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, strrchr_1);
  tcase_add_test(tc, strrchr_2);
  tcase_add_test(tc, strrchr_3);
  tcase_add_test(tc, strrchr_4);

  suite_add_tcase(s, tc);
  return s;
}