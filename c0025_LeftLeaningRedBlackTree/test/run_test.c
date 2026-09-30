#include "test_and_validation.h"
#include "test_data_process.h"
#include "test_player.h"
#include <assert.h>

#define CASE_SUM 100

void run_test_suites(TestCase *test_cases, size_t test_count) {
  for (int i = 0; i < test_count; i++) {
    if (test_cases[i].case_name == NULL) {
      return;
    }
    if (test_cases[i].test_function() == TEST_PASSED) {
      log_d("%s passed.", test_cases[i].case_name);
    } else {
      log_d("%s failed.", test_cases[i].case_name);
    }
  }
}

int main(int argc, char **argv) {

  TestCase test_case[CASE_SUM] = {
      {"test get result array", test_get_result_array},
      {"test get player array", test_get_player_array_func},
      {"test generate node", test_generate_node},
      {"test get node array", test_get_node_array_func},
      {"test insert node as root node", test_insert_node_as_root_node},
      {"test insert node exist", test_insert_node_exist},
      {"test clear tree", test_clear_tree},
      {"test build llrbtree", test_build_llrbtree},
      {"test left rotate", test_left_rotate},
      {"test right rotate", test_right_rotate},
      {"test left rotate then right", test_left_rotate_then_right},
      {"test check after each insert", test_check_after_each_insert},
      //{"test preorder traversal without
      // recurse",test_preorder_traversal_without_recurse},
      //{"test preorder traversal without recurse
      // 2",test_preorder_traversal_without_recurse_2},
      //{"test inorder traversal", test_inorder_traversal},
      //{"test inorder traversal without
      // recurse",test_inorder_traversal_without_recurse},
      //{"test postorder traversal", test_postorder_traversal},
      //{"test postorder traversal without
      // recurse",test_postorder_traversal_without_recurse},
      //{"test postorder traversal without recurse
      // 2",test_postorder_traversal_without_recurse_2},
      //{"test level traversal", test_level_traversal},
  };
  run_test_suites(test_case, CASE_SUM);
}
