#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arguments {

  int pattern_for_matching;

  int ignore_case;
  
  int invert_matches;
 
  int count_selected_lines;
 
  int files_with_matches;

  int line_number;

  int no_filename;
 
  int only_matching;

  int no_messages;

  int patterns_from_file;
  int code_error;
  int num_file;
  char *pattern;
  int length_pattern;
  int size_mem_pattern;
} arguments;

arguments process_parse_grep(int argc, char *argv[]);
void process_output_line(const char *line, int n);
void process_file(arguments *opt, const char *path);
void add_pattern(arguments *opt, const char *pattern);
void add_pattern_from_file(arguments *opt, const char *filepath);
void process_output_files(arguments *opt, int argc, char *argv[]);
int process_search_pattern(arguments *opt, char *line);
void print_only_matching(arguments *opt, char *line);
