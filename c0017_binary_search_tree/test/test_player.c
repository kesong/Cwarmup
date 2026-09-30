#include "test_player.h"
#include "../include/log.h"
#include "../src/print_ADT.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

extern TreeNode *root_node;

int search_tree_node(TreeNode *start_node, void *search_node,
                     NodeEnum tree_type, TreeNode *result_node,
                     TreeNode *result_parent_node) {
  TreeNode *current_node = start_node;
  if (start_node == root_node && root_node == NULL) {
    log_e("Tree is empty, please check.");
    return -1;
  }
  if (start_node == NULL || start_node->tree_data == NULL) {
    log_e("Search tree complete, not found.");
    return -1;
  }
  TreeNode *wrap_node = (TreeNode *)malloc(sizeof(TreeNode));
  memset(wrap_node, 0, sizeof(TreeNode));
  if (wrap_node == NULL) {
    log_e("Failed to allocate memory for wrap_node");
    return -1;
  }

  PLAYER *current_player = (PLAYER *)current_node->tree_data;

  wrap_node->tree_data = (PLAYER *)search_node;
  PLAYER *wrap_node_player = (PLAYER *)wrap_node->tree_data;
  wrap_node->left = NULL;
  wrap_node->right = NULL;
  if (tree_type == NODE_CHAR) {
    if (strcmp(current_player->pname, wrap_node_player->pname) == 0) {
      result_node->tree_data = current_node;
      return 0;
    }
    // use the following command:
    // "p (char*)((PLAYER*)(*result_parent_node)->tree_data)->pname" to check
    // the result_parent_node value during gdb debugging.
    result_parent_node->tree_data = current_node;
  }
  if (tree_type == NODE_INT) {
    if (current_player->pnumber == wrap_node_player->pnumber) {
      result_node = current_node;
      return 0;
    }
    result_parent_node->tree_data = current_node;
  }
  // 由于二叉搜索树的组织方式，比节点大向右，比节点小向左，可以实现类似二分查找，更快速的查询节点。
  if (tree_type == NODE_CHAR) {
    if (strcmp(wrap_node_player->pname, current_player->pname) > 0) {
      search_tree_node(current_node->right, search_node, tree_type, result_node,
                       result_parent_node);
    } else {
      search_tree_node(current_node->left, search_node, tree_type, result_node,
                       result_parent_node);
    }
  }
  if (tree_type == NODE_INT) {
    if (current_player->pnumber == wrap_node_player->pnumber) {
      search_tree_node(current_node->right, search_node, tree_type, result_node,
                       result_parent_node);
    } else {
      search_tree_node(current_node->left, search_node, tree_type, result_node,
                       result_parent_node);
    }
  }
}

// start_node为要删除的节点的左节点
TreeNode *get_most_right_node_from_left_tree(TreeNode *start_node) {
  if (start_node == NULL) {
    return NULL;
  }
  if (start_node->right == NULL) {
    return start_node;
  }
  get_most_right_node_from_left_tree(start_node->right);
}

// start_node为要删除的节点的右节点
TreeNode *get_most_left_node_from_right_tree(TreeNode *start_node) {
  if (start_node == NULL) {
    return NULL;
  }
  if (start_node->left == NULL) {
    return start_node;
  }
  get_most_left_node_from_right_tree(start_node->left);
}

// 删除目标节点，几种情况
// 1. 被删除节点没有子节点（子树），直接删除；
// 2. 被删除的节点只有一个左节点，左节点取代被删除节点；
// 3. 被删除的节点只有一个右节点，右节点取代被删除节点；
// 4.
// 被删除的节点有左右两个子树，用左子树的最右边的节点（没有子节点），或者右子树的最左边的节点替代被删除节点，这两个节点刚好是中序遍历二叉树时，
// 分别排列在被删除节点前面和后面的节点，所以用这两个节点替代被删除节点也不会打破二叉搜索树的平衡；
// 5. 取代被删除的节点要先与树断开连接关系；
// 6.
// 根据二叉搜索树的中间节点大于左边节点，小于右边节点的特性，中序遍历二叉搜索树得到的正好是从小到大排列的一组数据，上一步就是用排列在被删除节点前后的两个节点替代它；
void delete_tree_node(TreeNode *start_node, void *del_node,
                      NodeEnum node_type) {
  if (start_node == NULL || start_node->tree_data == NULL) {
    log_e("Cannot delete from empty tree");
    return;
  }
  PLAYER *player = (PLAYER *)start_node->tree_data;
  PLAYER *targ_player = (PLAYER *)del_node;

  int result_value = -1;
  TreeNode *search_result = (TreeNode *)malloc(sizeof(TreeNode));
  memset(search_result, 0, sizeof(TreeNode));
  TreeNode *search_result_parent = (TreeNode *)malloc(sizeof(TreeNode));
  memset(search_result_parent, 0, sizeof(TreeNode));
  result_value = search_tree_node(root_node, del_node, node_type, search_result,
                                  search_result_parent);
  bool node_is_left = false;
  bool node_is_right = false;
  TreeNode *replace_node = NULL;
  TreeNode *search_result_node =
      search_result != NULL ? (TreeNode *)search_result->tree_data : NULL;
  TreeNode *search_result_parent_node =
      search_result_parent != NULL ? (TreeNode *)search_result_parent->tree_data
                                   : NULL;
  if (search_result_node == NULL) {
    log_e("Node not found.");
    return;
  }
  char *search_result_node_player =
      (char *)((PLAYER *)search_result_node->tree_data)->pname;
  char *search_result_parent_left_player = NULL;
  char *search_result_parent_right_player = NULL;
  if (search_result_parent_node != NULL) {
    if (search_result_parent_node->left != NULL) {
      search_result_parent_left_player =
          (char *)((PLAYER *)search_result_parent_node->left->tree_data)->pname;
      if (strcmp(search_result_node_player, search_result_parent_left_player) ==
          0) {
        node_is_left = true;
      }
    }
    if (search_result_parent_node->right != NULL) {
      search_result_parent_right_player =
          (char *)((PLAYER *)search_result_parent_node->right->tree_data)
              ->pname;
      if (strcmp(search_result_node_player,
                 search_result_parent_right_player) == 0) {
        node_is_right = true;
      }
    }
  }
  if (search_result_node == NULL || result_value != 0) {
    log_e("Node is going to delete is not in the tree.");
    return;
  } else if (search_result_node->left == NULL &&
             search_result_node->right == NULL) {
    if (search_result_node == root_node) {
      free(root_node);
      root_node = NULL;
      return;
    }
    search_result_node->tree_data = NULL;
    search_result_node->left = NULL;
    search_result_node->right = NULL;
    free(search_result_node);
    search_result_node = NULL;
    search_result->tree_data = NULL;
    search_result->left = NULL;
    search_result->right = NULL;
    free(search_result);
    search_result = NULL;
    search_result_parent->tree_data = NULL;
    search_result_parent->left = NULL;
    search_result_parent->right = NULL;
    free(search_result_parent);
    search_result_parent = NULL;
    if (node_is_left) {
      search_result_parent_node->left = NULL;
    } else if (node_is_right) {
      search_result_parent_node->right = NULL;
    }
    return;
  } else if (search_result_node->left != NULL &&
             search_result_node->right == NULL) {
    if (search_result_node == root_node) {
      root_node = search_result_node->left;
      free(search_result);
      search_result = NULL;
      free(search_result_parent);
      search_result_parent = NULL;
      search_result_node->tree_data = NULL;
      search_result_node->left = NULL;
      search_result_node->right = NULL;
      free(search_result_node);
      search_result_node = NULL;
      return;
    }
    if (node_is_left) {
      search_result_parent_node->left = search_result_node->left;
      free(search_result);
      search_result = NULL;
      free(search_result_parent);
      search_result_parent = NULL;
      search_result_node->tree_data = NULL;
      search_result_node->left = NULL;
      search_result_node->right = NULL;
      free(search_result_node);
      search_result_node = NULL;
      return;
    }
    if (node_is_right) {
      search_result_parent_node->right = search_result_node->left;
      free(search_result);
      search_result = NULL;
      free(search_result_parent);
      search_result_parent = NULL;
      search_result_node->tree_data = NULL;
      search_result_node->left = NULL;
      search_result_node->right = NULL;
      free(search_result_node);
      search_result_node = NULL;
      return;
    }
  } else if (search_result_node->left == NULL &&
             search_result_node->right != NULL) {
    if (search_result_node == root_node) {
      root_node = search_result_node->right;
      free(search_result);
      search_result = NULL;
      free(search_result_parent);
      search_result_parent = NULL;
      search_result_node->tree_data = NULL;
      search_result_node->left = NULL;
      search_result_node->right = NULL;
      free(search_result_node);
      search_result_node = NULL;
      return;
    }
    if (node_is_left) {
      search_result_parent_node->left = search_result_node->right;
      free(search_result);
      search_result = NULL;
      free(search_result_parent);
      search_result_parent = NULL;
      search_result_node->tree_data = NULL;
      search_result_node->left = NULL;
      search_result_node->right = NULL;
      free(search_result_node);
      search_result_node = NULL;
      return;
    }
    if (node_is_right) {
      search_result_parent_node->right = search_result_node->right;
      free(search_result);
      search_result = NULL;
      free(search_result_parent);
      search_result_parent = NULL;
      search_result_node->tree_data = NULL;
      search_result_node->left = NULL;
      search_result_node->right = NULL;
      free(search_result_node);
      search_result_node = NULL;
      return;
    }
  } else if (search_result_node->left != NULL &&
             search_result_node->right != NULL) {
    TreeNode *tmp_node = NULL;
    replace_node = get_most_right_node_from_left_tree(search_result_node->left);
    if (search_result_node == root_node) {
      replace_node->right = root_node->right;
      root_node = replace_node;
      return;
    }
    if (node_is_left) {
      search_result_parent_node->left = replace_node;
      replace_node->right = search_result_node->right;
      free(search_result);
      search_result = NULL;
      free(search_result_parent);
      search_result_parent = NULL;
      search_result_node->tree_data = NULL;
      search_result_node->left = NULL;
      search_result_node->right = NULL;
      free(search_result_node);
      search_result_node = NULL;
      return;
    }
    if (node_is_right) {
      search_result_parent_node->right = replace_node;
      replace_node->right = search_result_node->right;
      free(search_result);
      search_result = NULL;
      free(search_result_parent);
      search_result_parent = NULL;
      search_result_node->tree_data = NULL;
      search_result_node->left = NULL;
      search_result_node->right = NULL;
      free(search_result_node);
      search_result_node = NULL;
      return;
    }
  }
}

// 结构体指针作为局部变量，如果只是临时用来接收另一个结构体指针的地址，以及传递地址给其他结构体指针，无需使用malloc分配空间，指向NULL完成初始化就可以。
// 如果需要接收其他结构体传递过来的数据，需要使用malloc分配空间，否则无法接收其他结构体指针中的数据，没有为结构体指针分配空间，那么结构体成员也就无法接收数据
// 使用完要将这个结构体指针的局部变量释放掉，能在本函数内直接释放的就在函数内释放，函数内无法释放的就在调用函数完成后释放。
// 这里只是用来接收各个节点的地址，不能用malloc分配空间，比如某个接收TreeNode地址的指针使用malloc分配空间后，接收的就只是节点地址了，无法保持树的连接关系

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

void init_player_data() {
  /* initial the player node.*/

  // kobe_node = (NODE *)malloc(sizeof(NODE));
  kobe = (PLAYER *)malloc(sizeof(PLAYER));
  kobe->tm = (TEAM *)malloc(sizeof(TEAM));
  kobe->pname = "Kobe", kobe->pnumber = 8, kobe->salary = 3500,
  kobe->tm->tname = "Lakers", kobe->tm->city = "LA";
  // kobe_node->ptr_data = kobe, kobe_node->left = NULL, kobe_node->right =
  // NULL; kobe_node->node_t = PLAYER_NODE;

  // jordan_node = (NODE *)malloc(sizeof(NODE));
  jordan = (PLAYER *)malloc(sizeof(PLAYER));
  jordan->tm = (TEAM *)malloc(sizeof(TEAM));
  jordan->pname = "Jordan", jordan->pnumber = 23, jordan->salary = 3000,
  jordan->tm->tname = "Bulls", jordan->tm->city = "Chicago";
  // jordan_node->ptr_data = jordan, jordan_node->left = NULL,
  // jordan_node->right = NULL;
  // jordan_node->node_t = PLAYER_NODE;

  // yao_node = (NODE *)malloc(sizeof(NODE));
  yao = (PLAYER *)malloc(sizeof(PLAYER));
  yao->tm = (TEAM *)malloc(sizeof(TEAM));
  yao->pname = "Yao", yao->pnumber = 11, yao->salary = 2500,
  yao->tm->tname = "Rockets", yao->tm->city = "Hous";
  // yao_node->ptr_data = yao, yao_node->left = NULL, yao_node->right = NULL;
  // yao_node->node_t = PLAYER_NODE;

  // yi_node = (NODE *)malloc(sizeof(NODE));
  yi = (PLAYER *)malloc(sizeof(PLAYER));
  yi->tm = (TEAM *)malloc(sizeof(TEAM));
  yi->pname = "Yi", yi->pnumber = 6, yi->salary = 500, yi->tm->tname = "Bucks",
  yi->tm->city = "Milv";
  // yi_node->ptr_data = yi, yi_node->left = NULL, yi_node->right = NULL;
  // yi_node->node_t = PLAYER_NODE;

  // camelo_node = (NODE *)malloc(sizeof(NODE));
  camelo = (PLAYER *)malloc(sizeof(PLAYER));
  camelo->tm = (TEAM *)malloc(sizeof(TEAM));
  camelo->pname = "Camelo", camelo->pnumber = 15, camelo->salary = 2700,
  camelo->tm->tname = "Nick", camelo->tm->city = "NY";
  // camelo_node->ptr_data = camelo, camelo_node->left = NULL,
  // camelo_node->right = NULL; camelo_node->node_t = PLAYER_NODE;

  // dunken_node = (NODE *)malloc(sizeof(NODE));
  dunken = (PLAYER *)malloc(sizeof(PLAYER));
  dunken->tm = (TEAM *)malloc(sizeof(TEAM));
  dunken->pname = "Tim", dunken->pnumber = 21, dunken->salary = 3200,
  dunken->tm->tname = "Spurs", dunken->tm->city = "Santo";
  // dunken_node->ptr_data = dunken, dunken_node->left =
  // NULL,dunken_node->right = NULL; dunken_node->node_t = PLAYER_NODE;

  // curry_node = (NODE *)malloc(sizeof(NODE));
  curry = (PLAYER *)malloc(sizeof(PLAYER));
  curry->tm = (TEAM *)malloc(sizeof(TEAM));
  curry->pname = "Curry", curry->pnumber = 30, curry->salary = 5000,
  curry->tm->tname = "War", curry->tm->city = "San";
  // curry_node->ptr_data = curry;
  //  curry_node->left = NULL, curry_node->right = NULL;
  //  curry_node->node_t = PLAYER_NODE;

  // jimmy_node = (NODE *)malloc(sizeof(NODE));
  jimmy = (PLAYER *)malloc(sizeof(PLAYER));
  jimmy->tm = (TEAM *)malloc(sizeof(TEAM));
  jimmy->pname = "Jimmy", jimmy->pnumber = 10, jimmy->salary = 5500,
  jimmy->tm->tname = "War", jimmy->tm->city = "San";
  // jimmy_node->ptr_data = jimmy, jimmy_node->left = NULL, jimmy_node->right
  // = NULL; jimmy_node->node_t = PLAYER_NODE;

  // book_node = (NODE *)malloc(sizeof(NODE));
  book = (PLAYER *)malloc(sizeof(PLAYER));
  book->tm = (TEAM *)malloc(sizeof(TEAM));
  book->pname = "Book", book->pnumber = 0, book->salary = 3800,
  book->tm->tname = "Suns", book->tm->city = "Phix";
  // book_node->ptr_data = book, book_node->left = NULL, book_node->right =
  // NULL; book_node->node_t = PLAYER_NODE;

  // paul_node = (NODE *)malloc(sizeof(NODE));
  paul = (PLAYER *)malloc(sizeof(PLAYER));
  paul->tm = (TEAM *)malloc(sizeof(TEAM));
  paul->pname = "Paul", paul->pnumber = 3, paul->salary = 4000,
  paul->tm->tname = "Suns", paul->tm->city = "Phix";
  // paul_node->ptr_data = paul, paul_node->left = NULL, paul_node->right =
  // NULL; paul_node->node_t = PLAYER_NODE;

  // rodman_node = (NODE *)malloc(sizeof(NODE));
  rodman = (PLAYER *)malloc(sizeof(PLAYER));
  rodman->tm = (TEAM *)malloc(sizeof(TEAM));
  rodman->pname = "Rodman", rodman->pnumber = 91, rodman->salary = 1000,
  rodman->tm->tname = "Piston", rodman->tm->city = "Dix";
  // rodman_node->ptr_data = rodman, rodman_node->left = NULL,
  // rodman_node->right = NULL; rodman_node->node_t = PLAYER_NODE;

  // jokic_node = (NODE *)malloc(sizeof(NODE));
  jokic = (PLAYER *)malloc(sizeof(PLAYER));
  jokic->tm = (TEAM *)malloc(sizeof(TEAM));
  jokic->pname = "Jokic", jokic->pnumber = 15, jokic->salary = 6000,
  jokic->tm->tname = "Nug", jokic->tm->city = "Den";
  // jokic_node->ptr_data = jokic, jokic_node->left = NULL, jokic_node->right
  // = NULL; jokic_node->node_t = PLAYER_NODE;

  yang = (PLAYER *)malloc(sizeof(PLAYER));
  yang->tm = (TEAM *)malloc(sizeof(TEAM));
  yang->pname = "Yang", yang->pnumber = 16, yang->salary = 800,
  yang->tm->tname = "Bla", yang->tm->city = "Por";

  sharq = (PLAYER *)malloc(sizeof(PLAYER));
  sharq->tm = (TEAM *)malloc(sizeof(TEAM));
  sharq->pname = "Sharq", sharq->pnumber = 34, yang->salary = 3600,
  sharq->tm->tname = "Heat", sharq->tm->city = "Mia";
  /* player node initialized complete.*/
}

// 二叉树会对节点进行比较，所以可以根据插入的球员姓名构建二叉树，节点比较就变成了比较姓名的字符串
// 也可以对在构建球员树的时候对球员号码进行比较来构建二叉树，节点比较就是整数的比较
// 不管那种插入方式，构建树的时候都要指明构建树的类型，根据binary_search_tree的头文件里面的NodeEnum进行指定，插入的节点的时候也要指明是按照姓名来插入还是按照
// 球员号码来插入。
TreeNode *build_player_tree_by_name() {
  NodeEnum node_type = NODE_CHAR;
  root_node = build_tree(node_type);
  init_player_data();
  insert_tree_node(root_node, jordan, node_type);
  insert_tree_node(root_node, jokic, node_type);
  insert_tree_node(root_node, yi, node_type);
  insert_tree_node(root_node, rodman, node_type);
  insert_tree_node(root_node, jimmy, node_type);
  insert_tree_node(root_node, book, node_type);
  insert_tree_node(root_node, dunken, node_type);
  insert_tree_node(root_node, camelo, node_type);
  insert_tree_node(root_node, paul, node_type);
  insert_tree_node(root_node, curry, node_type);
  insert_tree_node(root_node, yao, node_type);
  insert_tree_node(root_node, kobe, node_type);
  return root_node;
}

TreeNode *build_player_tree_by_number() {
  NodeEnum node_type = NODE_INT;
  root_node = build_tree(node_type);
  init_player_data();
  insert_tree_node(root_node, jordan, node_type);
  insert_tree_node(root_node, jokic, node_type);
  insert_tree_node(root_node, yi, node_type);
  insert_tree_node(root_node, rodman, node_type);
  insert_tree_node(root_node, jimmy, node_type);
  insert_tree_node(root_node, book, node_type);
  insert_tree_node(root_node, dunken, node_type);
  insert_tree_node(root_node, camelo, node_type);
  insert_tree_node(root_node, paul, node_type);
  insert_tree_node(root_node, curry, node_type);
  insert_tree_node(root_node, yao, node_type);
  insert_tree_node(root_node, kobe, node_type);
  return root_node;
}

void test_preorder_traversal_without_recurse() {
  TreeNode *test_start_node = build_player_tree_by_name();
  log_i("(VLR)preorder traversal without recurse result is (first method): \n");
  print_tree_in_specified_order(test_start_node,
                                &preorder_traversal_without_recurse);
}

void test_preorder_traversal_without_recurse_2() {
  TreeNode *test_start_node = build_player_tree_by_name();
  log_i("(VLR)preorder traversal without recurse result is (second method): "
        "\n");
  print_tree_in_specified_order(test_start_node,
                                &preorder_traversal_without_recurse_2);
}

void test_inorder_traversal() {
  TreeNode *test_start_node = build_player_tree_by_name();
  log_i("(LVR)inorder traversal result is: \n");
  print_tree_in_specified_order(test_start_node, &inorder_traversal);
}

void test_inorder_traversal_without_recurse() {
  TreeNode *test_start_node = build_player_tree_by_name();
  log_i("(LVR)inorder traversal without recurse result is: \n");
  print_tree_in_specified_order(test_start_node,
                                &inorder_traversal_without_recurse);
}

void test_postorder_traversal() {
  TreeNode *test_start_node = build_player_tree_by_name();
  log_i("(LRV)postorder traversal result is: \n");
  print_tree_in_specified_order(test_start_node, &postorder_traversal);
}

void test_postorder_traversal_without_recurse() {
  TreeNode *test_start_node = build_player_tree_by_name();
  log_i("(LRV)postorder traversal without recurse result is: \n");
  print_tree_in_specified_order(test_start_node,
                                &postorder_traversal_without_recurse);
}

void test_postorder_traversal_without_recurse_2() {
  TreeNode *test_start_node = build_player_tree_by_name();
  log_i("(LRV)postorder traversal without recurse result is: \n");
  print_tree_in_specified_order(test_start_node,
                                &postorder_traversal_without_recurse_2);
}

void test_mixedorder_traversal_without_recurse() {
  TreeNode *test_start_node = build_player_tree_by_name();
  log_i("(LRV)mixedorder traversal without recurse result is: \n");
  print_tree_in_specified_order(test_start_node,
                                &mixedorder_traversal_without_recurse);
}

void test_level_traversal() {
  TreeNode *test_start_node = build_player_tree_by_name();
  log_i("level traversal result is: \n");
  print_tree_in_specified_order(test_start_node, &level_traversal);
}

void test_player_tree() {
  init_player_data();
  log_i("~~~~~~~~~~~~~~~~~print count: 0~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  insert_tree_node(root_node, jordan, NODE_CHAR);

  insert_tree_node(root_node, jokic, NODE_CHAR);

  log_i("~~~~~~~~~~~~~~~~~print count: 1~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  delete_tree_node(root_node, jordan, NODE_CHAR);

  insert_tree_node(root_node, yi, NODE_CHAR);
  log_i("~~~~~~~~~~~~~~~~~print count: 2~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  insert_tree_node(root_node, rodman, NODE_CHAR);
  log_i("~~~~~~~~~~~~~~~~~print count: 3~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  insert_tree_node(root_node, jimmy, NODE_CHAR);
  log_i("~~~~~~~~~~~~~~~~~print count: 4~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  insert_tree_node(root_node, book, NODE_CHAR);
  log_i("~~~~~~~~~~~~~~~~~print count: 5~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  delete_tree_node(root_node, rodman, NODE_CHAR);

  log_i("~~~~~~~~~~~~~~~~~print count: 6~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  delete_tree_node(root_node, yi, NODE_CHAR);
  delete_tree_node(root_node, jimmy, NODE_CHAR);
  delete_tree_node(root_node, yao, NODE_CHAR);

  log_i("~~~~~~~~~~~~~~~~~print count: 7~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  insert_tree_node(root_node, kobe, NODE_CHAR);
  log_i("~~~~~~~~~~~~~~~~~print count: 8~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  insert_tree_node(root_node, yao, NODE_CHAR);
  delete_tree_node(root_node, kobe, NODE_CHAR);
  delete_tree_node(root_node, yao, NODE_CHAR);
  delete_tree_node(root_node, jordan, NODE_CHAR);
  log_i("~~~~~~~~~~~~~~~~~print count: 9~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  delete_tree_node(root_node, yao, NODE_CHAR);

  insert_tree_node(root_node, dunken, NODE_CHAR);
  log_i("~~~~~~~~~~~~~~~~~print count: 10~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  insert_tree_node(root_node, paul, NODE_CHAR);
  log_i("~~~~~~~~~~~~~~~~~print count: 11~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  insert_tree_node(root_node, book, NODE_CHAR);
  log_i("~~~~~~~~~~~~~~~~~print count: 12~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  insert_tree_node(root_node, jordan, NODE_CHAR);
  log_i("~~~~~~~~~~~~~~~~~print count: 13~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  insert_tree_node(root_node, camelo, NODE_CHAR);
  log_i("~~~~~~~~~~~~~~~~~print count: 14~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  delete_tree_node(root_node, book, NODE_CHAR);
  delete_tree_node(root_node, book, NODE_CHAR);
  delete_tree_node(root_node, book, NODE_CHAR);
  delete_tree_node(root_node, book, NODE_CHAR);
  delete_tree_node(root_node, book, NODE_CHAR);
  delete_tree_node(root_node, book, NODE_CHAR);
  delete_tree_node(root_node, book, NODE_CHAR);
  delete_tree_node(root_node, book, NODE_CHAR);
  delete_tree_node(root_node, book, NODE_CHAR);
  delete_tree_node(root_node, book, NODE_CHAR);
  insert_tree_node(root_node, curry, NODE_CHAR);
  insert_tree_node(root_node, jimmy, NODE_CHAR);
  log_i("~~~~~~~~~~~~~~~~~print count: 15~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);
  delete_tree_node(root_node, kobe, NODE_CHAR);
  delete_tree_node(root_node, yao, NODE_CHAR);
  delete_tree_node(root_node, yi, NODE_CHAR);
  delete_tree_node(root_node, camelo, NODE_CHAR);
  delete_tree_node(root_node, book, NODE_CHAR);
  delete_tree_node(root_node, jimmy, NODE_CHAR);
  delete_tree_node(root_node, dunken, NODE_CHAR);
  delete_tree_node(root_node, jordan, NODE_CHAR);
  delete_tree_node(root_node, jordan, NODE_CHAR);
  log_i("~~~~~~~~~~~~~~~~~print count: 16~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  delete_tree_node(root_node, jordan, NODE_CHAR);
  log_i("~~~~~~~~~~~~~~~~~print count: 17~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  delete_tree_node(root_node, jordan, NODE_CHAR);
  delete_tree_node(root_node, jordan, NODE_CHAR);
  log_i("~~~~~~~~~~~~~~~~~print count: 18~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  insert_tree_node(root_node, kobe, NODE_CHAR);
  log_i("~~~~~~~~~~~~~~~~~print count: 19~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  delete_tree_node(root_node, jordan, NODE_CHAR);
  delete_tree_node(root_node, jordan, NODE_CHAR);
  delete_tree_node(root_node, jordan, NODE_CHAR);
  delete_tree_node(root_node, jordan, NODE_CHAR);
  delete_tree_node(root_node, jordan, NODE_CHAR);
  delete_tree_node(root_node, jordan, NODE_CHAR);
  delete_tree_node(root_node, jordan, NODE_CHAR);
  delete_tree_node(root_node, jordan, NODE_CHAR);
  delete_tree_node(root_node, jordan, NODE_CHAR);
  delete_tree_node(root_node, jordan, NODE_CHAR);
  delete_tree_node(root_node, jordan, NODE_CHAR);
  delete_tree_node(root_node, jordan, NODE_CHAR);
  insert_tree_node(root_node, book, NODE_CHAR);
  insert_tree_node(root_node, jokic, NODE_CHAR);
  insert_tree_node(root_node, jimmy, NODE_CHAR);
  log_i("~~~~~~~~~~~~~~~~~print count: 20~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);
  delete_tree_node(root_node, jordan, NODE_CHAR);
  delete_tree_node(root_node, jordan, NODE_CHAR);
  insert_tree_node(root_node, dunken, NODE_CHAR);
  insert_tree_node(root_node, sharq, NODE_CHAR);
  log_i("~~~~~~~~~~~~~~~~~print count: 21~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);
  insert_tree_node(root_node, yao, NODE_CHAR);
  insert_tree_node(root_node, yi, NODE_CHAR);
  insert_tree_node(root_node, yang, NODE_CHAR);
  log_i("~~~~~~~~~~~~~~~~~print count: 22~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  delete_tree_node(root_node, paul, NODE_CHAR);
  log_i("~~~~~~~~~~~~~~~~~print count: 23~~~~~~~~~~~~~~~~~~~~~~~");
  print_tree(root_node);

  free(kobe), free(jordan), free(yao), free(yi), free(camelo), free(dunken);
  free(curry), free(jimmy), free(book), free(paul), free(rodman), free(jokic),
      free(yang), free(sharq);

  free(root_node);
  log_i("~~~~~~~~~~~~~~~~~ end. ~~~~~~~~~~~~~~~~~~~~~~~");
}
