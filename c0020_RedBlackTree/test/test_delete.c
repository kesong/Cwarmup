#include "../include/log.h"
#include "test_and_validation.h"
// #include "../src/print_ADT.h"
#include "test_player.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

extern TreeNode *root_node;
extern TreeNode *jordan_node;
extern TreeNode *edwards_node;
extern TreeNode *curry_node;
extern TreeNode *dunken_node;
extern TreeNode *sga_node;
extern TreeNode *iverson_node;
extern TreeNode *book_node;
extern TreeNode *yang_node;
extern TreeNode *yao_node;
extern TreeNode *jokic_node;
extern TreeNode *yi_node;
extern TreeNode *jimmy_node;
extern TreeNode *rodman_node;
extern TreeNode *kobe_node;
extern TreeNode *camelo_node;
extern TreeNode *paul_node;
extern TreeNode *sharq_node;
extern TreeNode *hill_node;
extern TreeNode *klay_node;
extern TreeNode *durant_node;
extern TreeNode *lebron_node;
extern TreeNode *wade_node;
extern TreeNode *macgrady_node;
extern TreeNode *doncic_node;
extern TreeNode *carter_node;
extern TreeNode *chris_node;
extern TreeNode *kawhi_node;

// 1&3.3.1.2-root
// 被删除节点为根节点，且有左右两个子节点，子节点均为黑色，左边子节点有一个红色左子节点
TestResult test_delete_root_node_with_child() {
  clear_tree(root_node);
  TreeNode *test_root = NULL;
  test_root = build_tree_manualy(test_root);
  if (test_root == NULL) {
    log_e("Didn't get right tree node.");
    return TEST_FAILED;
  }
  insert_node(curry_node);
  delete_node(jordan_node);
  PLAYER *root_player = (PLAYER *)root_node->tree_data;
  char *root_player_name = root_player->pname;
  assert(strcmp(root_player_name, "Edwards") == 0);
  assert(curry_node->node_color == BLACK_NODE);
  assert(edwards_node->node_color == BLACK_NODE);
  assert(sga_node->node_color == BLACK_NODE);
  free_nodes();
  return TEST_PASSED;
}

// 3.1
//  被删除节点为红色节点，且没有子节点
TestResult test_delete_red_node() {
  clear_tree(root_node);
  TreeNode *test_root = NULL;
  test_root = build_tree_manualy(test_root);
  if (test_root == NULL) {
    log_e("Didn't get right tree node.");
    return TEST_FAILED;
  }
  insert_node(curry_node);
  delete_node(curry_node);
  assert(edwards_node->left == NULL);
  assert(edwards_node->node_color == BLACK_NODE);
  assert(jordan_node->right->node_color == BLACK_NODE);
  assert(jordan_node->node_color == BLACK_NODE);
  free_nodes();
  return TEST_PASSED;
}

// 1&3.3.1.1.2-root
// 被删除节点为根节点，且有两个黑色子节点，两个子节点没有子节点了（根节点没有孙节点）,替代节点在右子树
// 转换成被删除节点在右子树，且兄弟节点为黑色
TestResult test_delete_root_node_with_two_black_child() {
  clear_tree(root_node);
  TreeNode *test_root = NULL;
  test_root = build_tree_manualy(test_root);
  if (test_root == NULL) {
    log_e("Didn't get right tree node.");
    return TEST_FAILED;
  }
  insert_node(curry_node);
  delete_node(curry_node);
  delete_node(jordan_node);
  PLAYER *root_player = (PLAYER *)root_node->tree_data;
  char *root_player_name = root_player->pname;
  PLAYER *root_left_player = (PLAYER *)root_node->left->tree_data;
  char *root_left_player_name = root_left_player->pname;
  assert(strcmp(root_player_name, "Sga") == 0);
  assert(root_node->left->node_color == RED_NODE);
  assert(strcmp(root_left_player_name, "Edwards") == 0);
  assert(root_node->right == NULL);
  free_nodes();
  return TEST_PASSED;
}

// 3.2.1.1.1
//  被删节点和兄弟节点均为黑色，且都没有子节点，父节点为红色，被删除节点在左子树
TestResult test_delete_black_node_without_child_at_left_with_red_father() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(durant_node);
  insert_node(sharq_node);
  insert_node(kobe_node);
  insert_node(yi_node);
  insert_node(kawhi_node);
  assert(kobe_node->left == kawhi_node);
  assert(sharq_node->node_color == RED_NODE);
  assert(kobe_node->node_color == BLACK_NODE);
  assert(yi_node->node_color == BLACK_NODE);
  delete_node(kawhi_node);
  assert(sharq_node->node_color == RED_NODE);
  assert(kobe_node->node_color == BLACK_NODE);
  assert(yi_node->node_color == BLACK_NODE);
  delete_node(kobe_node);
  assert(sharq_node->left == NULL);
  assert(sharq_node->right->node_color == RED_NODE);
  assert(sharq_node->node_color == BLACK_NODE);
  free_nodes();
  return TEST_PASSED;
}

// 3.3.1.1.1, 3.2.1.1.1
//  被删节点和兄弟节点均为黑色，且都没有子节点，父节点为红色，被删除节点在右子树
TestResult test_delete_black_node_without_child_at_right_with_red_father() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(durant_node);
  insert_node(sharq_node);
  insert_node(kobe_node);
  insert_node(yi_node);
  insert_node(kawhi_node);
  assert(kobe_node->left == kawhi_node);
  assert(sharq_node->node_color == RED_NODE);
  assert(kobe_node->node_color == BLACK_NODE);
  assert(yi_node->node_color == BLACK_NODE);
  delete_node(kawhi_node);
  assert(sharq_node->node_color == RED_NODE);
  assert(kobe_node->node_color == BLACK_NODE);
  assert(yi_node->node_color == BLACK_NODE);
  delete_node(yi_node);
  assert(sharq_node->right == NULL);
  assert(sharq_node->left->node_color == RED_NODE);
  assert(sharq_node->node_color == BLACK_NODE);
  free_nodes();
  return TEST_PASSED;
}

// 3.2.2.2, 3.2.1.3, 3.2.1.2
// 被删除节点为黑色，在左子树，没有子节点，兄弟节点为红色，兄弟节点的左节点有红色子节点
TestResult test_delete_black_node_without_child_have_red_brother() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(durant_node);
  insert_node(sharq_node);
  insert_node(kobe_node);
  insert_node(yi_node);
  insert_node(kawhi_node);
  assert(kobe_node->left == kawhi_node);
  assert(sharq_node->node_color == RED_NODE);
  assert(kobe_node->node_color == BLACK_NODE);
  assert(yi_node->node_color == BLACK_NODE);
  delete_node(durant_node);
  assert(root_node == sharq_node);
  assert(root_node->left == kawhi_node);
  assert(root_node->left->node_color == RED_NODE);
  assert(root_node->right == yi_node);
  assert(root_node->left->left == jordan_node);
  assert(root_node->left->right == kobe_node);
  assert(kawhi_node->right == kobe_node);
  assert(kawhi_node->left->node_color == BLACK_NODE);
  assert(kawhi_node->right->node_color == BLACK_NODE);
  delete_node(kawhi_node);
  assert(sharq_node->left->node_color == BLACK_NODE);
  assert(sharq_node->left->left->node_color == RED_NODE);
  assert(kobe_node->node_color == BLACK_NODE);
  assert(yi_node->node_color == BLACK_NODE);
  char *sharq_left_name =
      (char *)((PLAYER *)sharq_node->left->tree_data)->pname;
  assert(strcmp(sharq_left_name, "Kobe") == 0);
  char *kobe_left_name =
      (char *)((PLAYER *)sharq_node->left->left->tree_data)->pname;
  assert(strcmp(kobe_left_name, "Jordan") == 0);
  free_nodes();
  return TEST_PASSED;
}

// 3.2.1.2-1, 被删除节点没有子节点
//  被删除节点在左子树为黑色节点（父节点为根节点），兄弟节点为黑色，且右子节点为红色子节点
TestResult
test_delete_black_node_is_root_at_left_and_the_brother_have_red_right_child() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(edwards_node);
  insert_node(rodman_node);
  insert_node(yao_node);
  delete_node(edwards_node);
  assert(root_node == rodman_node);
  assert(root_node->left == jordan_node);
  assert(root_node->right == yao_node);
  assert(yao_node->node_color == BLACK_NODE);
  free_nodes();
  return TEST_PASSED;
}

// 3.2.1.2-2，被删除节点没有子节点
//  被删除节点在左子树为黑色节点(父节点不是根节点)，兄弟节点为黑色，且右子节点为红色子节点
TestResult
test_delete_black_node_at_left_and_the_brother_have_red_right_child() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(edwards_node);
  insert_node(rodman_node);
  insert_node(yao_node);
  insert_node(macgrady_node);
  insert_node(camelo_node);
  insert_node(iverson_node);
  insert_node(jimmy_node);
  assert(root_node->left->node_color == RED_NODE);
  assert(iverson_node->node_color == BLACK_NODE);
  assert(edwards_node->right == iverson_node);
  assert(root_node->right->left->node_color == RED_NODE);
  assert(root_node->right->right->node_color == RED_NODE);
  delete_node(camelo_node);
  assert(root_node->left == iverson_node);
  assert(iverson_node->node_color == RED_NODE);
  assert(iverson_node->left == edwards_node);
  free_nodes();
  return TEST_PASSED;
}

// 3.2.1.3-1
//   被删除节点在左子树为黑色节点(为根节点)，兄弟节点为黑色，且左子节点为红色子节点
TestResult
test_delete_black_node_at_left_is_root_and_the_brother_have_red_left_child() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(edwards_node);
  insert_node(sharq_node);
  insert_node(rodman_node);
  delete_node(edwards_node);
  assert(root_node == rodman_node);
  assert(root_node->left == jordan_node);
  assert(root_node->right == sharq_node);
  assert(root_node->right->node_color == RED_NODE);
  free_nodes();
  return TEST_PASSED;
}

// 3.2.1.3-2
//   被删除节点在左子树为黑色节点，兄弟节点为黑色，且左子节点为红色子节点
TestResult
test_delete_black_node_at_left_and_the_brother_have_red_left_child() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(edwards_node);
  insert_node(rodman_node);
  insert_node(yao_node);
  insert_node(macgrady_node);
  insert_node(camelo_node);
  insert_node(iverson_node);
  insert_node(hill_node);
  assert(root_node->left->node_color == RED_NODE);
  assert(iverson_node->node_color == BLACK_NODE);
  assert(edwards_node->right == iverson_node);
  assert(root_node->right->left->node_color == RED_NODE);
  assert(root_node->right->right->node_color == RED_NODE);
  delete_node(camelo_node);
  assert(root_node->left == hill_node);
  assert(hill_node->node_color == RED_NODE);
  assert(hill_node->left == edwards_node);
  assert(hill_node->left->node_color == BLACK_NODE);
  assert(hill_node->right == iverson_node);
  assert(hill_node->right->node_color == BLACK_NODE);
  free_nodes();
  return TEST_PASSED;
}

// 3.2.1.4，被删除节点没有子节点
//  被删除节点在左子树为黑色节点(父节点不是根节点)，兄弟节点为黑色，且左右子节点为红色子节点
TestResult
test_delete_black_node_at_left_and_the_brother_have_red_left_right_child() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(edwards_node);
  insert_node(rodman_node);
  insert_node(yao_node);
  insert_node(macgrady_node);
  insert_node(camelo_node);
  insert_node(iverson_node);
  insert_node(jimmy_node);
  insert_node(hill_node);
  assert(root_node->left->node_color == RED_NODE);
  assert(iverson_node->node_color == BLACK_NODE);
  assert(edwards_node->right == iverson_node);
  assert(root_node->right->left->node_color == RED_NODE);
  assert(root_node->right->right->node_color == RED_NODE);
  delete_node(camelo_node);
  assert(root_node->left == iverson_node);
  assert(iverson_node->node_color == RED_NODE);
  assert(iverson_node->left == edwards_node);
  free_nodes();
  return TEST_PASSED;
}

// 3.2.2.1
// 被删除节点在左子树为黑色，兄弟节点为红色，且左节点没有子节点
TestResult
test_delete_black_node_at_left_and_red_brother_have_left_child_with_no_grand_child() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(durant_node);
  insert_node(macgrady_node);
  insert_node(yao_node);
  insert_node(camelo_node);
  insert_node(iverson_node);
  insert_node(jimmy_node);
  insert_node(hill_node);
  insert_node(kobe_node);
  insert_node(kawhi_node);
  insert_node(edwards_node);
  assert(root_node == jordan_node);
  assert(root_node->left == durant_node);
  assert(root_node->right == macgrady_node);
  assert(durant_node->right == iverson_node);
  assert(durant_node->right->node_color == RED_NODE);
  assert(durant_node->left->node_color == BLACK_NODE);
  assert(hill_node->left == edwards_node);
  delete_node(edwards_node);
  assert(hill_node->left == NULL);
  delete_node(camelo_node);
  assert(root_node == jordan_node);
  assert(root_node->left == iverson_node);
  assert(root_node->left->node_color == BLACK_NODE);
  assert(durant_node->right == hill_node);
  assert(durant_node->right->node_color == RED_NODE);
  free_nodes();
  return TEST_PASSED;
}

// 3.2.2.2
// 被删除节点在左子树为黑色，兄弟节点为红色，且左节点只有一个左子节点
TestResult
test_delete_black_node_at_left_and_red_brother_have_left_child_with_left_grand_child() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(durant_node);
  insert_node(macgrady_node);
  insert_node(yao_node);
  insert_node(camelo_node);
  insert_node(iverson_node);
  insert_node(jimmy_node);
  insert_node(hill_node);
  insert_node(kobe_node);
  insert_node(kawhi_node);
  insert_node(edwards_node);
  delete_node(camelo_node);
  assert(root_node == jordan_node);
  assert(root_node->left == iverson_node);
  assert(root_node->left->left == edwards_node);
  assert(root_node->left->left->node_color == RED_NODE);
  assert(edwards_node->left == durant_node);
  assert(edwards_node->right == hill_node);
  free_nodes();
  return TEST_PASSED;
}

// 3.2.2.3
// 被删除节点在左子树为黑色，兄弟节点为红色，且左节点只有一个右子节点
TestResult
test_delete_black_node_at_left_and_red_brother_have_left_child_with_right_grand_child() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(camelo_node);
  insert_node(rodman_node);
  insert_node(yang_node);
  insert_node(book_node);
  insert_node(dunken_node);
  insert_node(kobe_node);
  insert_node(curry_node);
  insert_node(hill_node);
  insert_node(doncic_node);
  assert(root_node == dunken_node);
  assert(root_node->left == camelo_node);
  assert(root_node->right == jordan_node);
  assert(root_node->left->node_color == RED_NODE);
  assert(root_node->right->node_color == RED_NODE);
  assert(jordan_node->left == hill_node);
  assert(camelo_node->right == curry_node);
  assert(jordan_node->right == rodman_node);
  insert_node(paul_node);
  assert(root_node->right->node_color == BLACK_NODE);
  assert(jordan_node->right->node_color == RED_NODE);
  assert(rodman_node->left == kobe_node);
  assert(rodman_node->right == yang_node);
  delete_node(hill_node);
  assert(root_node == dunken_node);
  assert(root_node->right == rodman_node);
  assert(rodman_node->left == kobe_node);
  assert(rodman_node->node_color == BLACK_NODE);
  assert(kobe_node->node_color == RED_NODE);
  assert(kobe_node->left == jordan_node);
  free_nodes();
  return TEST_PASSED;
}

// 3.2.2.4
// 被删除节点在左子树为黑色，兄弟节点为红色，且左节点有左右两个节点
TestResult
test_delete_black_node_at_left_and_red_brother_have_left_child_with_left_right_grand_child() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(camelo_node);
  insert_node(rodman_node);
  insert_node(yang_node);
  insert_node(book_node);
  insert_node(dunken_node);
  insert_node(kobe_node);
  insert_node(kawhi_node);
  insert_node(curry_node);
  insert_node(hill_node);
  insert_node(carter_node);
  insert_node(doncic_node);
  assert(root_node == jordan_node);
  assert(root_node->left == camelo_node);
  assert(root_node->right == rodman_node);
  assert(root_node->left->node_color == BLACK_NODE);
  assert(root_node->right->node_color == BLACK_NODE);
  assert(root_node->right->node_color == BLACK_NODE);
  assert(root_node->left->right == dunken_node);
  assert(root_node->left->right->node_color == RED_NODE);
  delete_node(book_node);
  assert(root_node->left == dunken_node);
  assert(root_node->left->node_color == BLACK_NODE);
  assert(root_node->left->left == curry_node);
  assert(root_node->left->left->node_color == RED_NODE);
  assert(dunken_node->right == hill_node);
  assert(dunken_node->right->node_color == BLACK_NODE);
  assert(camelo_node->right == carter_node);
  assert(curry_node->right == doncic_node);
  assert(curry_node->right->node_color == BLACK_NODE);
  assert(curry_node->left == camelo_node);
  free_nodes();
  return TEST_PASSED;
}

// 3.3.1.1.1
// 被删除节点在右子树为黑色，兄弟节点为黑色，被删除节点和兄弟节点均无子节点，父节点为红色
TestResult
test_delete_black_node_at_right_and_brother_have_no_child_and_red_father() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(camelo_node);
  insert_node(rodman_node);
  insert_node(yang_node);
  insert_node(book_node);
  insert_node(dunken_node);
  insert_node(kobe_node);
  insert_node(kawhi_node);
  insert_node(curry_node);
  insert_node(hill_node);
  insert_node(carter_node);
  insert_node(doncic_node);
  delete_node(book_node);
  delete_node(carter_node);
  assert(root_node == jordan_node);
  assert(root_node->left == dunken_node);
  assert(root_node->right == rodman_node);
  assert(root_node->left->node_color == BLACK_NODE);
  assert(root_node->right->node_color == BLACK_NODE);
  assert(root_node->left->left->right == doncic_node);
  delete_node(doncic_node);
  assert(root_node == jordan_node);
  assert(root_node->left == dunken_node);
  assert(root_node->right == rodman_node);
  assert(root_node->left->left == curry_node);
  assert(root_node->left->left->node_color == BLACK_NODE);
  assert(root_node->left->left->left == camelo_node);
  assert(root_node->left->left->left->node_color == RED_NODE);
  assert(root_node->left->left->right == NULL);
  free_nodes();
  return TEST_PASSED;
}

// 3.3.1.2
//  被删除节点在右子树为黑色节点，兄弟节点为黑色，且左子节点为红色子节点
TestResult
test_delete_black_node_at_right_child_and_the_brother_have_red_left_child() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(camelo_node);
  insert_node(rodman_node);
  insert_node(yang_node);
  insert_node(book_node);
  insert_node(dunken_node);
  insert_node(kobe_node);
  insert_node(kawhi_node);
  insert_node(curry_node);
  insert_node(hill_node);
  insert_node(carter_node);
  insert_node(doncic_node);
  delete_node(book_node);
  delete_node(yang_node);
  assert(root_node == jordan_node);
  assert(root_node->left == dunken_node);
  assert(root_node->right == kobe_node);
  assert(root_node->right->left == kawhi_node);
  assert(root_node->right->right == rodman_node);
  assert(root_node->right->left->node_color == BLACK_NODE);
  assert(root_node->right->right->node_color == BLACK_NODE);
  free_nodes();
  return TEST_PASSED;
}

// 3.3.1.2-2
//  被删除节点在右子树为黑色，兄弟节点为红色，且右子节点只有左子节点
TestResult
test_delete_black_node_at_right_child_and_the_brother_have_red_left_child_2() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(camelo_node);
  insert_node(rodman_node);
  insert_node(yang_node);
  insert_node(book_node);
  insert_node(dunken_node);
  insert_node(kobe_node);
  insert_node(kawhi_node);
  insert_node(curry_node);
  insert_node(hill_node);
  insert_node(doncic_node);
  delete_node(book_node);
  if (book_node->node_color == BLACK_NODE) {
    book_node->node_color = RED_NODE;
  }
  insert_node(book_node);
  delete_node(doncic_node);
  assert(root_node == jordan_node);
  assert(root_node->left == dunken_node);
  assert(root_node->right == rodman_node);
  assert(root_node->left->node_color == BLACK_NODE);
  assert(root_node->right->node_color == BLACK_NODE);
  assert(root_node->left->left == camelo_node);
  assert(root_node->left->left->node_color == RED_NODE);
  assert(root_node->left->right == hill_node);
  assert(root_node->left->right->node_color == BLACK_NODE);
  assert(camelo_node->left == book_node);
  assert(camelo_node->left->node_color == BLACK_NODE);
  assert(camelo_node->right == curry_node);
  assert(camelo_node->right->node_color == BLACK_NODE);
  free_nodes();
  return TEST_PASSED;
}

// 3.3.1.3
//  被删除节点在右子树为黑色节点，兄弟节点为黑色，且右子节点为红色子节点
TestResult
test_delete_black_node_at_right_child_and_the_brother_have_red_right_child() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(camelo_node);
  insert_node(rodman_node);
  insert_node(yang_node);
  insert_node(book_node);
  insert_node(dunken_node);
  insert_node(kobe_node);
  insert_node(kawhi_node);
  insert_node(curry_node);
  insert_node(hill_node);
  insert_node(carter_node);
  insert_node(doncic_node);
  delete_node(book_node);
  delete_node(kawhi_node);
  assert(root_node->right == rodman_node);
  assert(root_node->right->left == kobe_node);
  assert(root_node->right->left->left == NULL);
  assert(root_node->right->left->right == NULL);
  assert(root_node->right->right == yang_node);
  assert(root_node->right->left->node_color == BLACK_NODE);
  assert(root_node->right->right->node_color == BLACK_NODE);
  insert_node(macgrady_node);
  assert(root_node->right->left->right == macgrady_node);
  assert(root_node->right->right == yang_node);
  assert(root_node->right->left->node_color == BLACK_NODE);
  assert(root_node->right->right->node_color == BLACK_NODE);
  delete_node(yang_node);
  assert(root_node == jordan_node);
  assert(root_node->right == macgrady_node);
  assert(root_node->right->left == kobe_node);
  assert(root_node->right->right == rodman_node);
  assert(root_node->right->right->right == NULL);
  assert(root_node->right->node_color == BLACK_NODE);
  assert(root_node->right->left->node_color == BLACK_NODE);
  assert(root_node->right->right->node_color == BLACK_NODE);
  free_nodes();
  return TEST_PASSED;
}

// 3.3.1.4
//  被删除节点在右子树为黑色节点，兄弟节点为黑色，且左右子节点为红色子节点
TestResult
test_delete_black_node_at_right_and_the_brother_have_red_left_right_child() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(durant_node);
  insert_node(sharq_node);
  insert_node(kobe_node);
  insert_node(yi_node);
  insert_node(kawhi_node);
  insert_node(rodman_node);
  delete_node(yi_node);
  char *root_right_player =
      (char *)((PLAYER *)root_node->right->tree_data)->pname;
  assert(strcmp(root_right_player, "Kobe") == 0);
  char *kobe_right_player =
      (char *)((PLAYER *)kobe_node->right->tree_data)->pname;
  assert(strcmp(kobe_right_player, "Sharq") == 0);
  char *Sharq_left_player =
      (char *)((PLAYER *)sharq_node->left->tree_data)->pname;
  assert(strcmp(Sharq_left_player, "Rodman") == 0);
  assert(kobe_node->left == kawhi_node);
  assert(kobe_node->left->node_color == BLACK_NODE);
  assert(sharq_node->left->node_color == RED_NODE);
  assert(root_node->right->node_color == RED_NODE);
  free_nodes();
  return TEST_PASSED;
}

// 3.3.2.1
//  被删除节点在右子树为黑色，兄弟节点为红色，且右子节点没有子节点
TestResult
test_delete_black_node_at_right_child_and_right_child_of_brother_have_no_child() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(camelo_node);
  insert_node(rodman_node);
  insert_node(yang_node);
  insert_node(book_node);
  insert_node(dunken_node);
  insert_node(kobe_node);
  insert_node(kawhi_node);
  insert_node(curry_node);
  insert_node(hill_node);
  insert_node(carter_node);
  insert_node(doncic_node);
  delete_node(book_node);
  delete_node(doncic_node);
  assert(root_node == jordan_node);
  assert(root_node->left == dunken_node);
  assert(root_node->right == rodman_node);
  assert(root_node->left->node_color == BLACK_NODE);
  assert(root_node->right->node_color == BLACK_NODE);
  assert(root_node->left->left == carter_node);
  assert(root_node->left->left->node_color == RED_NODE);
  assert(root_node->left->right == hill_node);
  assert(root_node->left->right->node_color == BLACK_NODE);
  assert(carter_node->left == camelo_node);
  assert(carter_node->left->node_color == BLACK_NODE);
  assert(carter_node->right == curry_node);
  assert(carter_node->right->node_color == BLACK_NODE);
  free_nodes();
  return TEST_PASSED;
}

// 3.3.2.2
//  被删除节点在右子树为黑色，兄弟节点为红色，且右子节点只有左子节点
TestResult
test_delete_black_node_at_right_child_and_right_child_of_brother_have_left_child() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(camelo_node);
  insert_node(rodman_node);
  insert_node(yang_node);
  insert_node(book_node);
  insert_node(dunken_node);
  insert_node(kobe_node);
  insert_node(kawhi_node);
  insert_node(curry_node);
  insert_node(hill_node);
  insert_node(doncic_node);
  delete_node(book_node);
  insert_node(paul_node);
  insert_node(macgrady_node);
  delete_node(yang_node);
  assert(root_node == jordan_node);
  assert(root_node->left == dunken_node);
  assert(root_node->right == kobe_node);
  assert(root_node->left->node_color == BLACK_NODE);
  assert(root_node->right->node_color == BLACK_NODE);
  assert(root_node->right->left == kawhi_node);
  assert(root_node->right->left->node_color == BLACK_NODE);
  assert(root_node->right->right == paul_node);
  assert(root_node->right->right->node_color == RED_NODE);
  assert(paul_node->left == macgrady_node);
  assert(paul_node->left->node_color == BLACK_NODE);
  assert(paul_node->right == rodman_node);
  assert(paul_node->right->node_color == BLACK_NODE);
  free_nodes();
  return TEST_PASSED;
}

// 3.3.2.3
//  被删除节点在右子树为黑色，兄弟节点为红色，且右子节点只有右子节点
TestResult
test_delete_black_node_at_right_child_and_right_child_of_brother_have_right_child() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(camelo_node);
  insert_node(rodman_node);
  insert_node(yang_node);
  insert_node(book_node);
  insert_node(dunken_node);
  insert_node(kobe_node);
  insert_node(kawhi_node);
  insert_node(curry_node);
  insert_node(hill_node);
  insert_node(doncic_node);
  delete_node(book_node);
  insert_node(macgrady_node);
  insert_node(paul_node);
  delete_node(yang_node);
  assert(root_node == jordan_node);
  assert(root_node->left == dunken_node);
  assert(root_node->right == kobe_node);
  assert(root_node->left->node_color == BLACK_NODE);
  assert(root_node->right->node_color == BLACK_NODE);
  assert(root_node->right->left == kawhi_node);
  assert(root_node->right->left->node_color == BLACK_NODE);
  assert(root_node->right->right == paul_node);
  assert(root_node->right->right->node_color == RED_NODE);
  assert(paul_node->left == macgrady_node);
  assert(paul_node->left->node_color == BLACK_NODE);
  assert(paul_node->right == rodman_node);
  assert(paul_node->right->node_color == BLACK_NODE);
  free_nodes();
  return TEST_PASSED;
}

// 3.3.2.4
//  被删除节点在右子树为黑色，兄弟节点为红色，且右子节点有左右子节点
TestResult
test_delete_black_node_at_right_child_and_right_child_of_brother_have_left_right_child() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(camelo_node);
  insert_node(rodman_node);
  insert_node(yang_node);
  insert_node(book_node);
  insert_node(dunken_node);
  insert_node(kobe_node);
  insert_node(kawhi_node);
  insert_node(curry_node);
  insert_node(hill_node);
  insert_node(doncic_node);
  delete_node(book_node);
  insert_node(macgrady_node);
  insert_node(paul_node);
  insert_node(lebron_node);
  delete_node(yang_node);
  assert(root_node == jordan_node);
  assert(root_node->left == dunken_node);
  assert(root_node->right == kobe_node);
  assert(root_node->left->node_color == BLACK_NODE);
  assert(root_node->right->node_color == BLACK_NODE);
  assert(root_node->right->left == kawhi_node);
  assert(root_node->right->left->node_color == BLACK_NODE);
  assert(root_node->right->right == macgrady_node);
  assert(root_node->right->right->node_color == RED_NODE);
  assert(macgrady_node->left == lebron_node);
  assert(macgrady_node->left->node_color == BLACK_NODE);
  assert(macgrady_node->right == rodman_node);
  assert(macgrady_node->right->node_color == BLACK_NODE);
  assert(macgrady_node->right->left == paul_node);
  assert(macgrady_node->right->left->node_color == RED_NODE);
  free_nodes();
  return TEST_PASSED;
}

// 3.2.1.1.2-1
//  删除双黑节点
//  最简单的双黑节点，一共三个节点，根节点，左右两个子节点均为黑，删除左边的黑色子节点
TestResult test_delete_double_black_node_at_left_1() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(edwards_node);
  insert_node(sharq_node);
  insert_node(rodman_node);
  delete_node(rodman_node);
  assert(root_node == jordan_node);
  assert(root_node->left == edwards_node);
  assert(root_node->right == sharq_node);
  assert(root_node->left->node_color == BLACK_NODE);
  assert(root_node->right->node_color == BLACK_NODE);
  delete_node(sharq_node);
  assert(root_node == jordan_node);
  assert(root_node->left == edwards_node);
  assert(root_node->left->node_color == RED_NODE);
  assert(root_node->right == NULL);
  free_nodes();
  return TEST_PASSED;
}

// 3.2.1.1.2-2
//  删除双黑节点
//  最简单的双黑节点，一共三个节点，根节点，左右两个子节点均为黑，删除右边的黑色子节点
TestResult test_delete_double_black_node_at_left_2() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(edwards_node);
  insert_node(sharq_node);
  insert_node(rodman_node);
  delete_node(rodman_node);
  assert(root_node == jordan_node);
  assert(root_node->left == edwards_node);
  assert(root_node->right == sharq_node);
  assert(root_node->left->node_color == BLACK_NODE);
  assert(root_node->right->node_color == BLACK_NODE);
  delete_node(edwards_node);
  assert(root_node == jordan_node);
  assert(root_node->right == sharq_node);
  assert(root_node->right->node_color == RED_NODE);
  assert(root_node->left == NULL);
  free_nodes();
  return TEST_PASSED;
}

// 3.2.1.1.2-3
//  删除双黑节点, 双黑节点在左子树
TestResult test_delete_double_black_node_at_left_3() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(durant_node);
  insert_node(macgrady_node);
  insert_node(yao_node);
  insert_node(camelo_node);
  insert_node(iverson_node);
  insert_node(jimmy_node);
  insert_node(hill_node);
  insert_node(kobe_node);
  insert_node(kawhi_node);
  insert_node(edwards_node);
  delete_node(edwards_node);
  delete_node(jimmy_node);
  assert(durant_node->right == iverson_node);
  assert(iverson_node->left == hill_node);
  assert(hill_node->node_color == RED_NODE);
  assert(iverson_node->node_color == BLACK_NODE);
  delete_node(hill_node);
  delete_node(camelo_node);
  assert(root_node == jordan_node);
  assert(jordan_node->left == durant_node);
  assert(jordan_node->right == macgrady_node);
  assert(durant_node->right == iverson_node);
  assert(iverson_node->node_color == RED_NODE);
  assert(jordan_node->right->node_color == RED_NODE);
  free_nodes();
  return TEST_PASSED;
}

// 3.2.1.1.2-4
//  删除双黑节点, 双黑节点在左子树，且有左右两个子节点
TestResult test_delete_double_black_node_at_left_4() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(durant_node);
  insert_node(macgrady_node);
  insert_node(yao_node);
  insert_node(camelo_node);
  insert_node(iverson_node);
  insert_node(jimmy_node);
  insert_node(hill_node);
  insert_node(kobe_node);
  insert_node(kawhi_node);
  insert_node(edwards_node);
  delete_node(edwards_node);
  delete_node(jimmy_node);
  assert(durant_node->right == iverson_node);
  assert(iverson_node->left == hill_node);
  assert(hill_node->node_color == RED_NODE);
  assert(iverson_node->node_color == BLACK_NODE);
  delete_node(hill_node);
  delete_node(durant_node);
  assert(root_node == jordan_node);
  char *root_left_player =
      (char *)((PLAYER *)root_node->left->tree_data)->pname;
  assert(strcmp(root_left_player, "Iverson") == 0);
  assert(jordan_node->right == macgrady_node);
  assert(root_node->left->node_color == BLACK_NODE);
  char *root_ll_player =
      (char *)((PLAYER *)root_node->left->left->tree_data)->pname;
  assert(strcmp(root_ll_player, "Camelo") == 0);
  assert(root_node->left->left->node_color == RED_NODE);
  assert(root_node->right->node_color == RED_NODE);
  free_nodes();
  return TEST_PASSED;
}
// 3.3.1.1.2
//  删除双黑节点, 双黑节点在右子树
TestResult test_delete_double_black_node_at_right() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(durant_node);
  insert_node(macgrady_node);
  insert_node(yao_node);
  insert_node(camelo_node);
  insert_node(iverson_node);
  insert_node(jimmy_node);
  insert_node(hill_node);
  insert_node(kobe_node);
  insert_node(kawhi_node);
  insert_node(edwards_node);
  delete_node(edwards_node);
  delete_node(jimmy_node);
  assert(durant_node->right == iverson_node);
  assert(iverson_node->left == hill_node);
  assert(hill_node->node_color == RED_NODE);
  assert(iverson_node->node_color == BLACK_NODE);
  delete_node(hill_node);
  delete_node(iverson_node);
  assert(root_node == jordan_node);
  assert(jordan_node->left == durant_node);
  assert(jordan_node->right == macgrady_node);
  assert(durant_node->left == camelo_node);
  assert(camelo_node->node_color == RED_NODE);
  assert(jordan_node->right->node_color == RED_NODE);
  free_nodes();
  return TEST_PASSED;
}

// 2.2, 被删除节点为黑色，在右子树，有一个红色右子节点
TestResult test_delete_black_node_at_right_and_have_a_single_red_right_child() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(durant_node);
  insert_node(sga_node);
  insert_node(curry_node);
  insert_node(hill_node);
  insert_node(kobe_node);
  insert_node(wade_node);
  insert_node(camelo_node);
  insert_node(dunken_node);
  insert_node(edwards_node);
  insert_node(jimmy_node);
  insert_node(klay_node);
  insert_node(paul_node);
  insert_node(sharq_node);
  insert_node(yao_node);
  insert_node(book_node);
  insert_node(carter_node);
  insert_node(doncic_node);
  insert_node(iverson_node);
  insert_node(jokic_node);
  insert_node(kawhi_node);
  insert_node(lebron_node);
  insert_node(rodman_node);
  insert_node(macgrady_node);
  insert_node(yang_node);
  insert_node(yi_node);
  insert_node(chris_node);
  assert(root_node->left == durant_node);
  assert(root_node->right == paul_node);
  assert(root_node->left->left->left->left == book_node);
  assert(root_node->left->left->left->node_color == RED_NODE);
  assert(root_node->left->left->left->left->node_color == BLACK_NODE);
  assert(camelo_node->node_color == RED_NODE);
  assert(camelo_node->left == book_node);
  assert(camelo_node->right == carter_node);
  assert(carter_node->right == chris_node);
  assert(carter_node->right->node_color == RED_NODE);
  assert(carter_node->left == NULL);
  assert(kobe_node->right == lebron_node);
  assert(kobe_node->node_color == BLACK_NODE);
  assert(sga_node->right == wade_node);
  assert(wade_node->node_color == RED_NODE);
  assert(chris_node->node_color == RED_NODE);
  delete_node(carter_node);
  assert(camelo_node->right == chris_node);
  assert(chris_node->right == NULL);
  assert(chris_node->node_color == BLACK_NODE);
  assert(root_node == jordan_node);
  free_nodes();
  return TEST_PASSED;
}

// 2.2-1,
// 被删除节点为黑色，在右子树，有一个红色左子节点（插入的节点和顺序与2.2完全相同，删除的节点不同）
TestResult
test_delete_black_node_at_right_and_have_a_single_red_right_child_1() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(durant_node);
  insert_node(sga_node);
  insert_node(curry_node);
  insert_node(hill_node);
  insert_node(kobe_node);
  insert_node(wade_node);
  insert_node(camelo_node);
  insert_node(dunken_node);
  insert_node(edwards_node);
  insert_node(jimmy_node);
  insert_node(klay_node);
  insert_node(paul_node);
  insert_node(sharq_node);
  insert_node(yao_node);
  insert_node(book_node);
  insert_node(carter_node);
  insert_node(doncic_node);
  insert_node(iverson_node);
  insert_node(jokic_node);
  insert_node(kawhi_node);
  insert_node(lebron_node);
  insert_node(rodman_node);
  insert_node(macgrady_node);
  insert_node(yang_node);
  insert_node(yi_node);
  insert_node(chris_node);
  assert(curry_node->right == dunken_node);
  assert(curry_node->right->node_color == BLACK_NODE);
  assert(dunken_node->left == doncic_node);
  assert(dunken_node->left->node_color == RED_NODE);
  assert(curry_node->left == camelo_node);
  assert(curry_node->left->node_color == RED_NODE);
  delete_node(dunken_node);
  assert(curry_node->left == camelo_node);
  assert(curry_node->left->node_color == RED_NODE);
  assert(curry_node->right == doncic_node);
  assert(curry_node->right->node_color == BLACK_NODE);
  assert(doncic_node->left == NULL);
  assert(doncic_node->right == NULL);
  assert(root_node == jordan_node);
  free_nodes();
  return TEST_PASSED;
}

// 2.1-1,
// 被删除节点为黑色，在左子树，有一个红色左子节点（插入的节点和顺序与2.2完全相同，删除的节点不同）
TestResult test_delete_black_node_at_left_and_have_a_single_red_left_child() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(durant_node);
  insert_node(sga_node);
  insert_node(curry_node);
  insert_node(hill_node);
  insert_node(kobe_node);
  insert_node(wade_node);
  insert_node(camelo_node);
  insert_node(dunken_node);
  insert_node(edwards_node);
  insert_node(jimmy_node);
  insert_node(klay_node);
  insert_node(paul_node);
  insert_node(sharq_node);
  insert_node(yao_node);
  insert_node(book_node);
  insert_node(carter_node);
  insert_node(doncic_node);
  insert_node(iverson_node);
  insert_node(jokic_node);
  insert_node(kawhi_node);
  insert_node(lebron_node);
  insert_node(rodman_node);
  insert_node(macgrady_node);
  insert_node(yang_node);
  insert_node(yi_node);
  insert_node(chris_node);
  assert(root_node->right == paul_node);
  assert(root_node->right->node_color == RED_NODE);
  assert(paul_node->right == sga_node);
  assert(paul_node->right->node_color == BLACK_NODE);
  assert(paul_node->left == kobe_node);
  assert(paul_node->left->node_color == BLACK_NODE);
  assert(kobe_node->left == klay_node);
  assert(kobe_node->left->node_color == BLACK_NODE);
  assert(klay_node->left == kawhi_node);
  assert(klay_node->left->node_color == RED_NODE);
  delete_node(klay_node);
  assert(kobe_node->left == kawhi_node);
  assert(kobe_node->left->node_color == BLACK_NODE);
  assert(kobe_node->right == lebron_node);
  assert(kobe_node->right->node_color == BLACK_NODE);
  assert(kawhi_node->left == NULL);
  assert(kawhi_node->right == NULL);
  assert(root_node == jordan_node);
  free_nodes();
  return TEST_PASSED;
}

// 2.1-2,
// 被删除节点为黑色，在左子树，有两个黑色子节点（插入的节点和顺序与2.1-1完全相同，删除的节点不同）
TestResult test_delete_black_node_at_left_and_have_red_left_right_child() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(durant_node);
  insert_node(sga_node);
  insert_node(curry_node);
  insert_node(hill_node);
  insert_node(kobe_node);
  insert_node(wade_node);
  insert_node(camelo_node);
  insert_node(dunken_node);
  insert_node(edwards_node);
  insert_node(jimmy_node);
  insert_node(klay_node);
  insert_node(paul_node);
  insert_node(sharq_node);
  insert_node(yao_node);
  insert_node(book_node);
  insert_node(carter_node);
  insert_node(doncic_node);
  insert_node(iverson_node);
  insert_node(jokic_node);
  insert_node(kawhi_node);
  insert_node(lebron_node);
  insert_node(rodman_node);
  insert_node(macgrady_node);
  insert_node(yang_node);
  insert_node(yi_node);
  insert_node(chris_node);
  assert(root_node->right == paul_node);
  assert(root_node->right->node_color == RED_NODE);
  assert(paul_node->right == sga_node);
  assert(paul_node->right->node_color == BLACK_NODE);
  assert(paul_node->left == kobe_node);
  assert(paul_node->left->node_color == BLACK_NODE);
  assert(kobe_node->left == klay_node);
  assert(kobe_node->left->node_color == BLACK_NODE);
  assert(kobe_node->right == lebron_node);
  assert(kobe_node->right->node_color == BLACK_NODE);
  assert(macgrady_node->node_color == RED_NODE);
  delete_node(kobe_node);
  assert(paul_node->left == kobe_node);
  char *kobe_player = (char *)((PLAYER *)kobe_node->tree_data)->pname;
  assert(strcmp(kobe_player, "Lebron") == 0);
  assert(kobe_node->left == klay_node);
  assert(kobe_node->left->node_color == BLACK_NODE);
  assert(kobe_node->right == macgrady_node);
  assert(kobe_node->right->node_color == BLACK_NODE);
  assert(macgrady_node->node_color == BLACK_NODE);
  assert(root_node == jordan_node);
  free_nodes();
  return TEST_PASSED;
}

// 1&3.3
//  被删除节点为黑色，在右子树，有两个黑色子节点，兄弟节点为黑色，替代节点为红色
//  （插入的节点和顺序与2.1-1完全相同，删除的节点不同）
TestResult test_delete_black_node_at_right_and_the_behind_node_is_red() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(durant_node);
  insert_node(sga_node);
  insert_node(curry_node);
  insert_node(hill_node);
  insert_node(kobe_node);
  insert_node(wade_node);
  insert_node(camelo_node);
  insert_node(dunken_node);
  insert_node(edwards_node);
  insert_node(jimmy_node);
  insert_node(klay_node);
  insert_node(paul_node);
  insert_node(sharq_node);
  insert_node(yao_node);
  insert_node(book_node);
  insert_node(carter_node);
  insert_node(doncic_node);
  insert_node(iverson_node);
  insert_node(jokic_node);
  insert_node(kawhi_node);
  insert_node(lebron_node);
  insert_node(rodman_node);
  insert_node(macgrady_node);
  insert_node(yang_node);
  insert_node(yi_node);
  insert_node(chris_node);
  assert(root_node->left == durant_node);
  assert(root_node->left->node_color == RED_NODE);
  assert(durant_node->right == hill_node);
  assert(durant_node->right->node_color == BLACK_NODE);
  assert(durant_node->left == curry_node);
  assert(durant_node->left->node_color == BLACK_NODE);
  assert(hill_node->left == edwards_node);
  assert(hill_node->left->node_color == BLACK_NODE);
  assert(hill_node->right == jimmy_node);
  assert(hill_node->right->node_color == BLACK_NODE);
  assert(jimmy_node->left == iverson_node);
  assert(jimmy_node->left->node_color == RED_NODE);
  assert(jimmy_node->right == jokic_node);
  assert(jimmy_node->right->node_color == RED_NODE);
  delete_node(hill_node);
  assert(durant_node->right == hill_node);
  char *hill_player = (char *)((PLAYER *)hill_node->tree_data)->pname;
  assert(strcmp(hill_player, "Iverson") == 0);
  assert(hill_node->left == edwards_node);
  assert(hill_node->left->node_color == BLACK_NODE);
  assert(jimmy_node->left == NULL);
  assert(jimmy_node->right == jokic_node);
  assert(jimmy_node->right->node_color == RED_NODE);
  assert(root_node == jordan_node);
  free_nodes();
  return TEST_PASSED;
}

// 1&3.2.1.4，转化成3.2.1.2
//  被删除节点为黑色，在右子树，有两个黑色子节点，兄弟节点为黑色，替代节点为红色
//  （插入的节点和顺序与2.1-1完全相同，删除的节点不同）
TestResult test_delete_black_node_at_left_and_have_two_different_color_child() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(durant_node);
  insert_node(sga_node);
  insert_node(curry_node);
  insert_node(hill_node);
  insert_node(kobe_node);
  insert_node(wade_node);
  insert_node(camelo_node);
  insert_node(dunken_node);
  insert_node(edwards_node);
  insert_node(jimmy_node);
  insert_node(klay_node);
  insert_node(paul_node);
  insert_node(sharq_node);
  insert_node(yao_node);
  insert_node(book_node);
  insert_node(carter_node);
  insert_node(doncic_node);
  insert_node(iverson_node);
  insert_node(jokic_node);
  insert_node(kawhi_node);
  insert_node(lebron_node);
  insert_node(rodman_node);
  insert_node(macgrady_node);
  insert_node(yang_node);
  insert_node(yi_node);
  insert_node(chris_node);
  assert(root_node->left == durant_node);
  assert(root_node->left->node_color == RED_NODE);
  assert(durant_node->right == hill_node);
  assert(durant_node->right->node_color == BLACK_NODE);
  assert(durant_node->left == curry_node);
  assert(durant_node->left->node_color == BLACK_NODE);
  assert(hill_node->left == edwards_node);
  assert(hill_node->left->node_color == BLACK_NODE);
  assert(hill_node->right == jimmy_node);
  assert(hill_node->right->node_color == BLACK_NODE);
  assert(jimmy_node->left == iverson_node);
  assert(jimmy_node->left->node_color == RED_NODE);
  assert(jimmy_node->right == jokic_node);
  assert(jimmy_node->right->node_color == RED_NODE);
  delete_node(sga_node);
  char *sga_player = (char *)((PLAYER *)sga_node->tree_data)->pname;
  assert(strcmp(sga_player, "Sharq") == 0);
  assert(sga_node->left == rodman_node);
  assert(sga_node->left->node_color == BLACK_NODE);
  assert(sga_node->right == yao_node);
  assert(sga_node->right->node_color == RED_NODE);
  assert(yao_node->left == wade_node);
  assert(yao_node->left->node_color == BLACK_NODE);
  assert(yao_node->right == yi_node);
  assert(yao_node->right->node_color == BLACK_NODE);
  assert(root_node == jordan_node);
  free_nodes();
  return TEST_PASSED;
}

// 1&3.1
//  被删除节点为红色，在右子树，有两个黑色子节点，兄弟节点为黑色，替代节点为红色
//  （插入的节点和顺序与2.1-1完全相同，删除的节点不同）
TestResult
test_delete_red_node_at_right_and_have_two_black_color_child_and_red_behind_node() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(durant_node);
  insert_node(sga_node);
  insert_node(curry_node);
  insert_node(hill_node);
  insert_node(kobe_node);
  insert_node(wade_node);
  insert_node(camelo_node);
  insert_node(dunken_node);
  insert_node(edwards_node);
  insert_node(jimmy_node);
  insert_node(klay_node);
  insert_node(paul_node);
  insert_node(sharq_node);
  insert_node(yao_node);
  insert_node(book_node);
  insert_node(carter_node);
  insert_node(doncic_node);
  insert_node(iverson_node);
  insert_node(jokic_node);
  insert_node(kawhi_node);
  insert_node(lebron_node);
  insert_node(rodman_node);
  insert_node(macgrady_node);
  insert_node(yang_node);
  insert_node(yi_node);
  insert_node(chris_node);
  assert(root_node->left == durant_node);
  assert(root_node->left->node_color == RED_NODE);
  assert(durant_node->right == hill_node);
  assert(durant_node->right->node_color == BLACK_NODE);
  assert(durant_node->left == curry_node);
  assert(durant_node->left->node_color == BLACK_NODE);
  assert(hill_node->left == edwards_node);
  assert(hill_node->left->node_color == BLACK_NODE);
  assert(hill_node->right == jimmy_node);
  assert(hill_node->right->node_color == BLACK_NODE);
  assert(jimmy_node->left == iverson_node);
  assert(jimmy_node->left->node_color == RED_NODE);
  assert(jimmy_node->right == jokic_node);
  assert(jimmy_node->right->node_color == RED_NODE);
  delete_node(wade_node);
  char *wade_player = (char *)((PLAYER *)wade_node->tree_data)->pname;
  assert(strcmp(wade_player, "Yang") == 0);
  assert(wade_node->left == sharq_node);
  assert(wade_node->left->node_color == BLACK_NODE);
  assert(wade_node->right == yao_node);
  assert(wade_node->right->node_color == BLACK_NODE);
  assert(yao_node->left == NULL);
  assert(yao_node->right == yi_node);
  assert(yao_node->right->node_color == RED_NODE);
  assert(root_node == jordan_node);
  free_nodes();
  return TEST_PASSED;
}

// 3.1
//  被删除节点为红色，没有子节点
//  （插入的节点和顺序与2.1-1完全相同，删除的节点不同）
TestResult test_delete_many_red_node_without_child() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(durant_node);
  insert_node(sga_node);
  insert_node(curry_node);
  insert_node(hill_node);
  insert_node(kobe_node);
  insert_node(wade_node);
  insert_node(camelo_node);
  insert_node(dunken_node);
  insert_node(edwards_node);
  insert_node(jimmy_node);
  insert_node(klay_node);
  insert_node(paul_node);
  insert_node(sharq_node);
  insert_node(yao_node);
  insert_node(book_node);
  insert_node(carter_node);
  insert_node(doncic_node);
  insert_node(iverson_node);
  insert_node(jokic_node);
  insert_node(kawhi_node);
  insert_node(lebron_node);
  insert_node(rodman_node);
  insert_node(macgrady_node);
  insert_node(yang_node);
  insert_node(yi_node);
  insert_node(chris_node);
  assert(root_node->left == durant_node);
  assert(root_node->left->node_color == RED_NODE);
  assert(durant_node->right == hill_node);
  assert(durant_node->right->node_color == BLACK_NODE);
  assert(durant_node->left == curry_node);
  assert(durant_node->left->node_color == BLACK_NODE);
  assert(hill_node->left == edwards_node);
  assert(hill_node->left->node_color == BLACK_NODE);
  assert(hill_node->right == jimmy_node);
  assert(hill_node->right->node_color == BLACK_NODE);
  assert(jimmy_node->left == iverson_node);
  assert(jimmy_node->left->node_color == RED_NODE);
  assert(jimmy_node->right == jokic_node);
  assert(jimmy_node->right->node_color == RED_NODE);
  delete_node(chris_node);
  assert(carter_node->right == NULL);
  assert(carter_node->node_color == BLACK_NODE);
  delete_node(doncic_node);
  assert(dunken_node->left == NULL);
  assert(dunken_node->node_color == BLACK_NODE);
  delete_node(iverson_node);
  assert(jimmy_node->left == NULL);
  assert(jimmy_node->node_color == BLACK_NODE);
  delete_node(jokic_node);
  assert(jimmy_node->right == NULL);
  assert(jimmy_node->node_color == BLACK_NODE);
  delete_node(kawhi_node);
  assert(klay_node->left == NULL);
  assert(klay_node->node_color == BLACK_NODE);
  delete_node(macgrady_node);
  assert(lebron_node->right == NULL);
  assert(lebron_node->node_color == BLACK_NODE);
  assert(root_node == jordan_node);
  free_nodes();
  return TEST_PASSED;
}

// 3.2.1.1.2-5
//  被删除节点为黑色，在左子树，没有子节点，父节点和兄弟节点均为黑色
//  （插入的节点和顺序与3.1完全相同，删除的节点不同）
TestResult test_delete_double_black_node_at_left_5() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(durant_node);
  insert_node(sga_node);
  insert_node(curry_node);
  insert_node(hill_node);
  insert_node(kobe_node);
  insert_node(wade_node);
  insert_node(camelo_node);
  insert_node(dunken_node);
  insert_node(edwards_node);
  insert_node(jimmy_node);
  insert_node(klay_node);
  insert_node(paul_node);
  insert_node(sharq_node);
  insert_node(yao_node);
  insert_node(book_node);
  insert_node(carter_node);
  insert_node(doncic_node);
  insert_node(iverson_node);
  insert_node(jokic_node);
  insert_node(kawhi_node);
  insert_node(lebron_node);
  insert_node(rodman_node);
  insert_node(macgrady_node);
  insert_node(yang_node);
  insert_node(yi_node);
  insert_node(chris_node);
  assert(root_node->left == durant_node);
  assert(root_node->left->node_color == RED_NODE);
  assert(durant_node->right == hill_node);
  assert(durant_node->right->node_color == BLACK_NODE);
  assert(durant_node->left == curry_node);
  assert(durant_node->left->node_color == BLACK_NODE);
  assert(hill_node->left == edwards_node);
  assert(hill_node->left->node_color == BLACK_NODE);
  assert(hill_node->right == jimmy_node);
  assert(hill_node->right->node_color == BLACK_NODE);
  assert(jimmy_node->left == iverson_node);
  assert(jimmy_node->left->node_color == RED_NODE);
  assert(jimmy_node->right == jokic_node);
  assert(jimmy_node->right->node_color == RED_NODE);
  delete_node(chris_node);
  delete_node(doncic_node);
  delete_node(iverson_node);
  delete_node(jokic_node);
  delete_node(kawhi_node);
  delete_node(macgrady_node);
  delete_node(edwards_node);
  assert(root_node == jordan_node);
  assert(root_node->left == curry_node);
  assert(root_node->left->node_color == RED_NODE);
  assert(curry_node->left == camelo_node);
  assert(curry_node->left->node_color == BLACK_NODE);
  assert(curry_node->right == durant_node);
  assert(curry_node->right->node_color == BLACK_NODE);
  assert(durant_node->left == dunken_node);
  assert(durant_node->left->node_color == BLACK_NODE);
  assert(durant_node->right == hill_node);
  assert(durant_node->right->node_color == BLACK_NODE);
  assert(hill_node->left == NULL);
  assert(hill_node->right == jimmy_node);
  assert(hill_node->right->node_color == RED_NODE);
  free_nodes();
  return TEST_PASSED;
}

// 3.3.1.1.2-1
//  被删除节点为黑色，在右子树，没有子节点，父节点和兄弟节点均为黑色
//  （插入的节点和顺序与3.1完全相同，删除的节点不同）
TestResult test_delete_double_black_node_at_right_1() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(durant_node);
  insert_node(sga_node);
  insert_node(curry_node);
  insert_node(hill_node);
  insert_node(kobe_node);
  insert_node(wade_node);
  insert_node(camelo_node);
  insert_node(dunken_node);
  insert_node(edwards_node);
  insert_node(jimmy_node);
  insert_node(klay_node);
  insert_node(paul_node);
  insert_node(sharq_node);
  insert_node(yao_node);
  insert_node(book_node);
  insert_node(carter_node);
  insert_node(doncic_node);
  insert_node(iverson_node);
  insert_node(jokic_node);
  insert_node(kawhi_node);
  insert_node(lebron_node);
  insert_node(rodman_node);
  insert_node(macgrady_node);
  insert_node(yang_node);
  insert_node(yi_node);
  insert_node(chris_node);
  assert(root_node->left == durant_node);
  assert(root_node->left->node_color == RED_NODE);
  assert(durant_node->right == hill_node);
  assert(durant_node->right->node_color == BLACK_NODE);
  assert(durant_node->left == curry_node);
  assert(durant_node->left->node_color == BLACK_NODE);
  assert(hill_node->left == edwards_node);
  assert(hill_node->left->node_color == BLACK_NODE);
  assert(hill_node->right == jimmy_node);
  assert(hill_node->right->node_color == BLACK_NODE);
  assert(jimmy_node->left == iverson_node);
  assert(jimmy_node->left->node_color == RED_NODE);
  assert(jimmy_node->right == jokic_node);
  assert(jimmy_node->right->node_color == RED_NODE);
  delete_node(chris_node);
  delete_node(doncic_node);
  delete_node(iverson_node);
  delete_node(jokic_node);
  delete_node(kawhi_node);
  delete_node(macgrady_node);
  delete_node(jimmy_node);
  assert(root_node == jordan_node);
  assert(root_node->left == curry_node);
  assert(root_node->left->node_color == RED_NODE);
  assert(curry_node->left == camelo_node);
  assert(curry_node->left->node_color == BLACK_NODE);
  assert(curry_node->right == durant_node);
  assert(curry_node->right->node_color == BLACK_NODE);
  assert(durant_node->left == dunken_node);
  assert(durant_node->left->node_color == BLACK_NODE);
  assert(durant_node->right == hill_node);
  assert(durant_node->right->node_color == BLACK_NODE);
  assert(hill_node->left == edwards_node);
  assert(hill_node->left->node_color == RED_NODE);
  assert(hill_node->right == NULL);
  free_nodes();
  return TEST_PASSED;
}

// 3.2.1.1.2-6
//  被删除节点为黑色，在左子树，有左右两个黑色子节点，兄弟节点均为黑色
//  被删除节点的后继节点为3.3.1.1.2-1中的被删除节点，所以这两个删除结果节点结构完全相同，节点值不同
//  （插入的节点和顺序与3.3.1.1.2-1完全相同，删除的节点不同）
TestResult test_delete_double_black_node_at_left_6() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(durant_node);
  insert_node(sga_node);
  insert_node(curry_node);
  insert_node(hill_node);
  insert_node(kobe_node);
  insert_node(wade_node);
  insert_node(camelo_node);
  insert_node(dunken_node);
  insert_node(edwards_node);
  insert_node(jimmy_node);
  insert_node(klay_node);
  insert_node(paul_node);
  insert_node(sharq_node);
  insert_node(yao_node);
  insert_node(book_node);
  insert_node(carter_node);
  insert_node(doncic_node);
  insert_node(iverson_node);
  insert_node(jokic_node);
  insert_node(kawhi_node);
  insert_node(lebron_node);
  insert_node(rodman_node);
  insert_node(macgrady_node);
  insert_node(yang_node);
  insert_node(yi_node);
  insert_node(chris_node);
  assert(root_node->left == durant_node);
  assert(root_node->left->node_color == RED_NODE);
  assert(durant_node->right == hill_node);
  assert(durant_node->right->node_color == BLACK_NODE);
  assert(durant_node->left == curry_node);
  assert(durant_node->left->node_color == BLACK_NODE);
  assert(hill_node->left == edwards_node);
  assert(hill_node->left->node_color == BLACK_NODE);
  assert(hill_node->right == jimmy_node);
  assert(hill_node->right->node_color == BLACK_NODE);
  assert(jimmy_node->left == iverson_node);
  assert(jimmy_node->left->node_color == RED_NODE);
  assert(jimmy_node->right == jokic_node);
  assert(jimmy_node->right->node_color == RED_NODE);
  delete_node(chris_node);
  delete_node(doncic_node);
  delete_node(iverson_node);
  delete_node(jokic_node);
  delete_node(kawhi_node);
  delete_node(macgrady_node);
  delete_node(hill_node);
  assert(root_node == jordan_node);
  assert(root_node->left == curry_node);
  assert(root_node->left->node_color == RED_NODE);
  assert(curry_node->left == camelo_node);
  assert(curry_node->left->node_color == BLACK_NODE);
  assert(curry_node->right == durant_node);
  assert(curry_node->right->node_color == BLACK_NODE);
  assert(durant_node->left == dunken_node);
  assert(durant_node->left->node_color == BLACK_NODE);
  assert(durant_node->right == hill_node);
  assert(durant_node->right->node_color == BLACK_NODE);
  assert(hill_node->left == edwards_node);
  assert(hill_node->left->node_color == RED_NODE);
  char *hill_player = (char *)((PLAYER *)hill_node->tree_data)->pname;
  assert(strcmp(hill_player, "Jimmy") == 0);
  assert(hill_node->right == NULL);
  free_nodes();
  return TEST_PASSED;
}
