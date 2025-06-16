
#include "test.h"

int main(void) {
  int failed = 0;
  Suite *s21_tests[] = {test_s21_memchr(),  test_s21_memcmp(),
                        test_s21_memcpy(),  test_s21_memset(),
                        test_s21_strncat(), test_s21_strchr(),
                        test_s21_strncmp(), test_s21_strncpy(),
                        test_s21_strcspn(), test_s21_strerror(),
                        test_s21_strlen(),  test_s21_strpbrk(),
                        test_s21_strrchr(), test_s21_strstr(),
                        test_s21_strtok(),  test_s21_c(),
                        test_s21_d(),       test_s21_f(),
                        test_s21_s(),       test_s21_u(),
                        test_s21_combo(),   test_s21_percent(),
                        test_s21_p(),       test_s21_o(),
                        test_e21_e(),       test_s21_x_n_round(),
                        test_s21_help(),    S21_NULL};
  for (int i = 0; s21_tests[i] != S21_NULL; ++i) {
    SRunner *sr = srunner_create(s21_tests[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);

  return failed == 0 ? 0 : 1;
}
