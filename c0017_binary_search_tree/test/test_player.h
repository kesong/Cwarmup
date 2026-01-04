#ifndef TEST_PLAYER
#define TEST_PLAYER

#include "binary_search_tree.h"``

typedef struct player PLAYER;
typedef struct team TEAM;

struct player {
  char *pname;
  int pnumber;
  int salary;
  struct team *tm;
};

struct team {
  char *tname;
  char *city;
};

void init_player_data();
int search_tree_node(TreeNode *, void *, NodeEnum, TreeNode *);
void delete_tree_node(TreeNode *, void *, NodeEnum);
TreeNode *get_most_right_node_from_left_tree(TreeNode *);
TreeNode *get_most_left_node_from_right_tree(TreeNode *);

TreeNode *build_player_tree();

void test_preorder_traversal_without_recurse();
void test_preorder_traversal_without_recurse_2();
void test_inorder_traversal();
void test_inorder_traversal_without_recurse();
void test_postorder_traversal();
void test_postorder_traversal_without_recurse();
void test_postorder_traversal_without_recurse_2();
void test_mixedorder_traversal_without_recurse();
void test_level_traversal();

void test_player_tree();

#endif // TEST_PLAYER
