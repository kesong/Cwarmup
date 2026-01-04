#include "print_ADT.h"

void print_player_node(TreeNode *p_node) {
  PLAYER *player = NULL;
  player = (PLAYER *)(p_node->tree_data);
  // log_i("%s", "this node is a PLAYER_NODE.");
  log_i("%6s:%20s", "Name", player->pname);
  log_i("%6s:%20d", "Number", player->pnumber);
  log_i("%6s:%20d", "Salary", player->salary);
  log_i("%6s:%20s", "Team", player->tm->tname);
  log_i("%6s:%20s", "City", player->tm->city);
  print_seperator(COLOR_YELLOW, "*");
}

/*
void print_player_name(NODE *p_node) {
  log_d("this node is a PLAYER_NAME.\n");
  char *player_name = NULL;
  player_name = (char *)p_node->ptr_data;
  log_d("%s%-20s", "Player name: ", player_name);
  print_seperator(COLOR_GREEN, "*");
}

void print_player_year(NODE *p_node) {
  log(COLOR_RED, "year", "%s", "this node is a PLAYER_YEAR.");
  // int player_year = (int)p_node->ptr_data;
  //
//int占用4位，ptr_data是void*类型，占用8位，将一个8位的数据转化为一个4位的数据，这里强制转换以后会有数值的错误；
  int *player_year_addr =
      (int *)p_node
          ->ptr_data; //
使用int*接收void*可以解决这个问题，但是能否彻底解决这个问题有待验证和思考
  log(COLOR_RED, "%s%d", "Player career start year: ", *player_year_addr);
  print_seperator(COLOR_MAGENTA, "*");
}

void print_tree_node(NODE *print_node) {
  if (is_empty()) {
    log_w("%s", "NONE: empty tree!");
    return;
  }
  if (print_node != NULL && print_node->ptr_data != NULL) {
    switch (print_node->node_t) {
    case PLAYER_NODE:
      print_player_node(print_node);
      break;
    case PLAYER_NAME:
      print_player_name(print_node);
      break;
    case PLAYER_YEAR:
      print_player_year(print_node);
      break;
    default:
      log_e("%s", "error: no info found!");
      break;
    }
  }
}
*/

void print_tree(TreeNode *root_node) {
  if (root_node == NULL || root_node->tree_data == NULL) {
    printf("Empty tree - nothing to print\n");
    return;
  }
  TreeNode *trav_result[MAX_SIZE];
  for (int i = 0; i < MAX_SIZE; i++) {
    trav_result[i] = NULL;
  }
  int index = 0;
  preorder_traversal(root_node, trav_result, &index);
  for (int i = 0; i < MAX_SIZE; i++) {
    if (trav_result[i] != NULL) {
      print_player_node(trav_result[i]);
    }
  }
}

void print_traversal_result_array(TreeNode **result_array) {
  if (result_array == NULL) {
    return;
  }
  for (int i = 0; *(result_array + i) != NULL; i++) {
    TreeNode *result = NULL;
    PLAYER *player_node = NULL;
    result = *(result_array + i);
    if (result == NULL) {
      break;
    }
    player_node = (PLAYER *)result->tree_data;
    if (*(result_array + i + 1) != NULL) {
      printf("%s", player_node->pname);
      printf(", ");
    } else
      printf("%s.\n", player_node->pname);
  }
  print_seperator(COLOR_MAGENTA, "*");
}

void print_tree_in_specified_order(TreeNode *start_node,
                                   traversal_function trav_func) {
  if (start_node == NULL || start_node->tree_data == NULL) {
    printf("Empty tree - nothing to print\n");
    return;
  }
  TreeNode *trav_result[MAX_SIZE];
  for (int i = 0; i < MAX_SIZE; i++) {
    trav_result[i] = NULL;
  }
  int index = 0;
  trav_func(start_node, trav_result, &index);
  print_traversal_result_array(trav_result);
  for (int i = 0; i < MAX_SIZE; i++) {
    if (trav_result[i] != NULL) {
      print_player_node(trav_result[i]);
    }
  }
}
