#include "../test.h"

START_TEST(sprintf_combo_1) {
  char str1[60];
  char str2[60];
  s21_sprintf(str1, "%c %d %f %s %u %%", 'W', -100, -123.12345678,
              "Hello world", 12345678);
  sprintf(str2, "%c %d %f %s %u %%", 'W', -100, -123.12345678, "Hello world",
          12345678);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_combo_2) {
  char str1[60];
  char str2[60];
  s21_sprintf(str1, "%c %d %f %s %u %%", ' ', -0, -0.0, "", 0);
  sprintf(str2, "%c %d %f %s %u %%", ' ', -0, -0.0, "", 0);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(sprintf_width_plus_1) {
  char str1[60];
  char str2[60];
  s21_sprintf(str1, "%1c %+10d %+3f %5s %3u %%", 'W', -100, -123.12345678,
              "Hello world", 12345678);
  sprintf(str2, "%1c %+10d %+3f %5s %3u %%", 'W', -100, -123.12345678,
          "Hello world", 12345678);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_precision_d_u_1) {
  char str1[200];
  char str2[200];
  s21_sprintf(str1, "%.0d %.5d %.3d %.8d %.0d %.5u %.3u %.8u", -12345, -12345,
              -12345, -12345, 12345, 12345, 12345, 12345);
  sprintf(str2, "%.0d %.5d %.3d %.8d %.0d %.5u %.3u %.8u", -12345, -12345,
          -12345, -12345, 12345, 12345, 12345, 12345);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_precision_f_1) {
  char str1[200];
  char str2[200];
  s21_sprintf(str1, "%.0f %.5f %.3f %.8f", -1.12345, 1.12345, -1.12345,
              1.12345);
  sprintf(str2, "%.0f %.5f %.3f %.8f", -1.12345, 1.12345, -1.12345, 1.12345);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_precision_s_1) {
  char str1[200];
  char str2[200];
  s21_sprintf(str1, "%.0s %.5s %.3s %.8s", "hello", "hello", "hello", "hello");
  sprintf(str2, "%.0s %.5s %.3s %.8s", "hello", "hello", "hello", "hello");
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_width_and_precision_1) {
  char str1[200];
  char str2[200];
  s21_sprintf(str1, "%10.5d %6.3f %12.10u %8.5s", -100, -123.12345678, 12345678,
              "hello world");
  sprintf(str2, "%10.5d %6.3f %12.10u %8.5s", -100, -123.12345678, 12345678,
          "hello world");
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_width_and_precision_2) {
  char str1[60];
  char str2[60];
  s21_sprintf(str1, "%3.5d %3.6f %8.10u %3.5s", -100, -123.12345678, 12345678,
              "hello world");
  sprintf(str2, "%3.5d %3.6f %8.10u %3.5s", -100, -123.12345678, 12345678,
          "hello world");
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_loop_int) {
  char buf1[200];
  char buf2[200];
  char str[8];
  int numbers[6] = {0, 1, -1, 334, 1232, -1234};
  char flags[5] = {'+', '-', ' ', '#', '0'};
  char lengths[2] = {'h', 'l'};
  int weigths[3] = {0, 9, 2};
  int precision[3] = {9, 0, 3};  // Не делать больше 10!
  int i = 0;
  char specifiers[6] = {'i', 'd', 'o', 'u', 'x', 'X'};
  for (int spec = 0; spec < 6; spec++) {
    for (int fl = 0; fl < 5; fl++) {
      for (int weig = 0; weig < 3; weig++) {
        for (int len = 0; len < 2; len++) {
          for (int pre = 0; pre < 3; pre++) {
            for (int num = 0; num < 6; num++) {
              if (i == 474) continue;  // Werror format
              str[0] = '%';
              str[1] = flags[fl];
              str[2] = '0' + weigths[weig];
              str[3] = '.';
              str[4] = '0' + precision[pre];
              str[5] = lengths[len];
              str[6] = specifiers[spec];
              str[7] = '\0';
              sprintf(buf2, str, numbers[num]);
              s21_sprintf(buf1, str, numbers[num]);

              ck_assert_str_eq(buf1, buf2);
              i++;
            }
          }
        }
      }
    }
  }
}
END_TEST

START_TEST(sprintf_width_minus_1) {
  char str1[60];
  char str2[60];
  s21_sprintf(str1, "%-1c %-10d %-3f %-5s %-3u %%", 'W', -100, -123.12345678,
              "Hello world", 12345678);
  sprintf(str2, "%-1c %-10d %-3f %-5s %-3u %%", 'W', -100, -123.12345678,
          "Hello world", 12345678);
  ck_assert_str_eq(str1, str2);
}
Suite *test_s21_combo(void) {
  Suite *s = suite_create("s21_sprintf_test_s21_combo1");
  TCase *tc = tcase_create("s21_sprintf_test_s21_combo1_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, sprintf_combo_1);
  tcase_add_test(tc, sprintf_combo_2);
  tcase_add_test(tc, sprintf_width_plus_1);
  tcase_add_test(tc, sprintf_precision_d_u_1);
  tcase_add_test(tc, sprintf_precision_f_1);
  tcase_add_test(tc, sprintf_precision_s_1);
  tcase_add_test(tc, sprintf_width_and_precision_1);
  tcase_add_test(tc, sprintf_width_and_precision_2);
  tcase_add_test(tc, sprintf_loop_int);
  tcase_add_test(tc, sprintf_width_minus_1);

  suite_add_tcase(s, tc);
  return s;
}