#include "../test.h"

START_TEST(strlen_1) {
  char str[] =
      "\n\tSidim s bobrom za stolom\n\tVdvoyom, na uzhin gotovim "
      "poleno\n\tDavaj pogovorim, bobyor\n\tO tom, chto nabolelo";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_2) {
  char str[] = "";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_3) {
  char str[] = "\0";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_4) {
  char str[] = "\0FURR-FURR";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_5) {
  char str[] = "HZ \0 hz";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

Suite *test_s21_strlen(void) {
  Suite *s = suite_create("s21_strlen");
  TCase *tc = tcase_create("s21_strlen_tc");

  tcase_add_test(tc, strlen_1);
  tcase_add_test(tc, strlen_2);
  tcase_add_test(tc, strlen_3);
  tcase_add_test(tc, strlen_4);
  tcase_add_test(tc, strlen_5);

  suite_add_tcase(s, tc);
  return s;
}