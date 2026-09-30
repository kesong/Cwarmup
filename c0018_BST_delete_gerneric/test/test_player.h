#ifndef TEST_PLAYER
#define TEST_PLAYER

#include "../src/binary_search_tree.h"

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

int compare_node_by_name(TreeNode *, TreeNode *);
int compare_node_by_number(TreeNode *, TreeNode *);

LeftOrRight node_is_left_or_right(TreeNode *, TreeNode *);

void init_player_data();

TreeNode *build_player_tree_by_name();
TreeNode *build_player_tree_by_number();

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
