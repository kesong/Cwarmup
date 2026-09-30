#include "test_player.h"
#include "../include/log.h"
#include "../src/print_ADT.h"
#include "test_and_validation.h"

#include <stdlib.h>
#include <string.h>

extern TreeNode *root_node;
extern TreeNode *root_node_bak;

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

  kobe_node = (TreeNode *)malloc(sizeof(TreeNode));
  kobe = (PLAYER *)malloc(sizeof(PLAYER));
  kobe->tm = (TEAM *)malloc(sizeof(TEAM));
  kobe->pname = "Kobe", kobe->pnumber = 8, kobe->salary = 3500,
  kobe->tm->tname = "Lakers", kobe->tm->city = "LA",
  kobe_node->node_color = RED_NODE;
  kobe_node->tree_data = kobe, kobe_node->left = NULL, kobe_node->right = NULL;

  jordan_node = (TreeNode *)malloc(sizeof(TreeNode));
  jordan = (PLAYER *)malloc(sizeof(PLAYER));
  jordan->tm = (TEAM *)malloc(sizeof(TEAM));
  jordan->pname = "Jordan", jordan->pnumber = 23, jordan->salary = 3000,
  jordan->tm->tname = "Bulls", jordan->tm->city = "Chicago";
  jordan_node->tree_data = jordan, jordan_node->left = NULL,
  jordan_node->right = NULL, jordan_node->node_color = RED_NODE;

  yao_node = (TreeNode *)malloc(sizeof(TreeNode));
  yao = (PLAYER *)malloc(sizeof(PLAYER));
  yao->tm = (TEAM *)malloc(sizeof(TEAM));
  yao->pname = "Yao", yao->pnumber = 11, yao->salary = 2500,
  yao->tm->tname = "Rockets", yao->tm->city = "Hous",
  yao_node->node_color = RED_NODE;
  yao_node->tree_data = yao, yao_node->left = NULL, yao_node->right = NULL;

  yi_node = (TreeNode *)malloc(sizeof(TreeNode));
  yi = (PLAYER *)malloc(sizeof(PLAYER));
  yi->tm = (TEAM *)malloc(sizeof(TEAM));
  yi->pname = "Yi", yi->pnumber = 6, yi->salary = 500, yi->tm->tname = "Bucks",
  yi->tm->city = "Milv", yi_node->node_color = RED_NODE;
  yi_node->tree_data = yi, yi_node->left = NULL, yi_node->right = NULL;

  camelo_node = (TreeNode *)malloc(sizeof(TreeNode));
  camelo = (PLAYER *)malloc(sizeof(PLAYER));
  camelo->tm = (TEAM *)malloc(sizeof(TEAM));
  camelo->pname = "Camelo", camelo->pnumber = 15, camelo->salary = 2700,
  camelo->tm->tname = "Nick", camelo->tm->city = "NY";
  camelo_node->tree_data = camelo, camelo_node->left = NULL,
  camelo_node->right = NULL, camelo_node->node_color = RED_NODE;

  dunken_node = (TreeNode *)malloc(sizeof(TreeNode));
  dunken = (PLAYER *)malloc(sizeof(PLAYER));
  dunken->tm = (TEAM *)malloc(sizeof(TEAM));
  dunken->pname = "Dunken", dunken->pnumber = 21, dunken->salary = 3200,
  dunken->tm->tname = "Spurs", dunken->tm->city = "Santo";
  dunken_node->tree_data = dunken, dunken_node->left = NULL,
  dunken_node->right = NULL, dunken_node->node_color = RED_NODE;

  curry_node = (TreeNode *)malloc(sizeof(TreeNode));
  curry = (PLAYER *)malloc(sizeof(PLAYER));
  curry->tm = (TEAM *)malloc(sizeof(TEAM));
  curry->pname = "Curry", curry->pnumber = 30, curry->salary = 5000,
  curry->tm->tname = "War", curry->tm->city = "San";
  curry_node->tree_data = curry, curry_node->node_color = RED_NODE;
  curry_node->left = NULL, curry_node->right = NULL;

  jimmy_node = (TreeNode *)malloc(sizeof(TreeNode));
  jimmy = (PLAYER *)malloc(sizeof(PLAYER));
  jimmy->tm = (TEAM *)malloc(sizeof(TEAM));
  jimmy->pname = "Jimmy", jimmy->pnumber = 10, jimmy->salary = 5500,
  jimmy->tm->tname = "War", jimmy->tm->city = "San";
  jimmy_node->tree_data = jimmy, jimmy_node->left = NULL,
  jimmy_node->right = NULL, jimmy_node->node_color = RED_NODE;

  book_node = (TreeNode *)malloc(sizeof(TreeNode));
  book = (PLAYER *)malloc(sizeof(PLAYER));
  book->tm = (TEAM *)malloc(sizeof(TEAM));
  book->pname = "Book", book->pnumber = 0, book->salary = 3800,
  book->tm->tname = "Suns", book->tm->city = "Phix",
  book_node->node_color = RED_NODE;
  book_node->tree_data = book, book_node->left = NULL, book_node->right = NULL;

  paul_node = (TreeNode *)malloc(sizeof(TreeNode));
  paul = (PLAYER *)malloc(sizeof(PLAYER));
  paul->tm = (TEAM *)malloc(sizeof(TEAM));
  paul->pname = "Paul", paul->pnumber = 3, paul->salary = 4000,
  paul->tm->tname = "Suns", paul->tm->city = "Phix",
  paul_node->node_color = RED_NODE;
  paul_node->tree_data = paul, paul_node->left = NULL, paul_node->right = NULL;

  rodman_node = (TreeNode *)malloc(sizeof(TreeNode));
  rodman = (PLAYER *)malloc(sizeof(PLAYER));
  rodman->tm = (TEAM *)malloc(sizeof(TEAM));
  rodman->pname = "Rodman", rodman->pnumber = 91, rodman->salary = 1000,
  rodman->tm->tname = "Piston", rodman->tm->city = "Dix";
  rodman_node->tree_data = rodman, rodman_node->left = NULL,
  rodman_node->right = NULL, rodman_node->node_color = RED_NODE;

  jokic_node = (TreeNode *)malloc(sizeof(TreeNode));
  jokic = (PLAYER *)malloc(sizeof(PLAYER));
  jokic->tm = (TEAM *)malloc(sizeof(TEAM));
  jokic->pname = "Jokic", jokic->pnumber = 15, jokic->salary = 6000,
  jokic->tm->tname = "Nug", jokic->tm->city = "Den";
  jokic_node->tree_data = jokic, jokic_node->left = NULL,
  jokic_node->right = NULL, jokic_node->node_color = RED_NODE;

  yang_node = (TreeNode *)malloc(sizeof(TreeNode));
  yang = (PLAYER *)malloc(sizeof(PLAYER));
  yang->tm = (TEAM *)malloc(sizeof(TEAM));
  yang->pname = "Yang", yang->pnumber = 16, yang->salary = 800,
  yang->tm->tname = "Bla", yang->tm->city = "Por",
  yang_node->node_color = RED_NODE;
  yang_node->tree_data = yang, yang_node->left = NULL, yang_node->right = NULL;

  sharq_node = (TreeNode *)malloc(sizeof(TreeNode));
  sharq = (PLAYER *)malloc(sizeof(PLAYER));
  sharq->tm = (TEAM *)malloc(sizeof(TEAM));
  sharq->pname = "Sharq", sharq->pnumber = 34, sharq->salary = 3600,
  sharq->tm->tname = "Heat", sharq->tm->city = "Mia";
  sharq_node->tree_data = sharq, sharq_node->left = NULL,
  sharq_node->right = NULL, sharq_node->node_color = RED_NODE;

  sga_node = (TreeNode *)malloc(sizeof(TreeNode));
  sga = (PLAYER *)malloc(sizeof(PLAYER));
  sga->tm = (TEAM *)malloc(sizeof(TEAM));
  sga->pname = "Sga", sharq->pnumber = 2, sga->salary = 4500,
  sga->tm->tname = "Thunder", sharq->tm->city = "Okl";
  sga_node->tree_data = sga, sga_node->left = NULL, sga_node->right = NULL,
  sga_node->node_color = RED_NODE;

  edwards_node = (TreeNode *)malloc(sizeof(TreeNode));
  edwards = (PLAYER *)malloc(sizeof(PLAYER));
  edwards->tm = (TEAM *)malloc(sizeof(TEAM));
  edwards->pname = "Edwards", edwards->pnumber = 5, edwards->salary = 4000,
  edwards->tm->tname = "Wolf", edwards->tm->city = "Mine";
  edwards_node->tree_data = edwards, edwards_node->left = NULL,
  edwards_node->right = NULL, edwards_node->node_color = RED_NODE;

  klay_node = (TreeNode *)malloc(sizeof(TreeNode));
  klay = (PLAYER *)malloc(sizeof(PLAYER));
  klay->tm = (TEAM *)malloc(sizeof(TEAM));
  klay->pname = "Klay", klay->pnumber = 11, klay->salary = 2000,
  klay->tm->tname = "Maveric", klay->tm->city = "Dal";
  klay_node->tree_data = klay, klay_node->left = NULL, klay_node->right = NULL,
  klay_node->node_color = RED_NODE;

  hill_node = (TreeNode *)malloc(sizeof(TreeNode));
  hill = (PLAYER *)malloc(sizeof(PLAYER));
  hill->tm = (TEAM *)malloc(sizeof(TEAM));
  hill->pname = "Hill", hill->pnumber = 33, hill->salary = 1500,
  hill->tm->tname = "Suns", hill->tm->city = "Phx";
  hill_node->tree_data = hill, hill_node->left = NULL, hill_node->right = NULL,
  hill_node->node_color = RED_NODE;

  durant_node = (TreeNode *)malloc(sizeof(TreeNode));
  durant = (PLAYER *)malloc(sizeof(PLAYER));
  durant->tm = (TEAM *)malloc(sizeof(TEAM));
  durant->pname = "Durant", durant->pnumber = 35, durant->salary = 3500,
  durant->tm->tname = "Suns", durant->tm->city = "Phx";
  durant_node->tree_data = durant, durant_node->left = NULL,
  durant_node->right = NULL, durant_node->node_color = RED_NODE;

  wade_node = (TreeNode *)malloc(sizeof(TreeNode));
  wade = (PLAYER *)malloc(sizeof(PLAYER));
  wade->tm = (TEAM *)malloc(sizeof(TEAM));
  wade->pname = "Wade", wade->pnumber = 3, wade->salary = 3500,
  wade->tm->tname = "Heat", wade->tm->city = "Mia";
  wade_node->tree_data = wade, wade_node->left = NULL, wade_node->right = NULL,
  wade_node->node_color = RED_NODE;

  lebron_node = (TreeNode *)malloc(sizeof(TreeNode));
  lebron = (PLAYER *)malloc(sizeof(PLAYER));
  lebron->tm = (TEAM *)malloc(sizeof(TEAM));
  lebron->pname = "Lebron", lebron->pnumber = 23, lebron->salary = 3500,
  lebron->tm->tname = "Lakers", lebron->tm->city = "Los";
  lebron_node->tree_data = lebron, lebron_node->left = NULL,
  lebron_node->right = NULL, lebron_node->node_color = RED_NODE;

  iverson_node = (TreeNode *)malloc(sizeof(TreeNode));
  iverson = (PLAYER *)malloc(sizeof(PLAYER));
  iverson->tm = (TEAM *)malloc(sizeof(TEAM));
  iverson->pname = "Iverson", iverson->pnumber = 3, iverson->salary = 2500,
  iverson->tm->tname = "Sixers", lebron->tm->city = "Phi";
  iverson_node->tree_data = iverson, iverson_node->left = NULL,
  iverson_node->right = NULL, iverson_node->node_color = RED_NODE;

  macgrady_node = (TreeNode *)malloc(sizeof(TreeNode));
  macgrady = (PLAYER *)malloc(sizeof(PLAYER));
  macgrady->tm = (TEAM *)malloc(sizeof(TEAM));
  macgrady->pname = "Macgrady", macgrady->pnumber = 1, macgrady->salary = 2500,
  macgrady->tm->tname = "Magic", macgrady->tm->city = "Olan";
  macgrady_node->tree_data = macgrady, macgrady_node->left = NULL,
  macgrady_node->right = NULL, macgrady_node->node_color = RED_NODE;

  kawhi_node = (TreeNode *)malloc(sizeof(TreeNode));
  kawhi = (PLAYER *)malloc(sizeof(PLAYER));
  kawhi->tm = (TEAM *)malloc(sizeof(TEAM));
  kawhi->pname = "Kawhi", kawhi->pnumber = 1, kawhi->salary = 3900,
  kawhi->tm->tname = "Clippers", kawhi->tm->city = "LA";
  kawhi_node->tree_data = kawhi, kawhi_node->left = NULL,
  kawhi_node->right = NULL, kawhi_node->node_color = RED_NODE;

  doncic_node = (TreeNode *)malloc(sizeof(TreeNode));
  doncic = (PLAYER *)malloc(sizeof(PLAYER));
  doncic->tm = (TEAM *)malloc(sizeof(TEAM));
  doncic->pname = "Doncic", doncic->pnumber = 77, doncic->salary = 3500,
  doncic->tm->tname = "Lakers", doncic->tm->city = "LA";
  doncic_node->tree_data = doncic, doncic_node->left = NULL,
  doncic_node->right = NULL, doncic_node->node_color = RED_NODE;

  carter_node = (TreeNode *)malloc(sizeof(TreeNode));
  carter = (PLAYER *)malloc(sizeof(PLAYER));
  carter->tm = (TEAM *)malloc(sizeof(TEAM));
  carter->pname = "Carter", carter->pnumber = 15, carter->salary = 2100,
  carter->tm->tname = "Rapters", carter->tm->city = "Tor";
  carter_node->tree_data = carter, carter_node->left = NULL,
  carter_node->right = NULL, carter_node->node_color = RED_NODE;

  chris_node = (TreeNode *)malloc(sizeof(TreeNode));
  chris = (PLAYER *)malloc(sizeof(PLAYER));
  chris->tm = (TEAM *)malloc(sizeof(TEAM));
  chris->pname = "Chris", chris->pnumber = 4, chris->salary = 1800,
  chris->tm->tname = "Kings", chris->tm->city = "Saq";
  chris_node->tree_data = chris, chris_node->left = NULL,
  chris_node->right = NULL, chris_node->node_color = RED_NODE;

  // 测试27个球员，每个球员编一个整数号码，在使用第三方提供的在线可视化创建红黑树时候比较方便验证
  //(book, 0), (camelo, 50), (curry, 100), (doncic, 150), (dunken, 200),
  //(durant, 250), (edwards, 300), (hill, 350), (iverson, 400) (jimmy, 450),
  //(jokic, 500), (jordan, 550), (kawhi, 600), (klay, 650), (kobe, 700),
  //(lebron, 750), (macgrady, 800), (paul, 850), (rodman, 900), (sga, 950),
  //(sharq, 1000), (wade, 1050), (yang, 1100), (yao, 1150), (yi, 1200),
  //(carter, 60), (chris, 75)

  /* player node initialized complete.*/
}

// 二叉树会对节点进行比较，所以可以根据插入的球员姓名构建二叉树，节点比较就变成了比较姓名的字符串
// 也可以对在构建球员树的时候对球员号码进行比较来构建二叉树，节点比较就是整数的比较
// 不管那种插入方式，构建树的时候都要指明构建树的类型，根据binary_search_tree的头文件里面的NodeEnum进行指定，插入的节点的时候也要指明是按照姓名来插入还是按照
// 球员号码来插入。
TreeNode *build_player_tree_by_name() {
  root_node = build_tree();
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
}

TreeNode *build_player_tree_by_number() {
  root_node = build_tree();
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
  return root_node;
}

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
}

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
}
