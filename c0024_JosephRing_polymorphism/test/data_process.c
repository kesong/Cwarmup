#include "data_process.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t string_size = 100;

int **read_file_and_return_int_array(char *file_path, int *count,
                                     int **result_arr) {
  FILE *test_data_file = fopen(file_path, "r");
  static int in_int = -65535;
  while (fscanf(test_data_file, "%d", &in_int) == 1) {
    printf("%d ", in_int);
    **result_arr = in_int;
    result_arr += 1;
    (*count)++;
  }
  // fread(result_arr, sizeof(int), count, test_data_file);
  fclose(test_data_file);
  return result_arr;
}

NODE **generate_node(int **data_in, NODE **node_out) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    (*node_out)->node_data = *data_in;
    (*node_out)->next = NULL;
    data_in += 1;
    node_out += 1;
  }
  return node_out;
}

NODE_DLL **generate_node_dll(int **data_in, NODE_DLL **node_dll_out) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    (*node_dll_out)->node_data = *data_in;
    (*node_dll_out)->prev = NULL;
    (*node_dll_out)->next = NULL;
    data_in += 1;
    node_dll_out += 1;
  }
  return node_dll_out;
}

void init_array(int **array) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    *array = (int *)malloc(sizeof(int *));
    memset(*array, -1, sizeof(int));
    array += 1;
  }
}

void free_array(int **array) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    if (array != NULL) {
      free(*array);
      *array = NULL;
      array += 1;
    }
  }
}

void init_node_sll(NODE **node_arr) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    *node_arr = (NODE *)malloc(sizeof(NODE));
    memset(*node_arr, 0, sizeof(NODE));
    node_arr += 1;
  }
}

void free_node_sll(NODE **node_arr) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    if (node_arr != NULL) {
      free((*node_arr)->node_data);
      (*node_arr)->node_data = NULL;
      (*node_arr)->next = NULL;
      free(*node_arr);
      *node_arr = NULL;
      node_arr += 1;
    }
  }
}

void init_node_dll_new(NODE_DLL **node_arr) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    *node_arr = (NODE_DLL *)malloc(sizeof(NODE_DLL));
    memset(*node_arr, 0, sizeof(NODE_DLL));
    node_arr += 1;
  }
}

void free_node_dll_new(NODE_DLL **node_arr) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    if (node_arr != NULL) {
      free((*node_arr)->node_data);
      (*node_arr)->node_data = NULL;
      (*node_arr)->prev = NULL;
      (*node_arr)->next = NULL;
      free(*node_arr);
      *node_arr = NULL;
      node_arr += 1;
    }
  }
}

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

int **get_int_array(char *file_name, char *current_path, char *test_path,
                    char *file_path, int **result_arr) {
  current_path = get_current_path();
  test_path = get_test_path(current_path);
  file_path = strcat(test_path, file_name);
  int count = 0;
  init_array(result_arr);
  printf("Get number from file is: ");
  read_file_and_return_int_array(file_path, &count, result_arr);
  printf(".\n");
  free(current_path);
  current_path = NULL;
  free(test_path);
  test_path = NULL;
  return result_arr;
}

NODE **get_node_array(NODE **node_arr, int **result_arr) {
  init_node_sll(node_arr);
  generate_node(result_arr, node_arr);
  return node_arr;
}

NODE_DLL **get_node_dll_array(NODE_DLL **node_arr, int **result_arr) {
  init_node_dll_new(node_arr);
  generate_node_dll(result_arr, node_arr);
  return node_arr;
}

NODE *convert_node_array(NODE **node_arr) {
  NODE *node_array = (NODE *)malloc(sizeof(NODE) * ARRAY_SIZE);
  memset(node_array, 0, sizeof(NODE) * ARRAY_SIZE);
  char *file_name = "test_data";
  char *current_path = NULL;
  char *test_path = NULL;
  char *file_path = NULL;
  int *result_arr[ARRAY_SIZE] = {NULL};
  get_int_array(file_name, current_path, test_path, file_path, result_arr);
  get_node_array(node_arr, result_arr);
  for (int i = 0; i < ARRAY_SIZE; i++) {
    (node_array + i)->node_data = (*(node_arr + i))->node_data;
    (node_array + i)->next = (*(node_arr + i))->next;
    // 释放init_node_sll中malloc分配的空间
    free(*(node_arr + i));
    *(node_arr + i) = NULL;
  }
  return node_array;
}

NODE_DLL *convert_node_dll_array(NODE_DLL **node_arr) {
  NODE_DLL *node_array = (NODE_DLL *)malloc(sizeof(NODE_DLL) * ARRAY_SIZE);
  memset(node_array, 0, sizeof(NODE_DLL) * ARRAY_SIZE);
  char *file_name = "test_data";
  char *current_path = NULL;
  char *test_path = NULL;
  char *file_path = NULL;
  int *result_arr[ARRAY_SIZE] = {NULL};
  get_int_array(file_name, current_path, test_path, file_path, result_arr);
  get_node_dll_array(node_arr, result_arr);
  for (int i = 0; i < ARRAY_SIZE; i++) {
    (node_array + i)->node_data = (*(node_arr + i))->node_data;
    (node_array + i)->prev = (*(node_arr + i))->prev;
    (node_array + i)->next = (*(node_arr + i))->next;
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
    free(((NODE *)(node_array + 16 * i))->node_data);
    ((NODE *)(node_array + 16 * i))->node_data = NULL;
  }
  free(node_array);
  node_array = NULL;
}

void free_node_dll_in_array(NODE_DLL *node_array) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    free(((NODE_DLL *)(node_array + i))->node_data);
    ((NODE_DLL *)(node_array + i))->node_data = NULL;
  }
  free(node_array);
  node_array = NULL;
}

// 释放single_linkedlist中init_single_linkedlist函数中convert_node_array为node_array和init_int_array中为int分配的空间
void free_node_in_sll(Linkedlist *llist) {
  void *temp_ptr = NULL;
  if (llist->head == NULL) {
    return;
  }
  temp_ptr = (NODE *)llist->head;
  // 循环链表和非循环链表在链表终点的条件判断不一样，其他都一样
  while (((NODE *)llist->head)->next != NULL) {
    free(((NODE *)llist->head)->node_data);
    ((NODE *)llist->head)->node_data = NULL;
    llist->head = ((NODE *)llist->head)->next;
  }
  // llist->head是node_array的首地址，这个node_array地址是一次申请了所有节点的地址，一旦释放，节点数组的空间就全部释放了，所以head要放在循环外，最后释放
  free(((NODE *)llist->head)->node_data);
  ((NODE *)llist->head)->node_data = NULL;
  ((NODE *)llist->head)->next = NULL;
  llist->head = temp_ptr;
  free(((NODE *)llist->head)->node_data);
  ((NODE *)llist->head)->node_data = NULL;
  ((NODE *)llist->head)->next = NULL;
  free(llist->head);
  llist->head = NULL;
}

void free_node_in_scll(Linkedlist *llist) {
  NODE *temp_ptr = NULL;
  if (llist->head == NULL) {
    return;
  }
  temp_ptr = (NODE *)llist->head;
  while (((NODE *)llist->head) != ((NODE *)llist->tail)) {
    free(((NODE *)llist->head)->node_data);
    ((NODE *)llist->head)->node_data = NULL;
    llist->head = ((NODE *)llist->head)->next;
  }
  // 释放llist->tail，此时head == tail
  free(((NODE *)llist->head)->node_data);
  ((NODE *)llist->head)->node_data = NULL;
  ((NODE *)llist->head)->next = NULL;
  // 恢复llist->head的最初值并释放
  llist->head = temp_ptr;
  free(((NODE *)llist->head)->node_data);
  ((NODE *)llist->head)->node_data = NULL;
  ((NODE *)llist->head)->next = NULL;
  free(llist->head);
  llist->head = NULL;
}

void free_node_in_dll(Linkedlist *llist) {
  void *temp_ptr = NULL;
  if (llist->head == NULL) {
    return;
  }
  // 备份链表的头指针，调用init函数初始化链表的，头指针指向node数组，一次性释放整个数组。
  temp_ptr = (NODE_DLL *)llist->head;
  // 循环链表和非循环链表在链表终点的条件判断不一样，其他都一样
  while (((NODE_DLL *)llist->head)->next != NULL) {
    free(((NODE_DLL *)llist->head)->node_data);
    ((NODE_DLL *)llist->head)->node_data = NULL;
    llist->head = ((NODE_DLL *)llist->head)->next;
  }
  // llist->head是node_array的首地址，这个node_array地址是一次申请了所有节点的地址，一旦释放，节点数组的空间就全部释放了，所以head要放在循环外，最后释放
  free(((NODE_DLL *)llist->head)->node_data);
  ((NODE_DLL *)llist->head)->node_data = NULL;
  ((NODE_DLL *)llist->head)->next = NULL;
  llist->head = temp_ptr;
  free(((NODE_DLL *)llist->head)->node_data);
  ((NODE_DLL *)llist->head)->node_data = NULL;
  ((NODE_DLL *)llist->head)->next = NULL;
  free(llist->head);
  llist->head = NULL;
}

// 双向循环链表的结构体写法跟其他不一样，无法使用(Linkedlist*)dcllist转型为父类，只能访问结构体中的super指针来访问链表成员
void free_node_in_dcll(DCLinkedList *dcllist) {
  NODE_DLL *temp_ptr = NULL;
  if (dcllist->super->head == NULL) {
    return;
  }
  temp_ptr = (NODE_DLL *)dcllist->super->head;
  while (((NODE_DLL *)dcllist->super->head) !=
         ((NODE_DLL *)dcllist->super->tail)) {
    free(((NODE_DLL *)dcllist->super->head)->node_data);
    ((NODE_DLL *)dcllist->super->head)->node_data = NULL;
    dcllist->super->head = ((NODE_DLL *)dcllist->super->head)->next;
  }
  free(((NODE_DLL *)dcllist->super->head)->node_data);
  ((NODE_DLL *)dcllist->super->head)->node_data = NULL;
  ((NODE_DLL *)dcllist->super->head)->next = NULL;
  dcllist->super->head = temp_ptr;
  free(((NODE_DLL *)dcllist->super->head)->node_data);
  ((NODE_DLL *)dcllist->super->head)->node_data = NULL;
  ((NODE_DLL *)dcllist->super->head)->next = NULL;
  free(dcllist->super->head);
  dcllist->super->head = NULL;
}
