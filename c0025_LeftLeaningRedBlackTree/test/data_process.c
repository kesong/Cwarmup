#include "data_process.h"
#include "test_player.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t string_size = 100;
#define NAME_LEN 10

// 读取保存数据的文件，将数据写入结构体（player）中，形成需要的数据类型
PLAYER **read_file_and_return_int_array(char *file_path, int *count,
                                        PLAYER **result_arr) {
  FILE *test_data_file = fopen(file_path, "r");
  static char player_buf[100] = {""};
  char player_temp[100] = {""};
  char *player_array[5] = {NULL};
  char *delim = ", \n";
  char *save_ptr = NULL;
  int col = 0;
  char *token = NULL;
  while (fgets(player_buf, sizeof(player_buf), test_data_file) != NULL) {
    printf("Get data from file is: %s", player_buf);
    token = strtok_r(player_buf, delim, &save_ptr);
    printf("The token is: ");
    while (token) {
      printf("%s", token);
      player_array[col] = token;
      token = strtok_r(NULL, delim, &save_ptr);
      if (token == NULL) {
        printf(".\n");
        break;
      }
      printf(", ");
      col++;
    }
    col = 0;
    strcpy((*result_arr)->pname, player_array[0]);
    (*result_arr)->pnumber = strtol((player_array[1]), 0, 0);
    (*result_arr)->salary = strtol((player_array[2]), 0, 0);
    strcpy((*result_arr)->tm->tname, player_array[3]);
    strcpy((*result_arr)->tm->city, player_array[4]);
    result_arr += 1;
    (*count)++;
  }
  fclose(test_data_file);
  return result_arr;
}

// 生成TreeNode数据，将player写入TreeNode的tree_data中
TreeNode **generate_node(PLAYER **data_in, TreeNode **node_out) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    (*node_out)->tree_data = *data_in;
    (*node_out)->left = NULL;
    (*node_out)->right = NULL;
    (*node_out)->node_color = RED_NODE;
    data_in += 1;
    node_out += 1;
  }
  return node_out;
}

// 将结构体数据组成数组，方便后续读取，在程序中传递
void init_array(PLAYER **array) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    *array = (PLAYER *)malloc(sizeof(PLAYER));
    memset(*array, 0, sizeof(PLAYER));
    (*array)->pname = (char *)malloc(sizeof(char) * NAME_LEN);
    memset((*array)->pname, 0, sizeof(char) * NAME_LEN);
    (*array)->tm = (TEAM *)malloc(sizeof(TEAM));
    memset((*array)->tm, 0, sizeof(TEAM));
    (*array)->tm->tname = (char *)malloc(sizeof(char) * NAME_LEN);
    memset((*array)->tm->tname, 0, sizeof(char) * NAME_LEN);
    (*array)->tm->city = (char *)malloc(sizeof(char) * NAME_LEN);
    memset((*array)->tm->city, 0, sizeof(char) * NAME_LEN);
    array += 1;
  }
}

// 释放在init_array中申请的空间
void free_array(PLAYER **array) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    if (array != NULL) {
      free((*array)->tm->tname);
      (*array)->tm->tname = NULL;
      free((*array)->tm->city);
      (*array)->tm->city = NULL;
      free((*array)->tm);
      (*array)->tm = NULL;
      free((*array)->pname);
      (*array)->pname = NULL;
      free(*array);
      *array = NULL;
      array += 1;
    }
  }
}

// 左倾红黑树需要的节点初始化，以数组形式保存，方便后续空间释放
void init_node_llrbtree(TreeNode **node_arr) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    *node_arr = (TreeNode *)malloc(sizeof(TreeNode));
    memset(*node_arr, 0, sizeof(TreeNode));
    node_arr += 1;
  }
}

// 释放红黑树节点申请的空间
void free_node_llrbtree(TreeNode **node_arr) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    if (node_arr != NULL) {
      // free((*node_arr)->tree_data);
      (*node_arr)->tree_data = NULL;
      (*node_arr)->left = NULL;
      (*node_arr)->right = NULL;
      free(*node_arr);
      *node_arr = NULL;
      node_arr += 1;
    }
  }
}

// 获取当前运行的程序所在目录
char *get_current_path() {
  char *program_full_path = (char *)malloc(sizeof(char) * string_size);
  memset(program_full_path, '\0', string_size);
  char *program_full_path_temp = program_full_path;
  char *program_name_str = NULL;
  char *current_path = (char *)malloc(sizeof(char) * string_size);
  memset(current_path, '\0', string_size);
  readlink("/proc/self/exe", program_full_path, string_size);
  program_name_str = strrchr(program_full_path, '/');
  strncpy(current_path, program_full_path,
          strlen(program_full_path) - strlen(program_name_str) + 1);
  free(program_full_path_temp);
  return current_path;
}

// 接收可执行程序所在目录获取test目录，因为test中保存有数据文件
char *get_test_path(char *current_path) {
  char *test_path = (char *)malloc(sizeof(char) * string_size);
  memset(test_path, '\0', string_size);
  char *test_path_temp = test_path;
  char *test_parent_path = (char *)malloc(sizeof(char) * string_size);
  memset(test_parent_path, '\0', string_size);
  strncpy(test_parent_path, current_path,
          strlen(current_path) - strlen("/build"));
  test_path = strcat(test_parent_path, "test/");
  free(test_path_temp);
  return test_path;
}

// 获取写入数据的结构体数组（player）
PLAYER **get_player_array(char *file_name, char *current_path, char *test_path,
                          char *file_path, PLAYER **result_arr) {
  current_path = get_current_path();
  test_path = get_test_path(current_path);
  file_path = strcat(test_path, file_name);
  int count = 0;
  init_array(result_arr);
  read_file_and_return_int_array(file_path, &count, result_arr);
  free(current_path);
  current_path = NULL;
  free(test_path);
  test_path = NULL;
  return result_arr;
}

// 将结构体数据写入节点，并生成节点数组，这些节点会被插入红黑树
TreeNode **get_node_array(TreeNode **node_arr, PLAYER **result_arr) {
  init_node_llrbtree(node_arr);
  generate_node(result_arr, node_arr);
  return node_arr;
}

TreeNode *convert_node_array(TreeNode **node_arr) {
  TreeNode *node_array = (TreeNode *)malloc(sizeof(TreeNode) * ARRAY_SIZE);
  memset(node_array, 0, sizeof(TreeNode) * ARRAY_SIZE);
  char *file_name = "test_data";
  char *current_path = NULL;
  char *test_path = NULL;
  char *file_path = NULL;
  PLAYER *result_arr[ARRAY_SIZE] = {NULL};
  get_player_array(file_name, current_path, test_path, file_path, result_arr);
  get_node_array(node_arr, result_arr);
  for (int i = 0; i < ARRAY_SIZE; i++) {
    (node_array + i)->tree_data = (*(node_arr + i))->tree_data;
    (node_array + i)->left = (*(node_arr + i))->left;
    (node_array + i)->right = (*(node_arr + i))->right;
    (node_array + i)->node_color = (*(node_arr + i))->node_color;
    // 释放init_node_llrbtree中malloc分配的空间
    free(*(node_arr + i));
    *(node_arr + i) = NULL;
  }
  return node_array;
}

void free_int_in_array(int **result_arr) {
  if (result_arr == NULL) {
    return;
  }
  if (**result_arr != 0) {
    return;
  }
  for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
    free(*(result_arr + i));
    *(result_arr + i) = NULL;
  }
  free(*result_arr);
  *result_arr = NULL;
}

// 释放convert_node_array中node_array分配的空间
void free_node_in_array(void *node_array) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    // 进入该函数前，执行node_array+1，node_array指针每次会移动16个字节，进入该函数后，执行node_array+1，每次只移动一个字节，指向的地址就不是我们要释放的空间
    free(((TreeNode *)(node_array + 16 * i))->tree_data);
    ((TreeNode *)(node_array + 16 * i))->tree_data = NULL;
  }
  free(node_array);
  node_array = NULL;
}
