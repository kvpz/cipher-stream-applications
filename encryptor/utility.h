#ifndef UTILITY_H
#define UTILITY_H
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>

void clear_terminal_screen(void);

void print_string_with_spaces(char*);

void print_string_to_ascii(char*);

char* get_stdin_stream();

#endif
