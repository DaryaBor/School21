#ifndef SRC_TESTS_ME_H
#define SRC_TESTS_ME_H

#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "../s21_string.h"

/*test string*/
Suite *test_s21_strpbrk(void);
Suite *test_s21_strncat(void);
Suite *test_s21_strchr(void);
Suite *test_s21_strcspn(void);
Suite *test_s21_strerror(void);
Suite *test_s21_strlen(void);
Suite *test_s21_strncmp(void);
Suite *test_s21_strncpy(void);
Suite *test_s21_strrchr(void);
Suite *test_s21_strstr(void);
Suite *test_s21_strtok(void);
Suite *test_s21_memchr(void);
Suite *test_s21_memcmp(void);
Suite *test_s21_memcpy(void);
Suite *test_s21_memset(void);

/*test sprintf*/

Suite *test_s21_c(void);
Suite *test_s21_d(void);
Suite *test_s21_f(void);
Suite *test_s21_s(void);
Suite *test_s21_u(void);
Suite *test_s21_combo(void);
Suite *test_s21_percent(void);
Suite *test_s21_p(void);
Suite *test_s21_o(void);
Suite *test_e21_e(void);
Suite *test_s21_x_n_round(void);
Suite *test_s21_help(void);
#endif  // SRC_TESTS_ME_H