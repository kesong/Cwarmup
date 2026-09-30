#include "../include/log.h"
// #include "../src/print_ADT.h"
#include "data_process.h"
#include "test_and_validation.h"
#include "test_player.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// extern TreeNode *root_node;
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
  LLRBTree *llrbtree = create_llrbtree();

  init_player_data();
  llrbtree->root_node = insert_node(llrbtree->root_node, jordan_node);
  PLAYER *player1 = (PLAYER *)(llrbtree->root_node)->tree_data;
  char *player1_name = player1->pname;
  assert(strcmp(player1_name, "Jordan") == 0);
  // free_nodes();
  return TEST_PASSED;
}

// test insert a node in the tree already.
TestResult test_insert_node_exist() {
  LLRBTree *llrbtree = create_llrbtree();

  llrbtree->root_node = insert_node(llrbtree->root_node, jordan_node);
  llrbtree->root_node = insert_node(llrbtree->root_node, jordan_node);
  assert(llrbtree->root_node->left == NULL);
  assert(llrbtree->root_node->right == NULL);
  // free_nodes();
  return TEST_PASSED;
}

// build a tree manualy to test.
TreeNode *build_tree_manualy(TreeNode *test_node) {
  LLRBTree *llrbtree = create_llrbtree();
  init_player_data();
  test_node != NULL ? test_node = NULL : (void)0;
  llrbtree->root_node = insert_node(llrbtree->root_node, jordan_node);
  llrbtree->root_node = insert_node(llrbtree->root_node, edwards_node);
  llrbtree->root_node = insert_node(llrbtree->root_node, sga_node);
  test_node = llrbtree->root_node;
  return test_node;
}

TestResult test_clear_tree() {
  LLRBTree *llrbtree = create_llrbtree();
  TreeNode *test_root = NULL;
  llrbtree->root_node = build_tree_manualy(test_root);
  test_root = llrbtree->root_node;
  assert(test_root != NULL);
  assert(strcmp(((PLAYER *)test_root->tree_data)->pname, "Jordan") == 0);
  assert(strcmp(((PLAYER *)test_root->left->tree_data)->pname, "Edwards") == 0);
  assert(strcmp(((PLAYER *)test_root->right->tree_data)->pname, "Sga") == 0);
  test_root = clear_tree(llrbtree->root_node, test_root);
  assert(test_root == NULL);
  // free_nodes();
  return TEST_PASSED;
}

TestResult test_build_llrbtree() {
  TreeNode *test_root = build_llrbtree();
  Stack *stack = create_stack();
  push_node_to_stack(stack, test_root);
  int player_amount = stack_size(stack);
  TreeNode *print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  if (player_amount != 27) {
    log_d("Expect %d players in the stack, get real amount is %d", 27,
          player_amount);
  }
  free(stack);
  stack = NULL;
  assert(player_amount == 27);
  // free_nodes();
  return TEST_PASSED;
}

// LL型旋转，root节点会变化；
TestResult test_left_rotate() {
  LLRBTree *llrbtree = create_llrbtree();
  init_player_data();
  llrbtree->root_node = insert_node(llrbtree->root_node, jordan_node);
  assert(llrbtree->root_node == jordan_node);
  llrbtree->root_node = insert_node(llrbtree->root_node, edwards_node);
  assert(llrbtree->root_node == jordan_node);
  llrbtree->root_node = insert_node(llrbtree->root_node, curry_node);
  assert(llrbtree->root_node == edwards_node);
  assert(llrbtree->root_node->node_color == BLACK_NODE);
  assert(llrbtree->root_node->left == curry_node);
  assert(llrbtree->root_node->left->node_color == BLACK_NODE);
  assert(llrbtree->root_node->right == jordan_node);
  assert(llrbtree->root_node->right->node_color == BLACK_NODE);
  return TEST_PASSED;
}

// RR型旋转，root节点会变化
TestResult test_right_rotate() {
  LLRBTree *llrbtree = create_llrbtree();
  init_player_data();
  llrbtree->root_node = insert_node(llrbtree->root_node, jordan_node);
  assert(llrbtree->root_node == jordan_node);
  llrbtree->root_node = insert_node(llrbtree->root_node, rodman_node);
  assert(llrbtree->root_node == rodman_node);
  assert(llrbtree->root_node->left == jordan_node);
  assert(llrbtree->root_node->left->node_color == RED_NODE);
  llrbtree->root_node = insert_node(llrbtree->root_node, yi_node);
  assert(llrbtree->root_node == rodman_node);
  assert(llrbtree->root_node->left == jordan_node);
  assert(llrbtree->root_node->left->node_color == BLACK_NODE);
  assert(llrbtree->root_node->right == yi_node);
  assert(llrbtree->root_node->right->node_color == BLACK_NODE);
  // free_nodes();
  return TEST_PASSED;
}

// LR型旋转
TestResult test_left_rotate_then_right() {
  LLRBTree *llrbtree = create_llrbtree();
  init_player_data();
  llrbtree->root_node = insert_node(llrbtree->root_node, sharq_node);
  assert(llrbtree->root_node == sharq_node);
  llrbtree->root_node = insert_node(llrbtree->root_node, rodman_node);
  llrbtree->root_node = insert_node(llrbtree->root_node, sga_node);
  assert(llrbtree->root_node == sga_node);
  assert(sga_node->left == rodman_node);
  assert(sga_node->right == sharq_node);
  assert(sga_node->node_color == BLACK_NODE);
  assert(sga_node->left->node_color == BLACK_NODE);
  assert(sga_node->right->node_color == BLACK_NODE);
  // free_nodes();
  return TEST_PASSED;
}

// 插入元素顺序按照build_llrbtree函数的来，即test_data中的元素排列顺序，比较方便检查插入结果
TestResult test_check_after_each_insert() {
  LLRBTree *llrbtree = create_llrbtree();
  TreeNode *test_root = NULL;
  init_player_data();
  llrbtree->root_node = insert_node(llrbtree->root_node, jordan_node);
  test_root = llrbtree->root_node;
  Stack *stack = create_stack();
  push_node_to_stack(stack, test_root);
  TreeNode *print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  char *root_player = ((PLAYER *)test_root->tree_data)->pname;
  assert(strcmp(root_player, "Jordan") == 0);
  assert(test_root->node_color == BLACK_NODE);
  log_i("jordan insert complete.");

  llrbtree->root_node = insert_node(llrbtree->root_node, kobe_node);
  test_root = llrbtree->root_node;
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  char *root_right = ((PLAYER *)test_root->tree_data)->pname;
  assert(strcmp(root_right, "Kobe") == 0);
  assert(test_root->node_color == BLACK_NODE);
  log_i("kobe insert complete.");

  llrbtree->root_node = insert_node(llrbtree->root_node, yao_node);
  test_root = llrbtree->root_node;
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  char *kobe_right = ((PLAYER *)test_root->right->tree_data)->pname;
  assert(strcmp(kobe_right, "Yao") == 0);
  assert(test_root->node_color == BLACK_NODE);
  log_i("yao insert complete.");

  llrbtree->root_node = insert_node(llrbtree->root_node, yi_node);
  test_root = llrbtree->root_node;
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  char *yi = ((PLAYER *)test_root->right->tree_data)->pname;
  assert(strcmp(yi, "Yi") == 0);
  assert(test_root->node_color == BLACK_NODE);
  log_i("yi insert complete.");

  llrbtree->root_node = insert_node(llrbtree->root_node, camelo_node);
  test_root = llrbtree->root_node;
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  char *melo = ((PLAYER *)test_root->left->left->tree_data)->pname;
  assert(strcmp(melo, "Camelo") == 0);
  assert(test_root->node_color == BLACK_NODE);
  log_i("camelo insert complete.");

  llrbtree->root_node = insert_node(llrbtree->root_node, dunken_node);
  test_root = llrbtree->root_node;
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  char *dunken = ((PLAYER *)test_root->left->tree_data)->pname;
  assert(strcmp(dunken, "Dunken") == 0);
  assert(test_root->node_color == BLACK_NODE);
  log_i("dunken insert complete.");

  llrbtree->root_node = insert_node(llrbtree->root_node, curry_node);
  test_root = llrbtree->root_node;
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  char *dunken_left = ((PLAYER *)test_root->left->left->tree_data)->pname;
  assert(strcmp(dunken_left, "Curry") == 0);
  assert(test_root->node_color == BLACK_NODE);
  log_i("curry insert complete.");

  llrbtree->root_node = insert_node(llrbtree->root_node, jimmy_node);
  test_root = llrbtree->root_node;
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  char *jimmy = ((PLAYER *)test_root->left->right->left->tree_data)->pname;
  assert(strcmp(jimmy, "Jimmy") == 0);
  assert(test_root->node_color == BLACK_NODE);
  log_i("jimmy insert complete.");

  llrbtree->root_node = insert_node(llrbtree->root_node, book_node);
  test_root = llrbtree->root_node;
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  char *book = ((PLAYER *)test_root->left->left->tree_data)->pname;
  assert(strcmp(book, "Book") == 0);
  assert(test_root->node_color == BLACK_NODE);
  log_i("book insert complete.");

  llrbtree->root_node = insert_node(llrbtree->root_node, paul_node);
  test_root = llrbtree->root_node;
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  char *mac_right = ((PLAYER *)test_root->tree_data)->pname;
  assert(strcmp(dunken_left, "Paul") == 0);
  assert(test_root->node_color == BLACK_NODE);
  log_i("paul insert complete.");

  llrbtree->root_node = insert_node(llrbtree->root_node, rodman_node);
  test_root = llrbtree->root_node;
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  char *shar_left = ((PLAYER *)test_root->tree_data)->pname;
  assert(strcmp(dunken_left, "Rodman") == 0);
  assert(test_root->node_color == BLACK_NODE);
  log_i("rodman insert complete.");

  llrbtree->root_node = insert_node(llrbtree->root_node, jokic_node);
  test_root = llrbtree->root_node;
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  char *root_left = (char *)((PLAYER *)test_root->left->tree_data)->pname;
  assert(strcmp(root_left, "Jokic") == 0);
  assert(test_root->left->node_color == RED_NODE);
  log_i("jokic insert complete.");

  llrbtree->root_node = insert_node(llrbtree->root_node, yang_node);
  test_root = llrbtree->root_node;
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  char *yao_left = (char *)((PLAYER *)test_root->right->tree_data)->pname;
  assert(strcmp(yao_left, "Yang") == 0);
  assert(test_root->right->node_color == BLACK_NODE);
  log_i("yang insert complete.");

  llrbtree->root_node = insert_node(llrbtree->root_node, sharq_node);
  test_root = llrbtree->root_node;
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  char *sharq = (char *)((PLAYER *)yi_node->left->tree_data)->pname;
  assert(strcmp(sharq, "Sharq") == 0);
  assert(yi_node->left->node_color == RED_NODE);
  assert(yi_node->node_color == BLACK_NODE);
  assert(jokic_node->node_color == BLACK_NODE);
  log_i("sharq insert complete.");

  llrbtree->root_node = insert_node(llrbtree->root_node, sga_node);
  test_root = llrbtree->root_node;
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  char *sga = (char *)((PLAYER *)jokic_node->left->tree_data)->pname;
  assert(strcmp(sga, "Sga") == 0);
  assert(jokic_node->left->node_color == RED_NODE);
  assert(jokic_node->node_color == BLACK_NODE);
  log_i("sga insert complete.");

  llrbtree->root_node = insert_node(llrbtree->root_node, edwards_node);
  test_root = llrbtree->root_node;
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  char *jimmy_left = (char *)((PLAYER *)jimmy_node->left->tree_data)->pname;
  char *jimmy_right = (char *)((PLAYER *)jimmy_node->right->tree_data)->pname;
  assert(strcmp(jimmy_left, "Book") == 0);
  assert(strcmp(jimmy_right, "Jokic") == 0);
  assert(test_root->left == jimmy_node);
  assert(jimmy_node->left->node_color == RED_NODE);
  assert(jimmy_node->right->node_color == RED_NODE);
  assert(jimmy_node->node_color == BLACK_NODE);
  log_i("edwards insert complete.");

  llrbtree->root_node = insert_node(llrbtree->root_node, klay_node);
  test_root = llrbtree->root_node;
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  assert(book_node->right == dunken_node);
  assert(jimmy_node->left->node_color == BLACK_NODE);
  assert(jimmy_node->right->node_color == BLACK_NODE);
  assert(jimmy_node->node_color == RED_NODE);
  log_i("klay insert complete.");

  llrbtree->root_node = insert_node(llrbtree->root_node, hill_node);
  test_root = llrbtree->root_node;
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  assert(jimmy_node->left == camelo_node);
  assert(camelo_node->left == book_node);
  assert(camelo_node->right == dunken_node);
  assert(camelo_node->node_color == BLACK_NODE);
  assert(camelo_node->left->node_color == RED_NODE);
  assert(camelo_node->right->node_color == RED_NODE);
  log_i("hill insert complete.");

  llrbtree->root_node = insert_node(llrbtree->root_node, durant_node);
  test_root = llrbtree->root_node;
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  assert(test_root->right == rodman_node);
  assert(test_root->right->right == yi_node);
  assert(test_root->right->left == paul_node);
  assert(test_root->right->node_color == BLACK_NODE);
  assert(test_root->right->right->node_color == RED_NODE);
  assert(test_root->right->left->node_color == RED_NODE);
  log_i("durant insert complete.");

  test_root = insert_node(llrbtree->root_node, wade_node);
  test_root = llrbtree->root_node;
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  log_i("wade insert complete.");
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

  test_root = insert_node(llrbtree->root_node, lebron_node);
  llrbtree->root_node = test_root;
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  log_i("lebron insert complete.");

  test_root = insert_node(llrbtree->root_node, iverson_node);
  llrbtree->root_node = test_root;
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  log_i("iverson insert complete.");

  test_root = insert_node(llrbtree->root_node, macgrady_node);
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  log_i("macgrady insert complete.");

  test_root = insert_node(llrbtree->root_node, kawhi_node);
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  log_i("kawhi insert complete.");
  assert(test_root->right == rodman_node);
  assert(rodman_node->left == jordan_node);
  assert(rodman_node->left->node_color == RED_NODE);
  assert(rodman_node->left->right == paul_node);
  assert(rodman_node->right == yao_node);

  test_root = insert_node(llrbtree->root_node, doncic_node);
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  log_i("doncic insert complete.");
  assert(sharq_node->left == sga_node);
  assert(sharq_node->right == yang_node);

  test_root = insert_node(llrbtree->root_node, carter_node);
  llrbtree->root_node = test_root;
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  log_i("carter insert complete.");
  assert(test_root->left->node_color == BLACK_NODE);
  assert(test_root->left->right == dunken_node);
  assert(test_root->left->right->node_color == BLACK_NODE);

  test_root = insert_node(llrbtree->root_node, chris_node);
  stack = create_stack();
  push_node_to_stack(stack, test_root);
  print_node = NULL;
  while (!is_stack_empty(stack)) {
    print_node = pop(stack, print_node);
    char *player_name = ((PLAYER *)((TreeNode *)print_node)->tree_data)->pname;
    if (stack->top < 0) {
      printf("%s.\n", player_name);
      break;
    }
    printf("%s, ", player_name);
  }
  free(stack);
  log_i("chris insert complete.");
  assert(kobe_node->left == klay_node);
  assert(kobe_node->right == paul_node);

  // free_nodes();
  return TEST_PASSED;
}

TestResult test_insert_node_at_left_branch() {
  LLRBTree *llrbtree = create_llrbtree();
  TreeNode *test_root = NULL;
  test_root = build_tree_manualy(test_root);
  if (test_root == NULL) {
    log_d("Didn't get right tree node.");
    return TEST_FAILED;
  }
  insert_node(llrbtree->root_node, curry_node);
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
  LLRBTree *llrbtree = create_llrbtree();
  TreeNode *test_root = NULL;
  test_root = build_tree_manualy(test_root);
  if (test_root == NULL) {
    log_d("Didn't get right tree node.");
    return TEST_FAILED;
  }
  insert_node(llrbtree->root_node, curry_node);
  insert_node(llrbtree->root_node, book_node);
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
  LLRBTree *llrbtree = create_llrbtree();
  TreeNode *test_root = NULL;
  test_root = build_tree_manualy(test_root);
  if (test_root == NULL) {
    log_d("Didn't get right tree node.");
    return TEST_FAILED;
  }
  insert_node(llrbtree->root_node, curry_node);
  insert_node(llrbtree->root_node, dunken_node);
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
  LLRBTree *llrbtree = create_llrbtree();
  TreeNode *test_root = NULL;
  test_root = build_tree_manualy(test_root);
  if (test_root == NULL) {
    log_d("Didn't get right tree node.");
    return TEST_FAILED;
  }
  insert_node(llrbtree->root_node, yang_node);
  insert_node(llrbtree->root_node, yao_node);
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
  // free_nodes();
  return TEST_PASSED;
}

TestResult test_insert_node_at_right_left_branch() {
  LLRBTree *llrbtree = create_llrbtree();
  TreeNode *test_root = NULL;
  test_root = build_tree_manualy(test_root);
  if (test_root == NULL) {
    log_d("Didn't get right tree node.");
    return TEST_FAILED;
  }
  insert_node(llrbtree->root_node, yang_node);
  insert_node(llrbtree->root_node, wade_node);
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
  // free_nodes();
  return TEST_PASSED;
}
