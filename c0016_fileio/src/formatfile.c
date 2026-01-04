#include "formatfile.h"
#include <string.h>

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

  /*
   * testint some file operation
  char *file_out_name =
      "/home/apuser/workspace/Cwarmup/c0016_fileio/test/wechat_out.xml";
  char *file_in_name =
      "/home/apuser/workspace/Cwarmup/c0016_fileio/test/wechat_in.xml";
  FILE *file_full_out = fopen(file_out_name, "r");

  if (!file_full_out) {
    perror("File open failed.");
    return EXIT_FAILURE;
  }

  FILE *file_full_in = fopen(file_in_name, "w+");
  if (!file_full_in) {
    perror("File in open failed.");
    return EXIT_FAILURE;
  }

  test_fgetc(file_full_out);
  test_fputc(file_full_out, file_full_in);
  fclose(file_full_out);
  fclose(file_full_in);
  */

  usage(argc, argv);

  size_t size = 100;
  // char current_dir[size] = {""};
  char *current_dir = (char *)malloc(sizeof(char) * size);
  memset(current_dir, '\0', size);
  // getcwd获取的路径会随着命令前面的路径不同产生变化，获取的路径可嫩会发生变化；
  // 使用readlink(char*, char*,int)
  // 获取路径与命令前面的是否添加命令所在路径无关，更好用
  /*
  getcwd(current_dir, size);
  if (current_dir == NULL) {
    printf("Get current directory name failed.");
    exit(-1);
  }
  strcat(current_dir, "/");
  */
  char programe_full_path[size];
  readlink("/proc/self/exe", programe_full_path, size);
  char *program_name_str = NULL;
  program_name_str = (char *)malloc(sizeof(char) * size);
  program_name_str = strrchr(programe_full_path, '/');
  strncpy(current_dir, programe_full_path,
          strlen(programe_full_path) - strlen(program_name_str) + 1);

  char *file_name = argv[1];
  char *file_origin_dir = NULL;
  char *file_name_only = NULL;
  file_origin_dir = (char *)malloc(sizeof(char) * size);
  memset(file_origin_dir, '\0', size);
  file_name_only = (char *)malloc(sizeof(char) * 50);
  memset(file_name_only, '\0', 50);
  // file_name_only_temp用来保存file_name_only的初始内存地址，以方便后续释放malloc空间
  char *file_name_only_temp = file_name_only;
  file_name_only = strrchr(file_name, '/');
  if (file_name_only != NULL) {
    file_name_only += 1;
  } else {
    file_name_only = file_name;
  }

  char *file_name_only_with_no_suffix = NULL;
  char *file_name_only_suffix = NULL;
  file_name_only_with_no_suffix = (char *)malloc(sizeof(char) * size);
  memset(file_name_only_with_no_suffix, '\0', size);
  file_name_only_suffix = (char *)malloc(sizeof(char) * size);
  memset(file_name_only_suffix, '\0', size);
  char *file_name_only_suffix_store = file_name_only_suffix;
  file_name_only_suffix = strrchr(file_name_only, '.');
  if (file_name_only_suffix != NULL) {
    strncpy(file_name_only_with_no_suffix, file_name_only,
            strlen(file_name_only) - strlen(file_name_only_suffix));
  } else {
    perror("File name in the commandline is invalid.");
  }

  char *file_insert_cr_temp = NULL;
  file_insert_cr_temp = (char *)malloc(sizeof(char) * size);
  memset(file_insert_cr_temp, '\0', size);
  // char *insert_cr_file_name = "wechat_insert_carriage_return.xml";
  char *insert_cr_file_name = compose_dir_file(
      strcpy(file_insert_cr_temp, file_name_only_with_no_suffix),
      "_insert_carriage_return.xml");

  // char *insert_indent_file_name = "wechat_insert_indent.xml";
  char *file_insert_indent_temp = NULL;
  file_insert_indent_temp = (char *)malloc(sizeof(char) * size);
  memset(file_insert_indent_temp, '\0', size);
  char *insert_indent_file_name = compose_dir_file(
      strcpy(file_insert_indent_temp, file_name_only_with_no_suffix),
      "_insert_indent.xml");

  char *file_origin =
      compose_dir_file(strcpy(file_origin_dir, current_dir), file_name_only);

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

  // file_name_only_temp用来保存file_name_only最初malloc之后的值，因为要free的file_name_only这个指针，必须保证该指针的值没有改变
  // 但是在读取参数以后，获取文件名的过程中改变了该指针，如果直接调用free()来释放这个指针，会报段错误。
  file_name_only = file_name_only_temp;
  file_name_only_suffix = file_name_only_suffix_store;
  free(file_name_only);
  file_name_only_temp = NULL;
  free(file_origin_dir);
  file_origin_dir = NULL;
  free(insert_cr_dir);
  insert_cr_dir = NULL;
  free(insert_indent_dir);
  insert_indent_dir = NULL;
  free(current_dir);
  free(file_name_only_with_no_suffix);
  file_name_only_with_no_suffix = NULL;
  free(file_name_only_suffix);
  file_name_only_suffix = NULL;
  current_dir = NULL;
  fclose(file);
  fclose(file_write_cr);
  fclose(file_write_indent);
}
