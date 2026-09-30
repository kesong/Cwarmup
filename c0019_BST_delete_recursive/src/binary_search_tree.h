#ifndef BSTREE_VAR
#define BSTREE_VAR

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

typedef struct TreeNode TreeNode;

struct TreeNode {
  void *tree_data;
  TreeNode *left;
  TreeNode *right;
};

typedef int (*func_compare)(TreeNode *, TreeNode *);
typedef void (*func_print)(TreeNode *);

TreeNode *build_tree();

bool is_tree_empty(TreeNode *);

TreeNode *min_tree_node(TreeNode *);
TreeNode *max_tree_node(TreeNode *);

CompareResult compare_node(TreeNode *, TreeNode *, func_compare);

TreeNode *insert_tree_node(TreeNode *, TreeNode *);
TreeNode *insert_node(TreeNode *);

TreeNode *delete_tree_node_min(TreeNode *);
TreeNode *delete_tree_node_max(TreeNode *);
TreeNode *min_tree_node(TreeNode *);
TreeNode *max_tree_node(TreeNode *);
TreeNode *delete_tree_node(TreeNode *, TreeNode *);
void delete_node(TreeNode *);

TreeNode *preorder_traversal(TreeNode *, TreeNode **, int *);
TreeNode *preorder_traversal_without_recurse(TreeNode *, TreeNode **, void *);
TreeNode *preorder_traversal_without_recurse_2(TreeNode *, TreeNode **, void *);
TreeNode *inorder_traversal(TreeNode *, TreeNode **, int *);
TreeNode *inorder_traversal_without_recurse(TreeNode *, TreeNode **, void *);
TreeNode *postorder_traversal(TreeNode *, TreeNode **, int *);
TreeNode *postorder_traversal_without_recurse(TreeNode *, TreeNode **, void *);
TreeNode *postorder_traversal_without_recurse_2(TreeNode *, TreeNode **,
                                                void *);
TreeNode *mixedorder_traversal_without_recurse(TreeNode *, TreeNode **, void *);
TreeNode *level_traversal(TreeNode *, TreeNode **, void *);

#endif // BSTREE_VAR
