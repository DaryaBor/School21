#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} flags;

static struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                       {"number", 0, 0, 'n'},
                                       {"squeeze-blank", 0, 0, 's'},
                                       {
                                           0,
                                           0,
                                           0,
                                           0,
                                       }};

flags flg = {0};

void print_file(int argc, char **argv, int i, flags *flg) {
  int count = 1;
  int c;
  int N = 0;
  char buff[2500];
  for (int k = i; k < argc; k++) {
    FILE *file = fopen(argv[k], "r");
    if (file != NULL) {
      while ((c = fgetc(file)) != EOF) {
        N++;
        buff[N - 1] = c;
      }
    } else {
      continue;
    }
    fclose(file);
  }
  char prev = '\n';
  int empty_lines = 0;
  int done = 0;

  for (int y = 0; y < N; y++) {
    done = 0;
    if (buff[y] == '\n' && prev == '\n') {
      empty_lines++;
    } else {
      empty_lines = 0;
    }

    if ((flg->b && buff[y] != '\n' && prev == '\n')) {
      printf("%6d\t", count);
      count += 1;
    }

    if ((flg->n && prev == '\n' && flg->b != 1 &&
         (empty_lines <= 1 || flg->s == 0))) {
      printf("%6d\t", count);
      count += 1;
    }

    if (flg->e && buff[y] == '\n' && (empty_lines <= 1 || flg->s == 0)) {
      printf("%c", '$');
    }

    if (flg->t == 1 && buff[y] == '\t') {
      printf("^I");
      done += 1;
    }

    if (flg->v && buff[y] != '\n' && buff[y] != '\t') {
      if (buff[y] >= 0 && buff[y] <= 31) {
        printf("^%c", buff[y] + 64);
        done += 1;
      }
      if (buff[y] == 127) {
        printf("^%c", buff[y] - 64);
        done += 1;
      }
    }

    if ((empty_lines <= 1 || flg->s == 0) && (done == 0)) {
      printf("%c", buff[y]);
    }
    prev = buff[y];
  }
}

void check_structure(flags *flg, char letter) {
  if (letter == 'b') {
    flg->b = 1;
  }
  if (letter == 'e') {
    flg->e = 1;
    flg->v = 1;
  }

  if (letter == 'n') {
    flg->n = 1;
  }

  if (letter == 's') {
    flg->s = 1;
  }
  if (letter == 't') {
    flg->t = 1;
    flg->v = 1;
  }
  if (letter == 'v') {
    flg->v = 1;
  }
  if (letter == 'T') {
    flg->t = 1;
  }
  if (letter == 'E') {
    flg->e = 1;
  }
}

void parse(int argc, char **argv, flags *flg) {
  int letter = 0;
  int long_index;
  while ((letter = getopt_long(argc, argv, "benstvTE", long_options,
                               &long_index)) != -1) {
    check_structure(flg, letter);
  }
  if (optind < argc) {
    print_file(argc, argv, optind, flg);
  }
}

int main(int argc, char **argv) {
  parse(argc, argv, &flg);

  return 0;
}