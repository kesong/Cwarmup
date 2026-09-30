#include "test_data_process.h"
#include "data_process.h"
#include "test_player.h"
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
  PLAYER *result_arr[ARRAY_SIZE] = {NULL};
  init_array(result_arr);
  read_file_and_return_int_array(file_path, &count, result_arr);
  assert(count == 27);
  assert(strcmp((*(result_arr + 2))->pname, "Yao") == 0);
  assert(strcmp((*(result_arr + 13))->pname, "Sharq") == 0);
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
  PLAYER **result_arr = (PLAYER **)malloc(sizeof(PLAYER *) * ARRAY_SIZE);
  init_array(result_arr);
  read_file_and_return_int_array(file_path, &count, result_arr);
  TreeNode *node_arr[ARRAY_SIZE] = {NULL};
  init_node_llrbtree(node_arr);
  generate_node(result_arr, node_arr);
  assert(strcmp((char *)((PLAYER *)(*node_arr)->tree_data)->pname, "Jordan") ==
         0);
  assert(strcmp(((PLAYER *)(*(node_arr + 2))->tree_data)->pname, "Yao") == 0);
  assert(strcmp(((PLAYER *)(*(node_arr + 13))->tree_data)->pname, "Sharq") ==
         0);

  free_array(result_arr);
  free(result_arr);
  free_node_llrbtree(node_arr);
  free(current_path);
  free(test_path);
  return TEST_PASSED;
}

TestResult test_get_player_array_func() {
  char *file_name = "test_data";
  char *current_path = NULL;
  char *test_path = NULL;
  char *file_path = NULL;
  PLAYER *result_arr[ARRAY_SIZE] = {NULL};
  get_player_array(file_name, current_path, test_path, file_path, result_arr);
  assert(strcmp((*(result_arr + 2))->pname, "Yao") == 0);
  assert(strcmp((*(result_arr + 13))->pname, "Sharq") == 0);

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
  PLAYER *result_arr[ARRAY_SIZE] = {NULL};
  TreeNode *node_arr[ARRAY_SIZE] = {NULL};
  get_player_array(file_name, current_path, test_path, file_path, result_arr);
  get_node_array(node_arr, result_arr);
  assert(strcmp((char *)((PLAYER *)(*node_arr)->tree_data)->pname, "Jordan") ==
         0);
  assert(strcmp(((PLAYER *)(*(node_arr + 2))->tree_data)->pname, "Yao") == 0);
  assert(strcmp(((PLAYER *)(*(node_arr + 13))->tree_data)->pname, "Sharq") ==
         0);

  free_array(result_arr);
  free_node_llrbtree(node_arr);
  free(current_path);
  free(test_path);
  return TEST_PASSED;
}
