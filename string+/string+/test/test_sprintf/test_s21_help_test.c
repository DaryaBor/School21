#include "../test.h"

START_TEST(s21_sprintf_d) {
  char str1[200] = "";
  char str2[200] = "";
  char *str3 = "<%d>|<%-3.d>|<%5.7d>|<%10d>|<%#d>|<%-d>|<%+d>|<%ld>|<% .d>";
  int val = 0;
  ck_assert_int_eq(
      sprintf(str1, str3, val, val, val, val, val, val, val, val, val),
      s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_e) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "<%#e>|<%#.e>|<%#5.e>|<%#.0e>|<%#0.0e> %%";
  double num = -665695342471359.;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_c) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "<%6.4c>|<%-6.4c>|<%4.10lc>|<%-4.10lc>|<%-0lc>";
  int a = 10;
  unsigned long int b = 10;
  unsigned long int c = 10;
  ck_assert_int_eq(sprintf(str1, str3, a, a, b, c, c),
                   s21_sprintf(str2, str3, a, a, b, c, c));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_E) {
  char str1[300] = "";
  char str2[300] = "";
  double num1 = .3529373967;
  double num2 = .0003529373967;
  double num3 = 0.00000003529373967;
  char *str3 = "<% 30.1E>|<% 30.E>|<%030.0E>";
  ck_assert_int_eq(sprintf(str1, str3, num1, num2, num3),
                   s21_sprintf(str2, str3, num1, num2, num3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_i) {
  char str1[200] = "";
  char str2[200] = "";
  char *str3 = "<%i><%3.i><%5.7i><%10i><%#i><%-i><%+i><%.i><% .i>";
  int val = 0;
  ck_assert_int_eq(
      sprintf(str1, str3, val, val, val, val, val, val, val, val, val),
      s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val,
                  val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_on) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "text %o %n  %o%n";
  int val = 012;
  int val2 = 017;
  int valn1 = 0, valn2 = 0, valn3 = 0, valn4 = 0;
  ck_assert_int_eq(sprintf(str1, str3, val, &valn1, val2, &valn3),
                   s21_sprintf(str2, str3, val, &valn2, val2, &valn4));
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(valn1, valn2);
  ck_assert_int_eq(valn3, valn4);
}
END_TEST

START_TEST(s21_sprintf_o) {
  char str1[200] = "";
  char str2[200] = "";
  char *str3 = "<%o><%3.o><%5.7o><%10o %#o %-o %+o %.o % .o>";
  int val = 0;
  ck_assert_int_eq(
      sprintf(str1, str3, val, val, val, val, val, val, val, val, val),
      s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_p) {
  char str1[200] = "";
  char str2[200] = "";
  char *str3 = "<%0p><%06p><%05.7p><%0.7p Oof %0.p>";
  char *val = "32";
  char *val2 = "8899";
  char *val3 = "91918";
  char *val4 = "32311";
  char *val5 = "8894";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_s) {
  char str1[200] = "";
  char str2[200] = "";
  char *str3 = "<% s><% 3.s><% 5.7s><% 10s GOD %.s>";
  char *val = "WHAT IS THIS>";
  char *val2 = "i don't care anymore, really";
  char *val3 = "PPAP";
  char *val4 = "I don't feel so good";
  char *val5 = "What is lovin'?!";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_u) {
  char str1[200] = "";
  char str2[200] = "";
  char *str3 = "<%u><%3.u><%5.7u><%10u><%#u><%-u><%+u><%.u><% .u>";
  unsigned int val = 0;
  sprintf(str1, str3, val, val, val, val, val, val, val, val, val);
  s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val);
  ck_assert_int_eq(
      sprintf(str1, str3, val, val, val, val, val, val, val, val, val),
      s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_f) {
  char str1[400] = "";
  char str2[400] = "";
  char *str3 = "<%Lf>|<%.Lf>|<%+-#Lf>|<%+#.Lf>|<%-#.Lf>";
  long double num = 76.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_g) {
  char str1[200] = "";
  char str2[200] = "";
  char *str3 = "<%g>|<%g>|<%g>|<%4g>|<%5.6g>";
  double num = -57251397732103429.56589367;
  ck_assert_int_eq(sprintf(str1, str3, num, 1000., 10.1, num, num),
                   s21_sprintf(str2, str3, num, 1000., 10.1, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_x) {
  char str1[200] = "";
  char str2[200] = "";
  char *str3 = "<%x><%3.x><%5.7x><%10x><%#x><%-x><%+x><%.x><% .x>";
  int val = 0;
  ck_assert_int_eq(
      sprintf(str1, str3, val, val, val, val, val, val, val, val, val),
      s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_h) {
  char *s21_test_str = (char *)calloc(256, sizeof(char));
  char *lib_test_str = (char *)calloc(256, sizeof(char));

  short e = 0;
  short f = 32767;
  unsigned short b = 65535;
  int lib_res = sprintf(lib_test_str, "|%hi| |%hd| |%hu|", e, f, b);
  int s21_res = s21_sprintf(s21_test_str, "|%hi| |%hd| |%hu|", e, f, b);

  ck_assert_str_eq(s21_test_str, lib_test_str);
  ck_assert_int_eq(s21_res, lib_res);

  free(s21_test_str);
  free(lib_test_str);
}
END_TEST

START_TEST(s21_sprintf_l) {
  char *s21_test_str = (char *)calloc(256, sizeof(char));
  char *lib_test_str = (char *)calloc(256, sizeof(char));
  long i = INT_MAX;
  long a = INT_MIN;
  unsigned long b = 4294967295;
  int lib_res = sprintf(lib_test_str, "|%li| |%ld| |%lu|", i, a, b);
  int s21_res = s21_sprintf(s21_test_str, "|%li| |%ld| |%lu|", i, a, b);

  ck_assert_str_eq(s21_test_str, lib_test_str);
  ck_assert_int_eq(s21_res, lib_res);

  free(s21_test_str);
  free(lib_test_str);
}
END_TEST

START_TEST(s21_sprintf_empty) {
  char *s21_test_str = (char *)calloc(512, sizeof(char));
  char *lib_test_str = (char *)calloc(512, sizeof(char));

  int lib_res = sprintf(lib_test_str, "%c", '\0');
  int s21_res = s21_sprintf(s21_test_str, "%c", '\0');

  ck_assert_str_eq(s21_test_str, lib_test_str);
  ck_assert_int_eq(s21_res, lib_res);

  free(s21_test_str);
  free(lib_test_str);
}
END_TEST

Suite *test_s21_help(void) {
  Suite *s = suite_create("s21_sprintf_help");
  TCase *tcase = tcase_create("s21_sprintf_help_tc");

  suite_add_tcase(s, tcase);
  tcase_add_test(tcase, s21_sprintf_d);
  tcase_add_test(tcase, s21_sprintf_u);
  tcase_add_test(tcase, s21_sprintf_x);
  tcase_add_test(tcase, s21_sprintf_g);
  tcase_add_test(tcase, s21_sprintf_p);
  tcase_add_test(tcase, s21_sprintf_o);
  tcase_add_test(tcase, s21_sprintf_on);
  tcase_add_test(tcase, s21_sprintf_x);
  tcase_add_test(tcase, s21_sprintf_e);
  tcase_add_test(tcase, s21_sprintf_E);
  tcase_add_test(tcase, s21_sprintf_c);
  tcase_add_test(tcase, s21_sprintf_f);
  tcase_add_test(tcase, s21_sprintf_i);
  tcase_add_test(tcase, s21_sprintf_s);
  tcase_add_test(tcase, s21_sprintf_h);
  tcase_add_test(tcase, s21_sprintf_l);
  tcase_add_test(tcase, s21_sprintf_empty);

  suite_add_tcase(s, tcase);
  return s;
}