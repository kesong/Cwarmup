#include "test_and_validation.h"
#include "../include/log.h"
// #include "../src/print_ADT.h"
#include "test_player.h"

void test_preorder_traversal_without_recurse() {
  TreeNode *test_start_node = build_player_tree_by_name();
  log_i("(VLR)preorder traversal without recurse result is (first method): \n");
  // print_tree_in_specified_order(test_start_node,
  // &preorder_traversal_without_recurse);
}

void test_preorder_traversal_without_recurse_2() {
  TreeNode *test_start_node = build_player_tree_by_name();
  log_i("(VLR)preorder traversal without recurse result is (second method): "
        "\n");
  // print_tree_in_specified_order(test_start_node,
  // &preorder_traversal_without_recurse_2);
}

void test_inorder_traversal() {
  TreeNode *test_start_node = build_player_tree_by_name();
  log_i("(LVR)inorder traversal result is: \n");
  // print_tree_in_specified_order(test_start_node, &inorder_traversal);
}

void test_inorder_traversal_without_recurse() {
  TreeNode *test_start_node = build_player_tree_by_name();
  log_i("(LVR)inorder traversal without recurse result is: \n");
  // print_tree_in_specified_order(test_start_node,
  // &inorder_traversal_without_recurse);
}

void test_postorder_traversal() {
  TreeNode *test_start_node = build_player_tree_by_name();
  log_i("(LRV)postorder traversal result is: \n");
  // print_tree_in_specified_order(test_start_node, &postorder_traversal);
}

void test_postorder_traversal_without_recurse() {
  TreeNode *test_start_node = build_player_tree_by_name();
  log_i("(LRV)postorder traversal without recurse result is: \n");
  // print_tree_in_specified_order(test_start_node,
  // &postorder_traversal_without_recurse);
}

void test_postorder_traversal_without_recurse_2() {
  TreeNode *test_start_node = build_player_tree_by_name();
  log_i("(LRV)postorder traversal without recurse result is: \n");
  // print_tree_in_specified_order(test_start_node,
  // &postorder_traversal_without_recurse_2);
}

void test_mixedorder_traversal_without_recurse() {
  TreeNode *test_start_node = build_player_tree_by_name();
  log_i("(LRV)mixedorder traversal without recurse result is: \n");
  // print_tree_in_specified_order(test_start_node,
  // &mixedorder_traversal_without_recurse);
}

void test_level_traversal() {
  TreeNode *test_start_node = build_player_tree_by_name();
  log_i("level traversal result is: \n");
  // print_tree_in_specified_order(test_start_node, &level_traversal);
}
