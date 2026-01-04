#include <stdio.h>
#include <stdlib.h>

void test_fgetc(FILE *file_arg) {
  int i = 10;
  printf("output char as:");
  while (i-- > 0) {
    int c = fgetc(file_arg);
    printf(" %d-%c", c, (unsigned char)c);
  }
  printf("\n");
}

void test_fputc(FILE *file_out, FILE *file_in) {
  int i = 10;
  printf("input char as: ");
  while (i-- > 0) {
    int c = fputc(fgetc(file_out), file_in);
    printf(" %d-%c", c, (unsigned char)c);
  }
  printf("\n");
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