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

typedef enum { PLAYER_NODE, PLAYER_NAME, PLAYER_YEAR } NODE_TYPE;
typedef struct TreeNode TreeNode;

struct TreeNode {
  // NODE_TYPE node_t;
  void *tree_data;
  TreeNode *left;
  TreeNode *right;
};

typedef bool (*func_compare)(void *, void *);
typedef void (*func_print)(TreeNode *);

TreeNode *build_tree();

bool is_tree_empty(TreeNode *);

TreeNode *insert_tree_node(TreeNode *, void *);
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
