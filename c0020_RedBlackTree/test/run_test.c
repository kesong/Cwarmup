#include "test_and_validation.h"
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
      {"test clear tree", test_clear_tree},
      {"test check color and modify", test_check_color_and_modify},
      {"test insert node as root node", test_insert_node_as_root_node},
      {"test insert node at left branch", test_insert_node_at_left_branch},
      {"test insert node exist", test_insert_node_exist},
      {"test insert node at left left branch",
       test_insert_node_at_left_left_branch},
      {"test left rotate", test_left_rotate},
      {"test right rotate", test_right_rotate},
      {"test left rotate then right", test_left_rotate_then_right},
      {"test right rotate then left", test_right_rotate_then_left},
      {"test check after every insert", test_check_after_every_insert},
      {"test insert LR rotate then root right rotate",
       test_insert_LR_rotate_then_root_right_rotate},
      {"1&3.3.1.2-root", test_delete_root_node_with_child},
      {"3.1-1", test_delete_red_node},
      {"1&3.3.1.1.2-root", test_delete_root_node_with_two_black_child},
      {"3.2.1.1.1",
       test_delete_black_node_without_child_at_left_with_red_father},
      {"3.3.1.1.1",
       test_delete_black_node_without_child_at_right_with_red_father},
      {"3.2.2.2&3.2.1.3",
       test_delete_black_node_without_child_have_red_brother},
      {"3.2.1.2-1",
       test_delete_black_node_is_root_at_left_and_the_brother_have_red_right_child},
      {"3.2.1.2-2",
       test_delete_black_node_at_left_and_the_brother_have_red_right_child},
      {"3.2.1.3",
       test_delete_black_node_at_left_and_the_brother_have_red_left_child},
      {"3.2.1.4",
       test_delete_black_node_at_left_and_the_brother_have_red_left_right_child},
      {"3.3.1.4",
       test_delete_black_node_at_right_and_the_brother_have_red_left_right_child},
      {"3.2.2.1",
       test_delete_black_node_at_left_and_red_brother_have_left_child_with_no_grand_child},
      {"3.2.2.2",
       test_delete_black_node_at_left_and_red_brother_have_left_child_with_left_grand_child},
      {"3.2.2.3",
       test_delete_black_node_at_left_and_red_brother_have_left_child_with_right_grand_child},
      {"3.2.2.4",
       test_delete_black_node_at_left_and_red_brother_have_left_child_with_left_right_grand_child},
      {"3.3.1.1.1",
       test_delete_black_node_at_right_and_brother_have_no_child_and_red_father},
      {"3.3.1.2",
       test_delete_black_node_at_right_child_and_the_brother_have_red_left_child},
      {"3.3.1.2-2",
       test_delete_black_node_at_right_child_and_the_brother_have_red_left_child_2},
      {"3.3.1.3",
       test_delete_black_node_at_right_child_and_the_brother_have_red_right_child},
      {"3.3.2.1",
       test_delete_black_node_at_right_child_and_right_child_of_brother_have_no_child},
      {"3.3.2.2",
       test_delete_black_node_at_right_child_and_right_child_of_brother_have_left_child},
      {"3.3.2.3",
       test_delete_black_node_at_right_child_and_right_child_of_brother_have_right_child},
      {"3.3.2.4",
       test_delete_black_node_at_right_child_and_right_child_of_brother_have_left_right_child},
      {"3.2.1.1.2-1", test_delete_double_black_node_at_left_1},
      {"3.2.1.1.2-2", test_delete_double_black_node_at_left_2},
      {"3.2.1.1.2-3", test_delete_double_black_node_at_left_3},
      {"3.2.1.1.2-4", test_delete_double_black_node_at_left_4},
      {"3.3.1.1.2", test_delete_double_black_node_at_right},
      {"2.2",
       test_delete_black_node_at_right_and_have_a_single_red_right_child},
      {"2.2-1",
       test_delete_black_node_at_right_and_have_a_single_red_right_child_1},
      {"2.1-1",
       test_delete_black_node_at_left_and_have_a_single_red_left_child},
      {"2.1-2", test_delete_black_node_at_left_and_have_red_left_right_child},
      {"1&3.3", test_delete_black_node_at_right_and_the_behind_node_is_red},
      {"1&3.2.1.4",
       test_delete_black_node_at_left_and_have_two_different_color_child},
      {"1&3.1",
       test_delete_red_node_at_right_and_have_two_black_color_child_and_red_behind_node},
      {"3.1-2", test_delete_many_red_node_without_child},
      {"3.2.1.1.2-5", test_delete_double_black_node_at_left_5},
      {"3.3.1.1.2-1", test_delete_double_black_node_at_right_1},
      {"3.2.1.1.2-6", test_delete_double_black_node_at_left_6},
      {"test build tree by name", test_build_player_tree_by_name},

      {"test preorder traversal without recurse",
       test_preorder_traversal_without_recurse},
      {"test preorder traversal without recurse 2",
       test_preorder_traversal_without_recurse_2},
      {"test inorder traversal", test_inorder_traversal},
      {"test inorder traversal without recurse",
       test_inorder_traversal_without_recurse},
      {"test postorder traversal", test_postorder_traversal},
      {"test postorder traversal without recurse",
       test_postorder_traversal_without_recurse},
      {"test postorder traversal without recurse 2",
       test_postorder_traversal_without_recurse_2},
      {"test level traversal", test_level_traversal}};
  run_test_suites(test_case, CASE_SUM);
}
