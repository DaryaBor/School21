
CC = gcc -g
CFLAGS = -Werror -Wextra -Wall -std=c11

CLANG = clang-format -i

CHECKFLAGS = -lcheck -lsubunit -lm

GCOVFLAGS = -fprofile-arcs -ftest-coverage

C_TEST_FILES_STRING = test/test_string/*.c
C_TEST_FILES_SPRINTF = test/test_sprintf/*.c
C_FILES_STRING = s21_string/*.c
C_FILES_SPRINTF = s21_sprintf/*.c

O_FILES = s21_*.o
O_TEST_FILES = test_s21*.o

# Основные цели
all: s21_string.a test gcov_report


# lib
s21_string_o: $(C_FILES_SPRINTF) $(C_FILES_STRING)
	$(CLANG) $(C_FILES_SPRINTF) $(C_FILES_STRING)
	$(CC) $(CFLAGS) -c $(C_FILES_SPRINTF) $(C_FILES_STRING)

s21_string.a: s21_string_o
	ar rcs s21_string.a $(O_FILES)
	ranlib s21_string.a

# test
s21_test_string_o: $(C_TEST_FILES_STRING) $(C_TEST_FILES_SPRINTF)
	$(CLANG) $(C_TEST_FILES_STRING) $(C_TEST_FILES_SPRINTF)
	$(CC) $(CFLAGS) -c $(C_TEST_FILES_STRING) $(C_TEST_FILES_SPRINTF)

test.o: test/test.c
	$(CC) $(CFLAGS) -c test/test.c

test: s21_test_string_o s21_string.a test.o
	$(CC) $(O_TEST_FILES) $(O_FILES) test.o -o s21_test $(CHECKFLAGS)
	./s21_test

# gcov_report
gcov_report: s21_string.a 
	gcc $(CFLAGS) $(GCOVFLAGS) test/test.c $(C_FILES_SPRINTF) $(C_FILES_STRING) $(C_TEST_FILES_SPRINTF) $(C_TEST_FILES_STRING) s21_string.a -L. s21_string.a $(CHECKFLAGS) -o s21_test 
	./s21_test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage_report
	@echo "HTML report generated in coverage_report/"
	open ./coverage_report/index.html

# Вспомогательные цели
rebuild:
	make clean
	make build

clean:
	rm -rf *.o s21_test *.gcda *.gcno *.info coverage_report *.a

