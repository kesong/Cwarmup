#include "test_data_process.h"
#include "data_process.h"
#include "test_and_validation.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

TestResult test_get_result_array() {
  char *current_path = get_current_path();
  printf("The path of the program is: %s\n", current_path);
  char *file_name = "test_data";
  char *test_path = get_test_path(current_path);
  char *file_path = strcat(test_path, file_name);
  int count = 0;
  int *result_arr[ARRAY_SIZE] = {NULL};
  init_array(result_arr);
  printf("Get number from file is: ");
  read_file_and_return_int_array(file_path, &count, result_arr);
  printf("\n");
  assert(count == 15);
  assert(**(result_arr + 3) == 8);
  assert(**(result_arr + 14) == 1201);
  free_array(result_arr);
  free(current_path);
  free(test_path);
  return TEST_PASSED;
}

TestResult test_generate_node() {
  char *file_name = "test_data";
  char *current_path = get_current_path();
  char *test_path = get_test_path(current_path);
  char *file_path = strcat(test_path, file_name);
  int count = 0;
  int **result_arr = (int **)malloc(sizeof(int *) * ARRAY_SIZE);
  init_array(result_arr);
  printf("Get number from file is: ");
  read_file_and_return_int_array(file_path, &count, result_arr);
  printf("\n");
  NODE *node_arr[ARRAY_SIZE] = {NULL};
  init_node_sll(node_arr);
  generate_node(result_arr, node_arr);
  assert(*(int *)(*node_arr)->node_data == 0);
  assert(*(int *)(*(node_arr + 3))->node_data == 8);
  assert(*(int *)(*(node_arr + 14))->node_data == 1201);

  free(result_arr);
  free_node_sll(node_arr);
  free(current_path);
  free(test_path);
  return TEST_PASSED;
}

TestResult test_generate_node_dll() {
  char *file_name = "test_data";
  char *current_path = get_current_path();
  char *test_path = get_test_path(current_path);
  char *file_path = strcat(test_path, file_name);
  int count = 0;
  int *result_arr[ARRAY_SIZE] = {NULL};
  init_array(result_arr);
  printf("Get number from file is: ");
  read_file_and_return_int_array(file_path, &count, result_arr);
  printf("\n");
  NODE_DLL *node_arr[ARRAY_SIZE] = {NULL};
  init_node_dll_new(node_arr);
  generate_node_dll(result_arr, node_arr);
  assert(*(int *)(*node_arr)->node_data == 0);
  assert(*(int *)(*(node_arr + 3))->node_data == 8);
  assert(*(int *)(*(node_arr + 14))->node_data == 1201);

  free_node_dll_new(node_arr);
  free(current_path);
  free(test_path);
  return TEST_PASSED;
}

TestResult test_get_int_array_func() {
  char *file_name = "test_data";
  char *current_path = NULL;
  char *test_path = NULL;
  char *file_path = NULL;
  int *result_arr[ARRAY_SIZE] = {NULL};
  printf("Get int array result: ");
  get_int_array(file_name, current_path, test_path, file_path, result_arr);
  printf("\n");
  assert(**(result_arr + 3) == 8);
  assert(**(result_arr + 14) == 1201);

  free_array(result_arr);
  free(current_path);
  free(test_path);
  return TEST_PASSED;
}

TestResult test_get_node_array_func() {
  char *file_name = "test_data";
  char *current_path = NULL;
  char *test_path = NULL;
  char *file_path = NULL;
  int *result_arr[ARRAY_SIZE] = {NULL};
  NODE *node_arr[ARRAY_SIZE] = {NULL};
  printf("Get node array result: ");
  get_int_array(file_name, current_path, test_path, file_path, result_arr);
  printf("\n");
  get_node_array(node_arr, result_arr);
  assert(*(int *)(*node_arr)->node_data == 0);
  assert(*(int *)(*(node_arr + 3))->node_data == 8);
  assert(*(int *)(*(node_arr + 14))->node_data == 1201);

  free_node_sll(node_arr);
  free(current_path);
  free(test_path);
  return TEST_PASSED;
}

TestResult test_get_node_dll_array_func() {
  char *file_name = "test_data";
  char *current_path = NULL;
  char *test_path = NULL;
  char *file_path = NULL;
  int *result_arr[ARRAY_SIZE] = {NULL};
  NODE_DLL *node_arr[ARRAY_SIZE] = {NULL};
  printf("Get node_dll array result: ");
  get_int_array(file_name, current_path, test_path, file_path, result_arr);
  printf("\n");
  get_node_dll_array(node_arr, result_arr);
  assert(**(result_arr + 3) == 8);
  assert(**(result_arr + 14) == 1201);

  free_node_dll_new(node_arr);
  free_array(result_arr);
  free(current_path);
  free(test_path);
  return TEST_PASSED;
}
