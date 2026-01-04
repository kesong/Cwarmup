#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char *program_name = argv[0];
  char program_full_path[100] = {""};
  char program_dir[100] = {""};
  char program_dir_real[100] = {""};
  char *program_name_str = NULL;
  printf("%s\n", program_name);
  readlink("/proc/self/exe", program_full_path, 100);
  printf("%s\n", program_full_path);
  program_name_str = (char *)malloc(sizeof(char) * 100);
  program_name_str = strrchr(program_full_path, '/');
  strncpy(program_dir_real, program_full_path,
          strlen(program_full_path) - strlen(program_name_str) + 1);
  printf("%s\n", program_dir_real);
  program_name_str += 1;
  printf("%s\n", program_name_str);
}
