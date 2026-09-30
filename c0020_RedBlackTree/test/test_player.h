#ifndef TEST_PLAYER
#define TEST_PLAYER

#include "../src/red_black_tree.h"
#include "test_and_validation.h"

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

TreeNode *build_tree_manualy(TreeNode *);

// test rotate node
TestResult test_left_rotate();
TestResult test_right_rotate();
TestResult test_left_rotate_then_right();
TestResult test_right_rotate_then_left();

// test insert node
TestResult test_clear_tree();
TestResult test_build_player_tree_by_name();
TestResult test_insert_node_as_root_node();
TestResult test_check_after_every_insert();
TestResult test_insert_node_exist();
TestResult test_insert_node_at_left_branch();
TestResult test_insert_node_at_left_left_branch();
TestResult test_insert_node_at_left_right_branch();
TestResult test_insert_node_at_right_right_branch();
TestResult test_insert_node_at_right_left_branch();
TestResult test_check_color_and_modify();
TestResult test_insert_LR_rotate_then_root_right_rotate();

// test delete node
// 3.1-1
TestResult test_delete_red_node();
// 1&3.3.1.1.2-root
TestResult test_delete_root_node_with_two_black_child();
// 3.2.1.1.1
TestResult test_delete_black_node_without_child_at_left_with_red_father();
// 3.3.1.1.1
TestResult test_delete_black_node_without_child_at_right_with_red_father();
// 1&3.3.1.2-root
TestResult test_delete_root_node_with_child();
// 3.2.2.2, 3.2.1.3, 3.2.1.2
TestResult test_delete_black_node_without_child_have_red_brother();

// test delete black node, only one child node
TestResult test_delete_black_node_at_left_child_with_single_child();
TestResult test_delete_black_node_at_right_child_with_single_child();
TestResult test_delete_red_node_at_left_child_();

// test delete black node, without child node
TestResult test_delete_black_node_at_left_child_without_child();
TestResult test_delete_black_node_at_right_child_without_child();

// test delete black node, with two child node
TestResult test_delete_black_node_at_left_child_with_two_child();

// 3.2.1.2
TestResult
test_delete_black_node_is_root_at_left_and_the_brother_have_red_right_child();
TestResult
test_delete_black_node_at_left_and_the_brother_have_red_right_child();
// 3.2.1.3
TestResult test_delete_black_node_at_left_and_the_brother_have_red_left_child();
// 3.2.1.4
TestResult
test_delete_black_node_at_left_and_the_brother_have_red_left_right_child();

// 3.2.2.1
TestResult
test_delete_black_node_at_left_and_red_brother_have_left_child_with_no_grand_child();

// 3.2.2.2
TestResult
test_delete_black_node_at_left_and_red_brother_have_left_child_with_left_grand_child();

// 3.2.2.3
TestResult
test_delete_black_node_at_left_and_red_brother_have_left_child_with_right_grand_child();

// 3.2.2.4
TestResult
test_delete_black_node_at_left_and_red_brother_have_left_child_with_left_right_grand_child();

// 3.3.1.4
TestResult
test_delete_black_node_at_right_and_the_brother_have_red_left_right_child();

// 3.3.1.1.1
TestResult
test_delete_black_node_at_right_and_brother_have_no_child_and_red_father();

// 3.3.1.2
TestResult
test_delete_black_node_at_right_child_and_the_brother_have_red_left_child();
TestResult
test_delete_black_node_at_right_child_and_the_brother_have_red_left_child_2();

// 3.3.1.3
TestResult
test_delete_black_node_at_right_child_and_the_brother_have_red_right_child();

// 3.3.2.1
TestResult
test_delete_black_node_at_right_child_and_right_child_of_brother_have_no_child();

// 3.3.2.2
TestResult
test_delete_black_node_at_right_child_and_right_child_of_brother_have_left_child();

// 3.3.2.3
TestResult
test_delete_black_node_at_right_child_and_right_child_of_brother_have_right_child();

// 3.3.2.4
TestResult
test_delete_black_node_at_right_child_and_right_child_of_brother_have_left_right_child();

// 3.2.1.1.2-1，双黑场景1
TestResult test_delete_double_black_node_at_left_1();
TestResult test_delete_double_black_node_at_left_2();
TestResult test_delete_double_black_node_at_left_3();
TestResult test_delete_double_black_node_at_left_4();

// 3.3.1.1.2
TestResult test_delete_double_black_node_at_right();

// 2.2
TestResult test_delete_black_node_at_right_and_have_a_single_red_right_child();
// 2.2-1
TestResult
test_delete_black_node_at_right_and_have_a_single_red_right_child_1();
// 2.1-1
TestResult test_delete_black_node_at_left_and_have_a_single_red_left_child();
// 2.1-2
TestResult test_delete_black_node_at_left_and_have_red_left_right_child();

// 1&3.3
TestResult test_delete_black_node_at_right_and_the_behind_node_is_red();
// 1&3.2.1.4
TestResult test_delete_black_node_at_left_and_have_two_different_color_child();
// 1&3.1
TestResult
test_delete_red_node_at_right_and_have_two_black_color_child_and_red_behind_node();
// 3.1-2
TestResult test_delete_many_red_node_without_child();
// 3.2.1.1.2-5
TestResult test_delete_double_black_node_at_left_5();
// 3.3.1.1.2-1
TestResult test_delete_double_black_node_at_right_1();
// 3.2.1.1.2-6
TestResult test_delete_double_black_node_at_left_6();

// test delete double black node
TestResult test_delete_double_black_node_at_left_child();

// test traversal
TestResult test_preorder_traversal_without_recurse();
TestResult test_preorder_traversal_without_recurse_2();
TestResult test_inorder_traversal();
TestResult test_inorder_traversal_without_recurse();
TestResult test_postorder_traversal();
TestResult test_postorder_traversal_without_recurse();
TestResult test_postorder_traversal_without_recurse_2();
TestResult test_mixedorder_traversal_without_recurse();
TestResult test_level_traversal();

void free_nodes();

TestResult test_player_tree();

#endif // TEST_PLAYER
