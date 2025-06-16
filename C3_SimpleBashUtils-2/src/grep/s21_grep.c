#include "s21_grep.h"

int process_search_pattern(arguments *opt, char *line) {
  regex_t regex;
  int result;
  int compile_result =
      regcomp(&regex, opt->pattern, REG_EXTENDED | opt->ignore_case);
  if (compile_result == 0) {
    result = regexec(&regex, line, 0, NULL, 0);
  } else {
    result = REG_BADPAT;
  }
  regfree(&regex);
  return result;
}
void process_output_line(const char *line, int n) {
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (n == 0 || line[n - 1] != '\n') {
    putchar('\n');
  }
}
void process_file(arguments *opt, const char *path) {
  FILE *fp = fopen(path, "r");
  if (fp == NULL) {
    opt->code_error = 1;
    if (!opt->no_messages) perror("s21_grep:No such file or directory\n");
  }
  if (!opt->code_error) {
    char *line = NULL;
    size_t size_mem_block = 0;
    int read = 0;
    int count_line = 0;
    int number_line_in_file = 1;
    read = getline(&line, &size_mem_block, fp);
    while (read != -1) {
      if (line[read - 1] == '\n') {
        line[read - 1] = '\0';
        read--;
      }
      int result = process_search_pattern(opt, line);
      if ((result == 0 && !opt->invert_matches) ||
          (result != 0 && opt->invert_matches && !opt->only_matching)) {
        if (opt->num_file && !opt->count_selected_lines &&
            !opt->files_with_matches && !opt->no_filename)
          printf("%s:", path);
        if (!opt->count_selected_lines && !opt->files_with_matches) {
          if (opt->line_number) printf("%d:", number_line_in_file);
          if (opt->only_matching) {
            print_only_matching(opt, line);
          } else {
            process_output_line(line, read);
          }
        }
        count_line++;
      }
      if (result != 0 && opt->invert_matches && opt->only_matching)
        count_line++;
      read = getline(&line, &size_mem_block, fp);
      number_line_in_file++;
    }
    free(line);
    if (opt->count_selected_lines && !opt->files_with_matches) {
      if (opt->num_file) {
        if (!opt->no_filename) printf("%s:", path);
      }
      printf("%d\n", count_line);
    }
    if (opt->files_with_matches && count_line > 0) {
      printf("%s\n", path);
    }
    fclose(fp);
  }
}

void add_pattern(arguments *opt, const char *pattern) {
  if (opt->length_pattern == 0) {
    opt->size_mem_pattern = 1024;
    opt->pattern = malloc(1024 * sizeof(char));
    if (opt->pattern == NULL) {
      opt->code_error = 1;
    }
  }
  if (!opt->code_error) {
    // +1 for |, +1 for null terminating char
    int n = strlen(pattern);
    int new_min_len = opt->length_pattern + (n + 2) * sizeof(char);
    if (opt->size_mem_pattern < new_min_len) {
      int new_len = new_min_len > opt->size_mem_pattern * 2
                        ? new_min_len
                        : opt->size_mem_pattern * 2;
      opt->size_mem_pattern = new_len;
      opt->pattern = realloc(opt->pattern, new_len);
      if (opt->pattern == NULL) {
        opt->code_error = 1;
      }
    }
    if (!opt->code_error) {
      if (opt->length_pattern != 0) {
        strcat(opt->pattern + opt->length_pattern, "|");
        opt->length_pattern += sizeof(char);
      }
      opt->length_pattern +=
          sprintf(opt->pattern + opt->length_pattern, "%s", pattern);
    }
  }
}
void add_pattern_from_file(arguments *opt, const char *filepath) {
  FILE *fp = fopen(filepath, "r");
  if (fp == NULL) {
    opt->code_error = 1;
    if (!opt->no_messages) perror("s21_grep:No such file or directory\n");
  }
  if (!opt->code_error) {
    char *line = NULL;
    size_t size_mem_block = 0;
    int read = 0;
    read = getline(&line, &size_mem_block, fp);
    while (read != -1) {
      if (line[read - 1] == '\n') (line[read - 1]) = '\0';
      add_pattern(opt, line);
      read = getline(&line, &size_mem_block, fp);
    }
    free(line);
    fclose(fp);
  }
}
void process_output_files(arguments *opt, int argc, char *argv[]) {
  if (argc - optind >= 2) opt->num_file++;
  if (!opt->code_error) {
    for (int i = optind; i < argc; i++) {
      process_file(opt, argv[i]);
    }
  }
}
arguments process_parse_grep(int argc, char *argv[]) {
  arguments opt = {0};
  int result = 0;
  while (((result = getopt(argc, argv, "ivclnhsoe:f:")) != EOF)) {
    switch (result) {
      case 'i':
        opt.ignore_case = REG_ICASE;
        break;
      case 'v':
        opt.invert_matches = 1;
        break;
      case 'c':
        opt.count_selected_lines = 1;
        break;
      case 'l':
        opt.files_with_matches = 1;
        break;
      case 'n':
        opt.line_number = 1;
        break;
      case 'h':
        opt.no_filename = 1;
        break;
      case 'o':
        opt.only_matching = 1;
        break;
      case 's':
        opt.no_messages = 1;
        break;
      case 'e':
        opt.pattern_for_matching = 1;
        add_pattern(&opt, optarg);
        break;
      case 'f':
        opt.patterns_from_file = 1;
        add_pattern_from_file(&opt, optarg);
        break;
      default:
        opt.code_error = 1;
        perror(
            "Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' for "
            "more information.\n");
    }
  }
  if (!opt.pattern_for_matching && !opt.patterns_from_file) {
    if (opt.length_pattern == 0) {
      add_pattern(&opt, argv[optind]);
      optind++;
    }
  }
  return opt;
}

void print_only_matching(arguments *opt, char *line) {
  regex_t regex;
  regmatch_t match;
  if (regcomp(&regex, opt->pattern, REG_EXTENDED | opt->ignore_case) == 0) {
    if (regexec(&regex, line, 0, NULL, 0) == 0) {
      int offset = 0;
      while (1) {
        int result = regexec(&regex, line + offset, 1, &match, 0);
        if (result != 0) {
          break;
        }
        for (int i = match.rm_so; i < match.rm_eo; i++) {
          putchar(line[offset + i]);
        }
        putchar('\n');
        offset += match.rm_eo;
      }
    }
    regfree(&regex);
  }
}

int main(int argc, char *argv[]) {
  if (argc > 2) {
    arguments opt = process_parse_grep(argc, argv);
    if (!opt.code_error) {
      process_output_files(&opt, argc, argv);
      free(opt.pattern);
    }
  } else {
    perror(
        "Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' for "
        "more information.\n");
  }
  return 0;
}
