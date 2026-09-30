#include "test_player.h"
#include "../include/log.h"
#include "../src/print_ADT.h"
#include "data_process.h"
#include "test_and_validation.h"

#include <stdlib.h>
#include <string.h>

// extern TreeNode *root_node;
// extern TreeNode *root_node_bak;

int compare_node_by_name(TreeNode *node_in_tree, TreeNode *node_input) {
  PLAYER *player_in_tree = (PLAYER *)node_in_tree->tree_data;
  char *player_name_in_tree = (char *)player_in_tree->pname;
  PLAYER *player_input = (PLAYER *)node_input->tree_data;
  char *player_name_in_node = (char *)player_input->pname;
  if (strcmp(player_name_in_tree, player_name_in_node) > 0) {
    return -1;
  } else if (strcmp(player_name_in_tree, player_name_in_node) == 0) {
    return 0;
  } else {
    return 1;
  }
}

int compare_node_by_number(TreeNode *node_in_tree, TreeNode *node_input) {
  PLAYER *player_in_tree = (PLAYER *)node_in_tree->tree_data;
  int player_number_in_tree = (int)player_in_tree->pnumber;
  PLAYER *player_input = (PLAYER *)node_input->tree_data;
  int player_number_in_node = (int)player_input->pnumber;
  if (player_number_in_tree > player_number_in_node) {
    return -1;
  } else if (player_number_in_tree == player_number_in_node) {
    return 0;
  } else {
    return 1;
  }
}

LeftOrRight node_is_left_or_right(TreeNode *search_result_node,
                                  TreeNode *search_result_node_parent) {
  char *search_result_node_player =
      (char *)((PLAYER *)search_result_node->tree_data)->pname;
  char *search_result_parent_left_player = NULL;
  char *search_result_parent_right_player = NULL;
  if (search_result_node_parent != NULL) {
    if (search_result_node_parent->left != NULL) {
      search_result_parent_left_player =
          (char *)((PLAYER *)search_result_node_parent->left->tree_data)->pname;
      if (strcmp(search_result_node_player, search_result_parent_left_player) ==
          0) {
        return LEFT_NODE;
      }
    }
    if (search_result_node_parent->right != NULL) {
      search_result_parent_right_player =
          (char *)((PLAYER *)search_result_node_parent->right->tree_data)
              ->pname;
      if (strcmp(search_result_node_player,
                 search_result_parent_right_player) == 0) {
        return RIGHT_NODE;
      }
    }
  }
  return -1;
}

// 结构体指针作为局部变量，如果只是临时用来接收另一个结构体指针的地址，以及传递地址给其他结构体指针，无需使用malloc分配空间，指向NULL完成初始化就可以。
// 如果需要接收其他结构体传递过来的数据，需要使用malloc分配空间，否则无法接收其他结构体指针中的数据，没有为结构体指针分配空间，那么结构体成员也就无法接收数据
// 使用完要将这个结构体指针的局部变量释放掉，能在本函数内直接释放的就在函数内释放，函数内无法释放的就在调用函数完成后释放。
// 这里只是用来接收各个节点的地址，不能用malloc分配空间，比如某个接收TreeNode地址的指针使用malloc分配空间后，接收的就只是节点地址了，无法保持树的连接关系
TreeNode *jordan_node = NULL;
TreeNode *kobe_node = NULL;
TreeNode *yao_node = NULL;
TreeNode *yi_node = NULL;
TreeNode *camelo_node = NULL;
TreeNode *dunken_node = NULL;
TreeNode *curry_node = NULL;
TreeNode *jimmy_node = NULL;
TreeNode *paul_node = NULL;
TreeNode *sharq_node = NULL;
TreeNode *yang_node = NULL;
TreeNode *rodman_node = NULL;
TreeNode *jokic_node = NULL;
TreeNode *book_node = NULL;
TreeNode *sga_node = NULL;
TreeNode *edwards_node = NULL;
TreeNode *klay_node = NULL;
TreeNode *hill_node = NULL;
TreeNode *durant_node = NULL;
TreeNode *wade_node = NULL;
TreeNode *lebron_node = NULL;
TreeNode *iverson_node = NULL;
TreeNode *macgrady_node = NULL;
TreeNode *kawhi_node = NULL;
TreeNode *doncic_node = NULL;
TreeNode *carter_node = NULL;
TreeNode *chris_node = NULL;

static PLAYER *kobe = NULL;
static PLAYER *jordan = NULL;
static PLAYER *yao = NULL;
static PLAYER *yi = NULL;
static PLAYER *camelo = NULL;
static PLAYER *dunken = NULL;
static PLAYER *curry = NULL;
static PLAYER *jimmy = NULL;
static PLAYER *book = NULL;
static PLAYER *paul = NULL;
static PLAYER *rodman = NULL;
static PLAYER *jokic = NULL;
static PLAYER *yang = NULL;
static PLAYER *sharq = NULL;
static PLAYER *sga = NULL;
static PLAYER *edwards = NULL;
static PLAYER *klay = NULL;
static PLAYER *hill = NULL;
static PLAYER *durant = NULL;
static PLAYER *wade = NULL;
static PLAYER *lebron = NULL;
static PLAYER *iverson = NULL;
static PLAYER *macgrady = NULL;
static PLAYER *kawhi = NULL;
static PLAYER *doncic = NULL;
static PLAYER *carter = NULL;
static PLAYER *chris = NULL;

void init_player_data() {
  /* initial the player node.*/
  char *file_name = "test_data";
  char *current_path = NULL;
  char *test_path = NULL;
  char *file_path = NULL;
  PLAYER *result_arr[ARRAY_SIZE] = {NULL};
  TreeNode *node_arr[ARRAY_SIZE] = {NULL};
  get_player_array(file_name, current_path, test_path, file_path, result_arr);
  get_node_array(node_arr, result_arr);
  book_node = *(node_arr + 8);
  camelo_node = *(node_arr + 4);
  carter_node = *(node_arr + 25);
  chris_node = *(node_arr + 26);
  curry_node = *(node_arr + 6);
  doncic_node = *(node_arr + 24);
  dunken_node = *(node_arr + 5);
  durant_node = *(node_arr + 18);
  edwards_node = *(node_arr + 15);
  hill_node = *(node_arr + 17);
  iverson_node = *(node_arr + 21);
  jimmy_node = *(node_arr + 7);
  jokic_node = *(node_arr + 11);
  jordan_node = *node_arr;
  kawhi_node = *(node_arr + 23);
  klay_node = *(node_arr + 16);
  kobe_node = *(node_arr + 1);
  lebron_node = *(node_arr + 20);
  macgrady_node = *(node_arr + 22);
  paul_node = *(node_arr + 9);
  rodman_node = *(node_arr + 10);
  sga_node = *(node_arr + 14);
  sharq_node = *(node_arr + 13);
  wade_node = *(node_arr + 19);
  yang_node = *(node_arr + 12);
  yao_node = *(node_arr + 2);
  yi_node = *(node_arr + 3);

  // 测试27个球员，每个球员编一个整数号码，在使用第三方提供的在线可视化创建红黑树时候比较方便验证
  //(book, 0), (camelo, 50), (curry, 100), (doncic, 150), (dunken, 200),
  //(durant, 250), (edwards, 300), (hill, 350), (iverson, 400) (jimmy, 450),
  //(jokic, 500), (jordan, 550), (kawhi, 600), (klay, 650), (kobe, 700),
  //(lebron, 750), (macgrady, 800), (paul, 850), (rodman, 900), (sga, 950),
  //(sharq, 1000), (wade, 1050), (yang, 1100), (yao, 1150), (yi, 1200),
  //(carter, 60), (chris, 75)

  /* player node initialized complete.*/
}

/*
//
二叉树会对节点进行比较，所以可以根据插入的球员姓名构建二叉树，节点比较就变成了比较姓名的字符串
//
也可以对在构建球员树的时候对球员号码进行比较来构建二叉树，节点比较就是整数的比较
//
不管那种插入方式，构建树的时候都要指明构建树的类型，根据binary_search_tree的头文件里面的NodeEnum进行指定，插入的节点的时候也要指明是按照姓名来插入还是按照
// 球员号码来插入。
TreeNode *build_player_tree_by_name() {
  // root_node = build_tree();
  init_player_data();
  insert_node(jordan_node);
  insert_node(jokic_node);
  insert_node(yi_node);
  insert_node(rodman_node);
  insert_node(jimmy_node);
  insert_node(book_node);
  insert_node(dunken_node);
  insert_node(camelo_node);
  insert_node(paul_node);
  insert_node(curry_node);
  insert_node(yao_node);
  insert_node(kobe_node);
  insert_node(yang_node);
  insert_node(sharq_node);
  insert_node(sga_node);
  insert_node(edwards_node);
  insert_node(klay_node);
  insert_node(hill_node);
  insert_node(durant_node);
  insert_node(wade_node);
  insert_node(lebron_node);
  insert_node(iverson_node);
  insert_node(macgrady_node);
  insert_node(kawhi_node);
  insert_node(doncic_node);
  insert_node(carter_node);
  insert_node(chris_node);
  return root_node;
}  */

TreeNode *build_llrbtree() {
  LLRBTree *llrbtree = create_llrbtree();
  char *file_name = "test_data";
  char *current_path = NULL;
  char *test_path = NULL;
  char *file_path = NULL;
  PLAYER *result_arr[ARRAY_SIZE] = {NULL};
  TreeNode *node_arr[ARRAY_SIZE] = {NULL};
  get_player_array(file_name, current_path, test_path, file_path, result_arr);
  get_node_array(node_arr, result_arr);

  for (int i = 0; i < ARRAY_SIZE; i++) {
    llrbtree->root_node = insert_node(llrbtree->root_node, *(node_arr + i));
  }
  return llrbtree->root_node;
}

/*
void free_nodes() {
  free(kobe->tm), kobe->tm = NULL, free(kobe), kobe = NULL, free(kobe_node),
                  kobe_node = NULL;
  free(jordan->tm), jordan->tm = NULL, free(jordan), jordan = NULL,
                    free(jordan_node), jordan_node = NULL;
  free(yao->tm), yao->tm = NULL, free(yao), yao = NULL, free(yao_node),
                 yao_node = NULL;
  free(yi->tm), yi->tm = NULL, free(yi), yi = NULL, free(yi_node),
                yi_node = NULL;
  free(camelo->tm), camelo->tm = NULL, free(camelo), camelo = NULL,
                    free(camelo_node), camelo_node = NULL;
  free(dunken->tm), dunken->tm = NULL, free(dunken), dunken = NULL,
                    free(dunken_node), dunken_node = NULL;
  free(curry->tm), curry->tm = NULL, free(curry), curry = NULL,
                   free(curry_node), curry_node = NULL;
  free(jimmy->tm), jimmy->tm = NULL, free(jimmy), jimmy = NULL,
                   free(jimmy_node), jimmy_node = NULL;
  free(book->tm), book->tm = NULL, free(book), book = NULL, free(book_node),
                  book_node = NULL;
  free(paul->tm), paul->tm = NULL, free(paul), paul = NULL, free(paul_node),
                  paul_node = NULL;
  free(rodman->tm), rodman->tm = NULL, free(rodman), rodman = NULL,
                    free(rodman_node), rodman_node = NULL;
  free(jokic->tm), jokic->tm = NULL, free(jokic), jokic = NULL,
                   free(jokic_node), jokic_node = NULL;
  free(yang->tm), yang->tm = NULL, free(yang), yang = NULL, free(yang_node),
                  yang_node = NULL;
  free(sharq->tm), sharq->tm = NULL, free(sharq), sharq = NULL,
                   free(sharq_node), sharq_node = NULL;
  root_node = NULL;
}   */

/*
TestResult test_player_tree() {
  init_player_data();
  log_i("~~~~~~~~~~~~~~~~~print count: 0~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  insert_node(jordan_node);

  insert_node(jokic_node);

  log_i("~~~~~~~~~~~~~~~~~print count: 1~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  // delete_node(jordan_node);

  insert_node(yi_node);
  log_i("~~~~~~~~~~~~~~~~~print count: 2~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  insert_node(rodman_node);
  log_i("~~~~~~~~~~~~~~~~~print count: 3~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  insert_node(jimmy_node);
  log_i("~~~~~~~~~~~~~~~~~print count: 4~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  insert_node(book_node);
  log_i("~~~~~~~~~~~~~~~~~print count: 5~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  // delete_node(rodman_node);

  log_i("~~~~~~~~~~~~~~~~~print count: 6~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  // delete_node(yi_node);
  // delete_node(jimmy_node);
  // delete_node(yao_node);

  log_i("~~~~~~~~~~~~~~~~~print count: 7~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  insert_node(kobe_node);
  log_i("~~~~~~~~~~~~~~~~~print count: 8~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  insert_node(yao_node);
  // delete_node(kobe_node);
  // delete_node(yao_node);
  // delete_node(jordan_node);
  log_i("~~~~~~~~~~~~~~~~~print count: 9~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  // delete_node(yao_node);

  insert_node(dunken_node);
  log_i("~~~~~~~~~~~~~~~~~print count: 10~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  insert_node(paul_node);
  log_i("~~~~~~~~~~~~~~~~~print count: 11~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  insert_node(book_node);
  log_i("~~~~~~~~~~~~~~~~~print count: 12~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  insert_node(jordan_node);
  log_i("~~~~~~~~~~~~~~~~~print count: 13~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  insert_node(camelo_node);
  log_i("~~~~~~~~~~~~~~~~~print count: 14~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  // delete_node(book_node);
  // delete_node(book_node);
  // delete_node(book_node);
  // delete_node(book_node);
  // delete_node(book_node);
  // delete_node(book_node);
  // delete_node(book_node);
  // delete_node(book_node);
  // delete_node(book_node);
  // delete_node(book_node);
  insert_node(curry_node);
  insert_node(jimmy_node);
  log_i("~~~~~~~~~~~~~~~~~print count: 15~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);
  // delete_node(kobe_node);
  // delete_node(yao_node);
  // delete_node(yi_node);
  // delete_node(camelo_node);
  // delete_node(book_node);
  // delete_node(jimmy_node);
  // delete_node(dunken_node);
  // delete_node(jordan_node);
  // delete_node(jordan_node);
  log_i("~~~~~~~~~~~~~~~~~print count: 16~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  // delete_node(jordan_node);
  log_i("~~~~~~~~~~~~~~~~~print count: 17~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  // delete_node(jordan_node);
  // delete_node(jordan_node);
  log_i("~~~~~~~~~~~~~~~~~print count: 18~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  insert_node(kobe_node);
  log_i("~~~~~~~~~~~~~~~~~print count: 19~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  // delete_node(jordan_node);
  // delete_node(jordan_node);
  // delete_node(jordan_node);
  // delete_node(jordan_node);
  // delete_node(jordan_node);
  // delete_node(jordan_node);
  // delete_node(jordan_node);
  // delete_node(jordan_node);
  // delete_node(jordan_node);
  // delete_node(jordan_node);
  // delete_node(jordan_node);
  // delete_node(jordan_node);
  insert_node(book_node);
  insert_node(jokic_node);
  insert_node(jimmy_node);
  log_i("~~~~~~~~~~~~~~~~~print count: 20~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);
  // delete_node(jordan_node);
  // delete_node(jordan_node);
  insert_node(dunken_node);
  insert_node(sharq_node);
  log_i("~~~~~~~~~~~~~~~~~print count: 21~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);
  insert_node(yao_node);
  insert_node(yi_node);
  insert_node(yang_node);
  log_i("~~~~~~~~~~~~~~~~~print count: 22~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  // delete_node(paul_node);
  log_i("~~~~~~~~~~~~~~~~~print count: 23~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  free_nodes();

  log_i("~~~~~~~~~~~~~~~~~ end. ~~~~~~~~~~~~~~~~~~~~~~~");
  return TEST_PASSED;
}   */
