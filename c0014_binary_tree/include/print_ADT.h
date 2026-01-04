#ifndef PRINT_ADT
#define PRINT_ADT

#include "../test/test_player.h"
#include "binary_tree.h"
#include "log.h"
#include <iso646.h>

typedef void *(*traversal_function)(TreeNode *, TreeNode **, void *);

void print_player_node(TreeNode *);

// void print_player_name(NODE *);

// void print_player_year(NODE *);

// void print_tree_node(NODE *);

void print_tree(TreeNode *);

void print_traversal_result_array(TreeNode **);

void print_tree_in_specified_order(TreeNode *, traversal_function);

#endif
