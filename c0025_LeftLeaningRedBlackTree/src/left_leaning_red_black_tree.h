#ifndef LLRBTREE_VAR
#define LLRBTREE_VAR

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/queue.h"
#include "../lib/stack.h"

#define LENGTH 10
#define TREENODE_ARRAY_LENGTH 10

typedef enum { LEFT_NODE, RIGHT_NODE } LeftOrRight;

typedef enum { N_EQUAL, N_GREATER, N_SMALLER, N_ERROR } CompareResult;

typedef enum { RED_NODE, BLACK_NODE, DOUBLE_BLACK_NODE } NODE_COLOR;

typedef struct TreeNode TreeNode;

struct TreeNode {
  void *tree_data;
  TreeNode *left;
  TreeNode *right;
  NODE_COLOR node_color;
};

typedef struct {
  TreeNode *root_node;
} LLRBTree;

typedef int (*func_compare)(TreeNode *, TreeNode *);
typedef void (*func_print)(TreeNode *);

LLRBTree *create_llrbtree();
bool is_tree_empty(TreeNode *);
CompareResult compare_node(TreeNode *, TreeNode *, func_compare);
TreeNode *left_rotate(TreeNode *);
TreeNode *right_rotate(TreeNode *);
// TreeNode *left_rotate_then_right(TreeNode *, TreeNode *);
// TreeNode *right_rotate_then_left(TreeNode *, TreeNode *);
TreeNode *flip_color(TreeNode *);

bool is_red(TreeNode *);
LeftOrRight child_is_left_or_right(TreeNode *, TreeNode *);
TreeNode *check_color_and_modify(TreeNode *, TreeNode *);
TreeNode *insert_tree_node(TreeNode *, TreeNode *, TreeNode *);
TreeNode *insert_node(TreeNode *, TreeNode *);

TreeNode *delete_tree_node_min(TreeNode *, TreeNode *);
TreeNode *delete_tree_node_max(TreeNode *, TreeNode *);

TreeNode *min_tree_node(TreeNode *);
TreeNode *max_tree_node(TreeNode *);

TreeNode *swap_node(TreeNode *, TreeNode *);
void swap_node_color(TreeNode *, TreeNode *);
TreeNode *left_rotate_without_color_change(TreeNode *);
TreeNode *right_rotate_without_color_change(TreeNode *);
// delete node
TreeNode *delete_tree_node_is_red_without_child(TreeNode *, TreeNode *,
                                                LeftOrRight);
TreeNode *black_brother_node_without_child_and_red_father(TreeNode *,
                                                          TreeNode *);
TreeNode *black_brother_node_RR(TreeNode *, TreeNode *);
TreeNode *black_brother_node_RL(TreeNode *, TreeNode *);
TreeNode *delete_node_at_left_and_the_brother_node_is_black(TreeNode *,
                                                            TreeNode *,
                                                            TreeNode *);
TreeNode *delete_node_at_left_and_the_brother_node_is_red(TreeNode *,
                                                          TreeNode *,
                                                          TreeNode *);
TreeNode *black_brother_node_LL(TreeNode *, TreeNode *);
TreeNode *black_brother_node_LR(TreeNode *, TreeNode *);
TreeNode *delete_node_at_right_and_the_brother_node_is_black(TreeNode *,
                                                             TreeNode *,
                                                             TreeNode *);
TreeNode *delete_node_at_right_and_the_brother_node_is_red(TreeNode *,
                                                           TreeNode *,
                                                           TreeNode *);
TreeNode *black_brother_node_double_black(TreeNode *, TreeNode *, TreeNode *);
TreeNode *delete_tree_node(TreeNode *, TreeNode *, TreeNode *);
void delete_node(TreeNode *, TreeNode *);

TreeNode *push_node_to_stack(Stack *, TreeNode *);
TreeNode *clear_tree(TreeNode *, TreeNode *);

TreeNode *preorder_traversal(TreeNode *, TreeNode **, void *);
TreeNode *preorder_traversal_without_recurse(TreeNode *, TreeNode **, void *);
TreeNode *preorder_traversal_without_recurse_2(TreeNode *, TreeNode **, void *);
TreeNode *inorder_traversal(TreeNode *, TreeNode **, void *);
TreeNode *inorder_traversal_without_recurse(TreeNode *, TreeNode **, void *);
TreeNode *postorder_traversal(TreeNode *, TreeNode **, void *);
TreeNode *postorder_traversal_without_recurse(TreeNode *, TreeNode **, void *);
TreeNode *postorder_traversal_without_recurse_2(TreeNode *, TreeNode **,
                                                void *);
TreeNode *mixedorder_traversal_without_recurse(TreeNode *, TreeNode **, void *);
TreeNode *level_traversal(TreeNode *, TreeNode **, void *);

#endif
