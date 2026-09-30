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
  char *paul = ((PLAYER *)test_root->right->left->right->tree_data)->pname;
  assert(strcmp(paul, "Paul") == 0);
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
  char *rodman = ((PLAYER *)test_root->right->left->right->tree_data)->pname;
  assert(strcmp(rodman, "Rodman") == 0);
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
  char *jokic = (char *)((PLAYER *)test_root->left->right->tree_data)->pname;
  assert(strcmp(jokic, "Jokic") == 0);
  assert(test_root->left->right->node_color == BLACK_NODE);
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
  char *yang =
      (char *)((PLAYER *)test_root->right->left->right->tree_data)->pname;
  assert(strcmp(yang, "Yang") == 0);
  assert(test_root->right->left->right->node_color == BLACK_NODE);
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
  char *sharq =
      (char *)((PLAYER *)test_root->right->left->right->left->tree_data)->pname;
  assert(strcmp(sharq, "Sharq") == 0);
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
  char *sga =
      (char *)((PLAYER *)test_root->right->left->right->tree_data)->pname;
  assert(strcmp(sga, "Sga") == 0);
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
  assert(strcmp(jimmy_left, "Edwards") == 0);
  assert(test_root->left->right->left == jimmy_node);
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
  char *klay =
      (char *)((PLAYER *)test_root->left->right->right->tree_data)->pname;
  assert(strcmp(klay, "Klay") == 0);
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
  char *hill =
      (char *)((PLAYER *)test_root->left->right->left->tree_data)->pname;
  assert(strcmp(hill, "Hill") == 0);
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
  char *durant =
      (char *)((PLAYER *)test_root->left->right->left->left->left->tree_data)
          ->pname;
  assert(strcmp(durant, "Durant") == 0);
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
  char *wade =
      (char *)((PLAYER *)test_root->right->right->left->left->tree_data)->pname;
  assert(strcmp(wade, "Wade") == 0);
  log_i("wade insert complete.");

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
  char *lebron =
      (char *)((PLAYER *)test_root->right->left->left->left->tree_data)->pname;
  assert(strcmp(lebron, "Lebron") == 0);
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
  char *iverson =
      (char *)((PLAYER *)test_root->left->right->left->right->left->tree_data)
          ->pname;
  assert(strcmp(iverson, "Iverson") == 0);
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
  char *mac =
      (char *)((PLAYER *)test_root->right->left->left->tree_data)->pname;
  assert(strcmp(mac, "Macgrady") == 0);
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
  char *kawhi = (char *)((PLAYER *)test_root->left->right->tree_data)->pname;
  assert(strcmp(kawhi, "Kawhi") == 0);
  log_i("kawhi insert complete.");

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
  char *doncic =
      (char *)((PLAYER *)test_root->left->left->left->right->tree_data)->pname;
  assert(strcmp(doncic, "Doncic") == 0);
  log_i("doncic insert complete.");

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
  char *carter =
      (char *)((PLAYER *)test_root->left->left->left->left->right->tree_data)
          ->pname;
  assert(strcmp(carter, "Carter") == 0);
  log_i("carter insert complete.");

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
  char *chris =
      (char *)((PLAYER *)test_root->left->left->left->left->right->tree_data)
          ->pname;
  assert(strcmp(chris, "Chris") == 0);
  log_i("chris insert complete.");

  // free_nodes();
  return TEST_PASSED;
}
