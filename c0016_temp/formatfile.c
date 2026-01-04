#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void insert_cr(FILE *file_in, FILE *file_out) {

  int out_char;
  int indent_count = 0;
  int i_count = 0;
  char *node_str = NULL;
  char *node_other = "node>";
  while ((out_char = fgetc(file_in)) != EOF) {
    fputc(out_char, file_out);
    if (out_char == '?' && (out_char = fgetc(file_in)) == '>') {
      fputc(out_char, file_out);
      fputc('\n', file_out);
    } else if (out_char == '>') {
      fputc('\n', file_out);
    }
  }
  fputc('\n', file_out);
  fflush(file_out);
}

void insert_indent(FILE *file_with_cr, FILE *file_with_indent) {
  int out_char;
  int indent_count = 0;
  int i_count = 0;
  char node_temp[500] = {""};
  char *node_begin = "<node";
  char *node_end = "</nod";
  bool node_end_flag = false;
  char *last_two_char = "/>";
  while (fgets(node_temp, 500, file_with_cr) != NULL) {
    // printf("%s", node_temp + strlen(node_temp) - 3);
    if (strncmp(node_begin, node_temp, 5) == 0) {
      if (!node_end_flag) {
        indent_count += 1;
      }
      i_count = indent_count;
      while (i_count-- > 0) {
        fputc('\t', file_with_indent);
      }
      fputs(node_temp, file_with_indent);
      node_end_flag = false;
      if (strncmp(last_two_char, node_temp + strlen(node_temp) - 3, 2) == 0) {
        node_end_flag = true;
        // printf("%s", node_temp + strlen(node_temp) - 2);
      }
    } else if (strncmp(node_end, node_temp, 5) == 0) {
      indent_count -= 1;
      i_count = indent_count;
      node_end_flag = true;
      while (i_count-- > 0) {
        fputc('\t', file_with_indent);
      }
      fputs(node_temp, file_with_indent);
    } else {
      fputs(node_temp, file_with_indent);
    }
  }
}

void test_copy_string(FILE *file_in, FILE *file_out) {
  int out_char;
  int indent_count = 0;
  int i_count = 0;
  char node_temp[500] = {""};
  char *node_begin = "<node";
  char *node_end = "</nod";
  bool node_end_flag = false;
  char *str_last_two = NULL;
  char *last_two_char = "/>";
  int strLen = 0;
  char *node_temp_real_str = NULL;
  while (fgets(node_temp, 500, file_in) != NULL) {
    strLen = 0;
    node_temp_real_str = NULL;
    printf("Length of a line get by fgets is %ld.\n", strlen(node_temp));
    for (int i = 0; strcmp((node_temp + i), "\n") != 0; i++) {
      strLen++;
    }
    node_temp_real_str = (char *)malloc(strLen);
    if (node_temp_real_str == NULL) {
      perror("allocate memory for node string failed.");
    }
    if (strncmp(last_two_char, node_temp + strlen(node_temp) - 2, 2) == 0) {
      printf("%s.\n", node_temp + strlen(node_temp) - 2);
    }
    memset(node_temp_real_str, '\0', strLen + 1);
    strncpy(node_temp_real_str, node_temp, strLen);
    printf("%d %ld\n", strLen, strlen(node_temp_real_str));
    printf("%s %s\n", node_temp, node_temp_real_str);
    assert(strlen(node_temp_real_str) == strLen);
    str_last_two = node_temp_real_str + strLen - 2;
    printf("%s\n", str_last_two);
  }
}

void test_fgets(FILE *file_cr, FILE *file_temp) {
  char str[500] = "Hello world!";
  char *pStr = NULL;
  int i = 0;
  while (i++ < 5) {
    if (fgets(pStr, 100, file_cr) != NULL) {
      // fputs(str, file_temp);
      // printf("%s\n", str);
      // printf("********\n");
      printf("%s\n", pStr);
    }
  }
}

void usage(int argc, char **argv) {
  char *usage_notfication =
      "Usage: formatfile /path/to/file \n"
      "\tOnly one argument needed, the argument is the file will be "
      "formated.\n"
      "\tThe second argument is the file you are going to formated.\n";

  char *too_few_arguments_error = "There are two arguments needed.";
  char *too_many_arguments_error =
      "There are too many arguments, two arguments is fine.";
  char *command_name_error =
      "The command is: formatfile, please check the spell.";
  char *file_not_provide_error = "Please provide the file after the command.";
  char *file_not_found_error = "File not existed.";

  if (argc < 2) {
    printf("%s\n", usage_notfication);
    printf("%s\n", too_few_arguments_error);
    exit(-1);
  } else if (argc > 2) {
    printf("%s\n", usage_notfication);
    printf("%s\n", too_many_arguments_error);
    exit(-1);
  }

  char *formatfile_command = "formatfile";
  char *command_extracted = strrchr(argv[0], '/') + 1;
  if (command_extracted == NULL) {
    printf("Please check the command or the path of command located.\n");
    exit(-1);
  }
  // printf("%s\n", command_extracted);
  // printf("%s\n", formatfile_command);
  if (strcmp(command_extracted, formatfile_command) != 0) {
    printf("%s\n", usage_notfication);
    printf("%s\n", command_name_error);
    exit(-1);
  }

  if (argv[1] == NULL) {
    printf("%s\n", usage_notfication);
    printf("%s\n", file_not_provide_error);
    exit(-1);
  }

  char *file_arg = argv[1];
  if (access(file_arg, F_OK) != 0) {
    printf("File not existed.\n");
    exit(-1);
  }
}

char *compose_dir_file(char *dir_name, char *file_name) {
  if (dir_name != NULL && file_name != NULL) {
    return strcat(dir_name, file_name);
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  // char *file_origin =
  // "/home/apuser/workspace/Cwarmup/c0016_fileio/src/wechat.xml"; char
  // *insert_cr_file =
  // "/home/apuser/workspace/Cwarmup/c0016_fileio/src/wechat_insert_carriage_return.xml";
  // char *insert_indent_file =
  // "/home/apuser/workspace/Cwarmup/c0016_fileio/src/wechat_insert_indent.xml";
  // char *temp_file =
  // "/home/apuser/workspace/Cwarmup/c0016_fileio/src/wechat_temp.xml";

  usage(argc, argv);

  size_t size = 100;
  char *current_dir = NULL;
  current_dir = (char *)malloc(sizeof(char) * size);
  getcwd(current_dir, size);
  if (current_dir == NULL) {
    printf("Get current directory name failed.");
    exit(-1);
  }

  strcat(current_dir, "/");

  char *insert_cr_file_name = "wechat_insert_carriage_return.xml";
  char *insert_indent_file_name = "wechat_insert_indent.xml";
  char *temp_file_name = "wechat_temp.xml";

  char *file_origin = argv[1];

  char *insert_cr_dir = (char *)malloc(sizeof(char) * size);
  memset(insert_cr_dir, '\0', strlen(insert_cr_dir));
  char *insert_cr_file =
      compose_dir_file(strcpy(insert_cr_dir, current_dir), insert_cr_file_name);
  printf("insert_cr_file is %s, size is %ld\n", insert_cr_file,
         strlen(insert_cr_file));

  char *insert_indent_dir = (char *)malloc(sizeof(char) * size);
  memset(insert_indent_dir, '\0', strlen(insert_indent_dir));
  char *insert_indent_file = compose_dir_file(
      strcpy(insert_indent_dir, current_dir), insert_indent_file_name);
  printf("insert_indent_dir is %s, size is %ld\n", insert_indent_file,
         strlen(insert_indent_file));

  char *temp_file_dir = (char *)malloc(sizeof(char) * size);
  memset(temp_file_dir, '\0', strlen(temp_file_dir));
  char *temp_file =
      compose_dir_file(strcpy(temp_file_dir, current_dir), temp_file_name);

  FILE *file = fopen(file_origin, "r");
  if (!file) {
    perror("File open failed.");
    return EXIT_FAILURE;
  }

  FILE *file_write_cr = fopen(insert_cr_file, "w+");
  if (!file_write_cr) {
    perror("File write CR open failed.");
    return EXIT_FAILURE;
  }

  FILE *file_write_indent = fopen(insert_indent_file, "w+");
  if (!file_write_indent) {
    perror("File write indent open failed.");
    return EXIT_FAILURE;
  }

  FILE *file_t = fopen(temp_file, "w+");
  if (!file_t) {
    perror("Temp file open failed.");
    return EXIT_FAILURE;
  }

  insert_cr(file, file_write_cr);
  int write_cr = fflush(file_write_cr);
  if (write_cr == EOF) {
    perror("write cr file flush failed.");
  }
  rewind(file);
  // test_fgets(file, file_t);
  rewind(file_write_cr);
  insert_indent(file_write_cr, file_write_indent);

  // test_copy_string(file_write_cr, NULL);

  fclose(file);
  fclose(file_write_cr);
  fclose(file_write_indent);
  fclose(file_t);
}
