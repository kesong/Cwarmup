#include "../include/log.h"
#include "../src/print_ADT.h"
#include "test_and_validation.h"
#include "test_player.h"
#include <assert.h>
#include <stdbool.h>
#include <string.h>

extern TreeNode *root_node;

TreeNode *get_tree_by_traversal(TreeNode *start_node,
                                traversal_function trav_func,
                                TreeNode **trav_result) {
  if (start_node == NULL || start_node->tree_data == NULL) {
    printf("Empty tree.\n");
    return NULL;
  }
  int *index = 0;
  trav_func(start_node, trav_result, &index);
  return *trav_result;
}

// 前序遍历的结果（VLR）： jimmy, dunken, camelo, book. curry, chris, carter,
// doncic, edwards, durant, hill, iverson, rodman, jordan, jokic, kobe, klay,
// kawhi. macgrady, lebron, paul, yang, sharq, sga, yi, wade, yao
TestResult test_preorder_traversal_without_recurse() {
  TreeNode *test_start_node = build_player_tree_by_name();
  TreeNode *traversal_result[MAX_SIZE];
  for (int i = 0; i < MAX_SIZE; i++) {
    traversal_result[i] = NULL;
  }
  get_tree_by_traversal(test_start_node, &preorder_traversal_without_recurse,
                        traversal_result);

  PLAYER *player1 = (PLAYER *)traversal_result[0]->tree_data;
  char *player1_name = player1->pname;
  PLAYER *player2 = (PLAYER *)traversal_result[4]->tree_data;
  char *player2_name = player2->pname;
  PLAYER *player3 = (PLAYER *)traversal_result[26]->tree_data;
  char *player3_name = player3->pname;
  bool result_value_valid = false;
  validate(player1_name, "Jimmy");
  if (strcmp(player1_name, "Jimmy") == 0) {
    result_value_valid = true;
  }
  validate(player2_name, "Curry");
  if (strcmp(player2_name, "Curry") == 0) {
    result_value_valid = true;
  }
  validate(player3_name, "Wade");
  if (strcmp(player3_name, "Wade") == 0) {
    result_value_valid = true;
  }
  if (result_value_valid) {
    log_i(
        "(VLR)preorder traversal without recurse result is (first method): \n");
    print_traversal_result_array(traversal_result);
    return TEST_PASSED;
  } else {
    return TEST_FAILED;
  }
  // print_tree_in_specified_order(test_start_node,
  // &preorder_traversal_without_recurse);
}

TestResult test_preorder_traversal_without_recurse_2() {
  TreeNode *test_start_node = build_player_tree_by_name();
  TreeNode *traversal_result[MAX_SIZE];
  for (int i = 0; i < MAX_SIZE; i++) {
    traversal_result[i] = NULL;
  }
  get_tree_by_traversal(test_start_node, &preorder_traversal_without_recurse_2,
                        traversal_result);

  PLAYER *player1 = (PLAYER *)traversal_result[7]->tree_data;
  char *player1_name = player1->pname;
  PLAYER *player2 = (PLAYER *)traversal_result[8]->tree_data;
  char *player2_name = player2->pname;
  PLAYER *player3 = (PLAYER *)traversal_result[9]->tree_data;
  char *player3_name = player3->pname;
  bool result_value_valid = false;
  if (strcmp(player1_name, "Doncic") == 0) {
    result_value_valid = true;
  } else {
    log_e("Test failed, expect value is %s, but get %s.", "Doncic",
          player1_name);
    result_value_valid = false;
  }
  if (strcmp(player2_name, "Edwards") == 0) {
    result_value_valid = true;
  } else {
    log_e("Test failed, expect value is %s, but get %s.", "Edwards",
          player2_name);
    result_value_valid = false;
  }
  if (strcmp(player3_name, "Durant") == 0) {
    result_value_valid = true;
  } else {
    log_e("Test failed, expect value is %s, but get %s.", "Durant",
          player3_name);
    result_value_valid = false;
  }
  if (result_value_valid) {
    log_i("(VLR)preorder traversal without recurse result is (second method): "
          "\n");
    print_traversal_result_array(traversal_result);
    return TEST_PASSED;
  } else {
    return TEST_FAILED;
  }
  // print_tree_in_specified_order(test_start_node,
  // &preorder_traversal_without_recurse_2);
}

// 中序遍历结果（LVR，遍历结果其实就是元素的排列顺序，可以用中序遍历来进行排序）：book,
// camelo, carter, chris, curry, doncic, dunken, durant, edwards, hill, iverson,
// jimmy, jokic, jordan, kawhi, klay, kobe, lebron, macgrady, paul, rodman, sga,
// sharq, wade, yi, yang, yao
TestResult test_inorder_traversal() {
  TreeNode *test_start_node = build_player_tree_by_name();
  log_i("(LVR)inorder traversal result is: \n");
  TreeNode *traversal_result[MAX_SIZE];
  for (int i = 0; i < MAX_SIZE; i++) {
    traversal_result[i] = NULL;
  }
  get_tree_by_traversal(test_start_node, &preorder_traversal_without_recurse_2,
                        traversal_result);

  PLAYER *player1 = (PLAYER *)traversal_result[6]->tree_data;
  char *player1_name = player1->pname;
  PLAYER *player2 = (PLAYER *)traversal_result[10]->tree_data;
  char *player2_name = player2->pname;
  PLAYER *player3 = (PLAYER *)traversal_result[21]->tree_data;
  char *player3_name = player3->pname;
  bool result_value_valid = false;
  if (strcmp(player1_name, "Dunken") == 0) {
    result_value_valid = true;
  } else {
    log_e("Test failed, expect value is %s, but get %s.", "Dunken",
          player1_name);
    result_value_valid = false;
  }
  if (strcmp(player2_name, "Iverson") == 0) {
    result_value_valid = true;
  } else {
    log_e("Test failed, expect value is %s, but get %s.", "Iverson",
          player2_name);
    result_value_valid = false;
  }
  if (strcmp(player3_name, "Sga") == 0) {
    result_value_valid = true;
  } else {
    log_e("Test failed, expect value is %s, but get %s.", "Sga", player3_name);
    result_value_valid = false;
  }
  if (result_value_valid) {
    log_i("(VLR)preorder traversal without recurse result is (second method): "
          "\n");
    print_traversal_result_array(traversal_result);
    return TEST_PASSED;
  } else {
    return TEST_FAILED;
  }
  // print_tree_in_specified_order(test_start_node, &inorder_traversal);
}

TestResult test_inorder_traversal_without_recurse() {
  TreeNode *test_start_node = build_player_tree_by_name();
  TreeNode *traversal_result[MAX_SIZE];
  for (int i = 0; i < MAX_SIZE; i++) {
    traversal_result[i] = NULL;
  }
  get_tree_by_traversal(test_start_node, &inorder_traversal_without_recurse,
                        traversal_result);

  PLAYER *player1 = (PLAYER *)traversal_result[1]->tree_data;
  char *player1_name = player1->pname;
  PLAYER *player2 = (PLAYER *)traversal_result[8]->tree_data;
  char *player2_name = player2->pname;
  PLAYER *player3 = (PLAYER *)traversal_result[14]->tree_data;
  char *player3_name = player3->pname;
  bool result_value_valid = false;
  if (strcmp(player1_name, "Camelo") == 0) {
    result_value_valid = true;
  } else {
    log_e("Test failed, expect value is %s, but get %s.", "Camelo",
          player1_name);
    result_value_valid = false;
  }
  if (strcmp(player2_name, "Edwards") == 0) {
    result_value_valid = true;
  } else {
    log_e("Test failed, expect value is %s, but get %s.", "Edwards",
          player2_name);
    result_value_valid = false;
  }
  if (strcmp(player3_name, "Kawhi") == 0) {
    result_value_valid = true;
  } else {
    log_e("Test failed, expect value is %s, but get %s.", "Kawhi",
          player3_name);
    result_value_valid = false;
  }
  if (result_value_valid) {
    log_i("(LVR)inorder traversal without recurse result is: \n");
    print_traversal_result_array(traversal_result);
    return TEST_PASSED;
  } else {
    return TEST_FAILED;
  }
  // print_tree_in_specified_order(test_start_node,
  // &inorder_traversal_without_recurse);
}

// 后序遍历结果（LRV）：book, carter, chris, doncic, curry, camelo, durant,
// iverson, hill, edwards, dunken, jokic, kawhi, klay, lebron, paul, macgrady,
// kobe, jordan, sga, wade, yi, sharq, yao, yang, rodman, jimmy
TestResult test_postorder_traversal() {
  TreeNode *test_start_node = build_player_tree_by_name();
  TreeNode *traversal_result[MAX_SIZE];
  for (int i = 0; i < MAX_SIZE; i++) {
    traversal_result[i] = NULL;
  }
  get_tree_by_traversal(test_start_node, &postorder_traversal,
                        traversal_result);

  PLAYER *player1 = (PLAYER *)traversal_result[1]->tree_data;
  char *player1_name = player1->pname;
  PLAYER *player2 = (PLAYER *)traversal_result[8]->tree_data;
  char *player2_name = player2->pname;
  PLAYER *player3 = (PLAYER *)traversal_result[26]->tree_data;
  char *player3_name = player3->pname;
  bool result_value_valid = false;
  if (strcmp(player1_name, "Carter") == 0) {
    result_value_valid = true;
  } else {
    log_e("Test failed, expect value is %s, but get %s.", "Carter",
          player1_name);
    result_value_valid = false;
  }
  if (strcmp(player2_name, "Hill") == 0) {
    result_value_valid = true;
  } else {
    log_e("Test failed, expect value is %s, but get %s.", "Hill", player2_name);
    result_value_valid = false;
  }
  if (strcmp(player3_name, "Jimmy") == 0) {
    result_value_valid = true;
  } else {
    log_e("Test failed, expect value is %s, but get %s.", "Jimmy",
          player3_name);
    result_value_valid = false;
  }
  if (result_value_valid) {
    log_i("(LRV)postorder traversal result is: \n");
    print_traversal_result_array(traversal_result);
    return TEST_PASSED;
  } else {
    return TEST_FAILED;
  }
  // print_tree_in_specified_order(test_start_node, &postorder_traversal);
}

TestResult test_postorder_traversal_without_recurse() {
  TreeNode *test_start_node = build_player_tree_by_name();
  TreeNode *traversal_result[MAX_SIZE];
  for (int i = 0; i < MAX_SIZE; i++) {
    traversal_result[i] = NULL;
  }
  get_tree_by_traversal(test_start_node, &postorder_traversal_without_recurse,
                        traversal_result);

  PLAYER *player1 = (PLAYER *)traversal_result[2]->tree_data;
  char *player1_name = player1->pname;
  PLAYER *player2 = (PLAYER *)traversal_result[18]->tree_data;
  char *player2_name = player2->pname;
  PLAYER *player3 = (PLAYER *)traversal_result[20]->tree_data;
  char *player3_name = player3->pname;
  bool result_value_valid = false;
  if (strcmp(player1_name, "Chris") == 0) {
    result_value_valid = true;
  } else {
    log_e("Test failed, expect value is %s, but get %s.", "Chris",
          player1_name);
    result_value_valid = false;
  }
  if (strcmp(player2_name, "Jordan") == 0) {
    result_value_valid = true;
  } else {
    log_e("Test failed, expect value is %s, but get %s.", "Jordan",
          player2_name);
    result_value_valid = false;
  }
  if (strcmp(player3_name, "Wade") == 0) {
    result_value_valid = true;
  } else {
    log_e("Test failed, expect value is %s, but get %s.", "Wade", player3_name);
    result_value_valid = false;
  }
  if (result_value_valid) {
    log_i("(LRV)postorder traversal without recurse result is: \n");
    print_traversal_result_array(traversal_result);
    return TEST_PASSED;
  } else {
    return TEST_FAILED;
  }
  // print_tree_in_specified_order(test_start_node,
  // &postorder_traversal_without_recurse);
}

TestResult test_postorder_traversal_without_recurse_2() {
  TreeNode *test_start_node = build_player_tree_by_name();
  TreeNode *traversal_result[MAX_SIZE];
  for (int i = 0; i < MAX_SIZE; i++) {
    traversal_result[i] = NULL;
  }
  get_tree_by_traversal(test_start_node, &postorder_traversal_without_recurse_2,
                        traversal_result);

  PLAYER *player1 = (PLAYER *)traversal_result[0]->tree_data;
  char *player1_name = player1->pname;
  PLAYER *player2 = (PLAYER *)traversal_result[11]->tree_data;
  char *player2_name = player2->pname;
  PLAYER *player3 = (PLAYER *)traversal_result[23]->tree_data;
  char *player3_name = player3->pname;
  bool result_value_valid = false;
  if (strcmp(player1_name, "Book") == 0) {
    result_value_valid = true;
  } else {
    log_e("Test failed, expect value is %s, but get %s.", "Book", player1_name);
    result_value_valid = false;
  }
  if (strcmp(player2_name, "Jokic") == 0) {
    result_value_valid = true;
  } else {
    log_e("Test failed, expect value is %s, but get %s.", "Jokic",
          player2_name);
    result_value_valid = false;
  }
  if (strcmp(player3_name, "Yao") == 0) {
    result_value_valid = true;
  } else {
    log_e("Test failed, expect value is %s, but get %s.", "Yao", player3_name);
    result_value_valid = false;
  }
  if (result_value_valid) {
    log_i("(LRV)postorder traversal without recurse result is: \n");
    print_traversal_result_array(traversal_result);
    return TEST_PASSED;
  } else {
    return TEST_FAILED;
  }
  // print_tree_in_specified_order(test_start_node,
  // &postorder_traversal_without_recurse_2);
}

// 层序遍历结果：jimmy, dunken, rodman, camelo, edwards, jordan, yang, book,
// curry, durant, hill, jokic, kobe, sharq, yao, chris, doncic, iverson, klay,
// macgrady, sga, yi, carter, kawhi,lebron, paul, wade
TestResult test_level_traversal() {
  TreeNode *test_start_node = build_player_tree_by_name();
  TreeNode *traversal_result[MAX_SIZE];
  for (int i = 0; i < MAX_SIZE; i++) {
    traversal_result[i] = NULL;
  }
  get_tree_by_traversal(test_start_node, &level_traversal, traversal_result);

  PLAYER *player1 = (PLAYER *)traversal_result[0]->tree_data;
  char *player1_name = player1->pname;
  PLAYER *player2 = (PLAYER *)traversal_result[6]->tree_data;
  char *player2_name = player2->pname;
  PLAYER *player3 = (PLAYER *)traversal_result[10]->tree_data;
  char *player3_name = player3->pname;
  bool result_value_valid = false;
  if (strcmp(player1_name, "Jimmy") == 0) {
    result_value_valid = true;
  } else {
    log_e("Test failed, expect value is %s, but get %s.", "Jimmy",
          player1_name);
    result_value_valid = false;
  }
  if (strcmp(player2_name, "Yang") == 0) {
    result_value_valid = true;
  } else {
    log_e("Test failed, expect value is %s, but get %s.", "Yang", player2_name);
    result_value_valid = false;
  }
  if (strcmp(player3_name, "Hill") == 0) {
    result_value_valid = true;
  } else {
    log_e("Test failed, expect value is %s, but get %s.", "Hill", player3_name);
    result_value_valid = false;
  }
  if (result_value_valid) {
    log_i("level traversal result is: \n");
    print_traversal_result_array(traversal_result);
    return TEST_PASSED;
  } else {
    return TEST_FAILED;
  }
  // print_tree_in_specified_order(test_start_node, &level_traversal);
}
