#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void insert_cr(FILE*, FILE*);
void insert_indent(FILE*, FILE*);
void usage(int, char**);
char *compose_dir_file(char*, char*);