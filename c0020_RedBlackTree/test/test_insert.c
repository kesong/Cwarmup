#include "../include/log.h"
// #include "../src/print_ADT.h"
#include "test_and_validation.h"
#include "test_player.h"
#include <assert.h>
#include <stdio.h>
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

// test node into an empty tree, the node will be root node
TestResult test_insert_node_as_root_node() {
  TreeNode *test_tree = build_tree();
  TreeNode *insert_node = NULL;
  TreeNode *insert_result = NULL;
  init_player_data();
  insert_result = insert_tree_node(test_tree, jordan_node);
  PLAYER *player1 = (PLAYER *)root_node->tree_data;
  char *player1_name = player1->pname;
  PLAYER *player2 = (PLAYER *)insert_result->tree_data;
  char *player2_name = player2->pname;
  bool equal_result = false;
  assert(strcmp(player2_name, "Jordan") == 0);
  assert(strcmp(player1_name, player2_name) == 0);
  free_nodes();
  return TEST_PASSED;
}

// test insert a node in the tree already.
TestResult test_insert_node_exist() {
  TreeNode *test_tree = build_tree();
  TreeNode *insert_node = NULL;
  init_player_data();
  insert_tree_node(test_tree, jordan_node);
  insert_tree_node(test_tree, jordan_node);
  bool equal_result = false;
  assert(test_tree->left == NULL);
  assert(test_tree->right == NULL);
  free_nodes();
  return TEST_PASSED;
}

// build a tree manualy to test.
TreeNode *build_tree_manualy(TreeNode *test_node) {
  init_player_data();
  test_node != NULL ? test_node = NULL : (void)0;
  insert_node(jordan_node);
  insert_node(edwards_node);
  test_node = insert_node(sga_node);
  return test_node;
}

TestResult test_clear_tree() {
  TreeNode *test_root = NULL;
  test_root = build_tree_manualy(test_root);
  assert(test_root != NULL);
  test_root = clear_tree(test_root);
  assert(test_root == NULL);
  free_nodes();
  return TEST_PASSED;
}

TestResult test_build_player_tree_by_name() {
  TreeNode *test_root = NULL;
  test_root = build_player_tree_by_name();
  Stack *stack = create_stack();
  push_node_to_stack(stack, test_root);
  int player_amount = stack_size(stack);
  TreeNode *print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  if (player_amount != 27) {
    log_d("Expect %d players in the stack, get real amount is %d", 27,
          player_amount);
  }
  free(stack);
  assert(player_amount == 27);
  free_nodes();
  return TEST_PASSED;
}

// LL型旋转，root节点会变化；
TestResult test_left_rotate() {
  clear_tree(root_node);
  init_player_data();
  insert_node(jordan_node);
  TreeNode *test_root = root_node;
  assert(test_root == jordan_node);
  test_root = insert_node(edwards_node);
  assert(test_root == jordan_node);
  test_root = insert_node(curry_node);
  assert(test_root == edwards_node);
  assert(test_root->node_color == BLACK_NODE);
  assert(test_root->left == curry_node);
  assert(test_root->left->node_color == RED_NODE);
  assert(test_root->right == jordan_node);
  assert(test_root->right->node_color == RED_NODE);
  return TEST_PASSED;
}

// RR型旋转，root节点会变化
TestResult test_right_rotate() {
  clear_tree(root_node);
  init_player_data();
  insert_node(jordan_node);
  TreeNode *test_root = root_node;
  assert(test_root == jordan_node);
  test_root = insert_node(rodman_node);
  assert(test_root->right->node_color == RED_NODE);
  test_root = insert_node(yi_node);
  assert(test_root == rodman_node);
  assert(test_root->left == jordan_node);
  assert(test_root->left->node_color == RED_NODE);
  assert(test_root->right == yi_node);
  assert(test_root->right->node_color == RED_NODE);
  free_nodes();
  return TEST_PASSED;
}

// LR型旋转
TestResult test_left_rotate_then_right() {
  init_player_data();
  TreeNode *test_root = paul_node;
  test_root->right = sharq_node;
  test_root->left = NULL;
  sharq_node->left = rodman_node;
  sharq_node->right = NULL;
  rodman_node->right = sga_node;
  rodman_node->left = NULL;
  left_rotate_then_right(sharq_node, rodman_node);
  char *test_root_right =
      (char *)((PLAYER *)test_root->right->tree_data)->pname;
  char *sga_name = (char *)((PLAYER *)sga_node->tree_data)->pname;
  char *sga_left = (char *)((PLAYER *)sga_node->left->tree_data)->pname;
  char *sga_right = (char *)((PLAYER *)sga_node->right->tree_data)->pname;
  char *sharq = (char *)((PLAYER *)sharq_node->tree_data)->pname;
  char *rodman = (char *)((PLAYER *)rodman_node->tree_data)->pname;
  // assert(strcmp(test_root_right, sga_name) == 0);
  assert(strcmp(sga_left, rodman) == 0);
  assert(strcmp(sga_right, sharq) == 0);
  free_nodes();
  return TEST_PASSED;
}

// RL型旋转
TestResult test_right_rotate_then_left() {
  init_player_data();
  TreeNode *test_root = paul_node;
  test_root->left = sharq_node;
  test_root->right = NULL;
  sharq_node->right = rodman_node;
  sharq_node->left = NULL;
  rodman_node->left = sga_node;
  rodman_node->right = NULL;
  right_rotate_then_left(sharq_node, rodman_node);
  char *test_root_left = (char *)((PLAYER *)test_root->left->tree_data)->pname;
  char *sga_name = (char *)((PLAYER *)sga_node->tree_data)->pname;
  char *sga_left = (char *)((PLAYER *)sga_node->left->tree_data)->pname;
  char *sga_right = (char *)((PLAYER *)sga_node->right->tree_data)->pname;
  char *sharq = (char *)((PLAYER *)sharq_node->tree_data)->pname;
  char *rodman = (char *)((PLAYER *)rodman_node->tree_data)->pname;
  assert(strcmp(sga_left, sharq) == 0);
  assert(strcmp(sga_right, rodman) == 0);
  free_nodes();
  return TEST_PASSED;
}

// 先进行LR调整，再将根节点右旋转
TestResult test_insert_LR_rotate_then_root_right_rotate() {
  init_player_data();
  insert_node(jordan_node);
  insert_node(durant_node);
  insert_node(yao_node);
  insert_node(macgrady_node);
  insert_node(camelo_node);
  insert_node(iverson_node);
  insert_node(jimmy_node);
  insert_node(hill_node);
  assert(root_node == jordan_node);
  assert(root_node->left->node_color == RED_NODE);
  assert(root_node->right->node_color == BLACK_NODE);
  insert_node(edwards_node);
  assert(root_node == iverson_node);
  assert(root_node->left->node_color == RED_NODE);
  assert(root_node->right->node_color == RED_NODE);
  assert(iverson_node->left == durant_node);
  assert(iverson_node->right == jordan_node);
  assert(jordan_node->left == jimmy_node);
  assert(jordan_node->right == yao_node);
  free_nodes();
  return TEST_PASSED;
}

TestResult test_check_after_every_insert() {
  clear_tree(root_node);
  TreeNode *test_root = NULL;
  init_player_data();
  test_root = insert_node(jordan_node);
  Stack *stack = create_stack();
  push_node_to_stack(stack, test_root);
  TreeNode *print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  test_root = root_node;
  char *root_player = (char *)((PLAYER *)test_root->tree_data)->pname;
  assert(strcmp(root_player, "Jordan") == 0);
  assert(test_root->node_color == BLACK_NODE);
  log_i("jordan insert complete.");

  insert_node(jokic_node);
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  test_root = root_node;
  char *root_left = (char *)((PLAYER *)test_root->left->tree_data)->pname;
  assert(strcmp(root_left, "Jokic") == 0);
  assert(test_root->left->node_color == RED_NODE);
  log_i("jokic insert complete.");

  insert_node(yi_node);
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  test_root = root_node;
  char *root_right = (char *)((PLAYER *)test_root->right->tree_data)->pname;
  assert(strcmp(root_right, "Yi") == 0);
  assert(test_root->right->node_color == RED_NODE);
  log_i("yi insert complete.");

  insert_node(rodman_node);
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  char *yi_left = (char *)((PLAYER *)yi_node->left->tree_data)->pname;
  assert(strcmp(yi_left, "Rodman") == 0);
  assert(yi_node->left->node_color == RED_NODE);
  assert(yi_node->node_color == BLACK_NODE);
  assert(jokic_node->node_color == BLACK_NODE);
  log_i("rodman insert complete.");

  insert_node(jimmy_node);
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  char *jokic_left = (char *)((PLAYER *)jokic_node->left->tree_data)->pname;
  assert(strcmp(jokic_left, "Jimmy") == 0);
  assert(jokic_node->left->node_color == RED_NODE);
  assert(jokic_node->node_color == BLACK_NODE);
  log_i("jimmy insert complete.");

  insert_node(book_node);
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  test_root = root_node;
  char *jimmy_left = (char *)((PLAYER *)jimmy_node->left->tree_data)->pname;
  char *jimmy_right = (char *)((PLAYER *)jimmy_node->right->tree_data)->pname;
  assert(strcmp(jimmy_left, "Book") == 0);
  assert(strcmp(jimmy_right, "Jokic") == 0);
  assert(test_root->left == jimmy_node);
  assert(jimmy_node->left->node_color == RED_NODE);
  assert(jimmy_node->right->node_color == RED_NODE);
  assert(jimmy_node->node_color == BLACK_NODE);
  log_i("book insert complete.");

  insert_node(dunken_node);
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  assert(book_node->right == dunken_node);
  assert(jimmy_node->left->node_color == BLACK_NODE);
  assert(jimmy_node->right->node_color == BLACK_NODE);
  assert(jimmy_node->node_color == RED_NODE);
  log_i("dunken insert complete.");

  insert_node(camelo_node);
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  assert(jimmy_node->left == camelo_node);
  assert(camelo_node->left == book_node);
  assert(camelo_node->right == dunken_node);
  assert(camelo_node->node_color == BLACK_NODE);
  assert(camelo_node->left->node_color == RED_NODE);
  assert(camelo_node->right->node_color == RED_NODE);
  log_i("camelo insert complete.");

  insert_node(paul_node);
  test_root = root_node;
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  assert(test_root->right == rodman_node);
  assert(test_root->right->right == yi_node);
  assert(test_root->right->left == paul_node);
  assert(test_root->right->node_color == BLACK_NODE);
  assert(test_root->right->right->node_color == RED_NODE);
  assert(test_root->right->left->node_color == RED_NODE);
  log_i("paul insert complete.");

  insert_node(curry_node);
  test_root = root_node;
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  log_i("curry insert complete.");
  assert(test_root == jimmy_node);
  assert(test_root->node_color == BLACK_NODE);
  assert(test_root->right == jordan_node);
  assert(test_root->left == camelo_node);
  assert(test_root->right->node_color == RED_NODE);
  assert(test_root->left->node_color == RED_NODE);
  assert(dunken_node->left == curry_node);
  assert(dunken_node->left->node_color == RED_NODE);
  assert(camelo_node->left == book_node);
  assert(camelo_node->right == dunken_node);
  assert(camelo_node->left->node_color == BLACK_NODE);
  assert(camelo_node->right->node_color == BLACK_NODE);

  insert_node(yao_node);
  test_root = root_node;
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  log_i("yao insert complete.");

  insert_node(kobe_node);
  test_root = root_node;
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  log_i("kobe insert complete.");

  insert_node(yang_node);
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  log_i("yang insert complete.");

  insert_node(sharq_node);
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  log_i("sharq insert complete.");
  assert(test_root->right == rodman_node);
  assert(rodman_node->left == jordan_node);
  assert(rodman_node->left->node_color == RED_NODE);
  assert(rodman_node->left->right == paul_node);
  assert(rodman_node->right == yao_node);

  insert_node(sga_node);
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  log_i("sga insert complete.");
  assert(sharq_node->left == sga_node);
  assert(sharq_node->right == yang_node);

  insert_node(edwards_node);
  test_root = root_node;
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  log_i("edwards insert complete.");
  assert(test_root->left->node_color == BLACK_NODE);
  assert(test_root->left->right == dunken_node);
  assert(test_root->left->right->node_color == BLACK_NODE);

  insert_node(klay_node);
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  log_i("klay insert complete.");
  assert(kobe_node->left == klay_node);
  assert(kobe_node->right == paul_node);

  insert_node(hill_node);
  test_root = root_node;
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  log_i("hill insert complete.");
  assert(test_root->left->right == dunken_node);
  assert(test_root->left->right->node_color == RED_NODE);
  assert(dunken_node->right->right == hill_node);

  insert_node(durant_node);
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  log_i("durant insert complete.");
  char *edwards_left_name =
      (char *)((PLAYER *)edwards_node->left->tree_data)->pname;
  assert(edwards_node->node_color == BLACK_NODE);
  assert(strcmp(edwards_left_name, "Durant") == 0);
  assert(edwards_node->left->node_color == RED_NODE);
  char *edwards_right_name =
      (char *)((PLAYER *)edwards_node->right->tree_data)->pname;
  assert(edwards_node->right->node_color == RED_NODE);

  insert_node(wade_node);
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  log_i("wade insert complete.");
  assert(yao_node->left == sharq_node);
  assert(yao_node->node_color == BLACK_NODE);
  assert(yao_node->left->node_color == RED_NODE);
  assert(sharq_node->right->node_color == BLACK_NODE);
  assert(yang_node->left == wade_node);

  insert_node(lebron_node);
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  log_i("lebron insert complete.");
  assert(kobe_node->node_color == RED_NODE);
  assert(paul_node->node_color == BLACK_NODE);
  assert(paul_node->left == lebron_node);

  insert_node(iverson_node);
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  log_i("iverson insert complete.");
  assert(test_root->left == dunken_node);
  assert(edwards_node->node_color == RED_NODE);
  assert(edwards_node->right->node_color == BLACK_NODE);
  assert(edwards_node->right->right == iverson_node);

  insert_node(macgrady_node);
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  log_i("macgrady insert complete.");
  assert(kobe_node->right == macgrady_node);
  assert(macgrady_node->node_color == BLACK_NODE);
  assert(macgrady_node->right == paul_node);
  assert(paul_node->node_color == RED_NODE);

  insert_node(kawhi_node);
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  log_i("kawhi insert complete.");
  assert(klay_node->left == kawhi_node);

  insert_node(doncic_node);
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  log_i("doncic insert complete.");
  assert(curry_node->right == doncic_node);

  insert_node(carter_node);
  test_root = root_node;
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  log_i("carter insert complete.");
  assert(curry_node->left == carter_node);
  assert(carter_node->node_color == RED_NODE);
  assert(curry_node->node_color == BLACK_NODE);
  char *curry_right_name =
      (char *)((PLAYER *)curry_node->right->tree_data)->pname;
  assert(strcmp(curry_right_name, "Doncic") == 0);
  assert(curry_node->right->node_color == RED_NODE);

  insert_node(chris_node);
  test_root = root_node;
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    pop(stack, &print_node);
    char *player_name = (char *)((PLAYER *)print_node->tree_data)->pname;
    printf("%s, ", player_name);
  }
  printf("\n");
  free(stack);
  log_i("chris insert complete.");
  char *jordan_left_name =
      (char *)((PLAYER *)jordan_node->left->tree_data)->pname;
  assert(strcmp(jordan_left_name, "Jokic") == 0);
  assert(jordan_node->left->node_color == BLACK_NODE);
  char *jordan_right_name =
      (char *)((PLAYER *)jordan_node->right->tree_data)->pname;
  assert(strcmp(jordan_right_name, "Kobe") == 0);
  assert(jordan_node->right->node_color == RED_NODE);
  char *carter_right_name =
      (char *)((PLAYER *)carter_node->right->tree_data)->pname;
  assert(strcmp(carter_right_name, "Chris") == 0);
  assert(carter_node->right->node_color == RED_NODE);

  free_nodes();
  return TEST_PASSED;
}

TestResult test_insert_node_at_left_branch() {
  TreeNode *test_root = NULL;
  test_root = build_tree_manualy(test_root);
  if (test_root == NULL) {
    log_d("Didn't get right tree node.");
    return TEST_FAILED;
  }
  insert_node(curry_node);
  PLAYER *in_player = (PLAYER *)test_root->left->left->tree_data;
  char *in_player_name = in_player->pname;
  char *curry_name = (char *)((PLAYER *)curry_node->tree_data)->pname;
  assert(test_root->left->node_color == BLACK_NODE);
  assert(test_root->right->node_color == BLACK_NODE);
  assert(test_root->left->left->node_color == RED_NODE);
  if (strcmp(in_player_name, curry_name) == 0) {
    return TEST_PASSED;
  } else {
    log_d("Expect name is %s, but get %s.", curry_name, in_player_name);
    return TEST_FAILED;
  }
}

TestResult test_insert_node_at_left_left_branch() {
  TreeNode *test_root = NULL;
  test_root = build_tree_manualy(test_root);
  if (test_root == NULL) {
    log_d("Didn't get right tree node.");
    return TEST_FAILED;
  }
  insert_node(curry_node);
  insert_node(book_node);
  PLAYER *in_player = (PLAYER *)test_root->left->tree_data;
  char *in_player_name = in_player->pname;
  char *curry_name = (char *)((PLAYER *)curry_node->tree_data)->pname;
  PLAYER *in_player2 = (PLAYER *)test_root->left->left->tree_data;
  char *in_player2_name = in_player2->pname;
  char *book_name = (char *)((PLAYER *)book_node->tree_data)->pname;
  assert(test_root->left->node_color == BLACK_NODE);
  assert(test_root->right->node_color == BLACK_NODE);
  assert(test_root->left->right->node_color == RED_NODE);
  assert(test_root->left->left->node_color == RED_NODE);
  assert(strcmp(in_player_name, curry_name) == 0);
  if (strcmp(in_player2_name, book_name) == 0) {
    return TEST_PASSED;
  } else {
    log_d("Expect name is %s, but get %s.", book_name, in_player2_name);
    return TEST_FAILED;
  }
}

TestResult test_insert_node_at_left_right_branch() {
  TreeNode *test_root = NULL;
  test_root = build_tree_manualy(test_root);
  if (test_root == NULL) {
    log_d("Didn't get right tree node.");
    return TEST_FAILED;
  }
  insert_node(curry_node);
  insert_node(dunken_node);
  PLAYER *in_player = (PLAYER *)test_root->left->tree_data;
  char *in_player_name = in_player->pname;
  char *edwards_name = (char *)((PLAYER *)edwards_node->tree_data)->pname;
  PLAYER *in_player2 = (PLAYER *)test_root->left->right->tree_data;
  char *in_player2_name = in_player2->pname;
  char *dunken_name = (char *)((PLAYER *)dunken_node->tree_data)->pname;
  assert(test_root->left->node_color == BLACK_NODE);
  assert(test_root->right->node_color == BLACK_NODE);
  assert(test_root->left->right->node_color == RED_NODE);
  assert(test_root->left->left->node_color == RED_NODE);
  assert(strcmp(in_player_name, dunken_name) == 0);
  if (strcmp(in_player2_name, edwards_name) == 0) {
    return TEST_PASSED;
  } else {
    log_d("Expect name is %s, but get %s.", dunken_name, in_player2_name);
    return TEST_FAILED;
  }
}

TestResult test_insert_node_at_right_right_branch() {
  TreeNode *test_root = NULL;
  test_root = build_tree_manualy(test_root);
  if (test_root == NULL) {
    log_d("Didn't get right tree node.");
    return TEST_FAILED;
  }
  insert_node(yang_node);
  insert_node(yao_node);
  PLAYER *in_player = (PLAYER *)test_root->right->tree_data;
  char *in_player_name = in_player->pname;
  char *yang_name = (char *)((PLAYER *)yang_node->tree_data)->pname;
  PLAYER *in_player2 = (PLAYER *)test_root->right->right->tree_data;
  char *in_player2_name = in_player2->pname;
  char *yao_name = (char *)((PLAYER *)yao_node->tree_data)->pname;
  assert(test_root->left->node_color == BLACK_NODE);
  assert(test_root->right->node_color == BLACK_NODE);
  assert(test_root->right->right->node_color == RED_NODE);
  assert(test_root->right->left->node_color == RED_NODE);
  assert(strcmp(in_player_name, yang_name) == 0);
  assert(strcmp(in_player2_name, yao_name) == 0);
  free_nodes();
  return TEST_PASSED;
}

TestResult test_insert_node_at_right_left_branch() {
  TreeNode *test_root = NULL;
  test_root = build_tree_manualy(test_root);
  if (test_root == NULL) {
    log_d("Didn't get right tree node.");
    return TEST_FAILED;
  }
  insert_node(yang_node);
  insert_node(wade_node);
  PLAYER *in_player = (PLAYER *)test_root->right->tree_data;
  char *in_player_name = in_player->pname;
  char *yang_name = (char *)((PLAYER *)yang_node->tree_data)->pname;
  PLAYER *in_player2 = (PLAYER *)test_root->right->right->tree_data;
  char *in_player2_name = in_player2->pname;
  char *wade_name = (char *)((PLAYER *)wade_node->tree_data)->pname;
  assert(test_root->left->node_color == BLACK_NODE);
  assert(test_root->right->node_color == BLACK_NODE);
  assert(test_root->right->right->node_color == RED_NODE);
  assert(test_root->right->left->node_color == RED_NODE);
  assert(strcmp(in_player_name, wade_name) == 0);
  assert(strcmp(in_player2_name, yang_name) == 0);
  free_nodes();
  return TEST_PASSED;
}

TestResult test_check_color_and_modify() {
  TreeNode *test_root = NULL;
  test_root = build_tree_manualy(test_root);
  if (test_root == NULL) {
    log_d("Didn't get right tree node.");
    return TEST_FAILED;
  }
  // iversion will be as the right node of the edwards_node, the color of
  // edwards and sga will modified to BLACK_NODE；
  test_root->left->right = iverson_node;
  TreeNode *check_node = test_root->left->right;
  // the color of edwards and sga will modified to BLACK_NODE；
  check_color_and_modify(test_root->left, check_node);
  assert(edwards_node->node_color == BLACK_NODE);
  assert(sga_node->node_color == BLACK_NODE);
  assert(check_node->node_color == RED_NODE);
  free_nodes();
  return TEST_PASSED;
}
