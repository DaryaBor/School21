CC = gcc
CFLAGS = -Wall -Werror -Wextra
CAT_DIR = cat
GREP_DIR = grep
s21_cat:
	$(CC) $(CFLAGS) $(CAT_DIR)/s21_cat.c -o $(CAT_DIR)/s21_cat

s21_grep:
	$(CC) $(CFLAGS) $(GREP_DIR)/s21_grep.c -o $(GREP_DIR)/s21_grep

cat_test:
	cd cat && bash cat_test.sh
	
grep_test:
	cd grep && bash grep_test.sh

clean:
	rm cat/s21_cat grep/s21_grep