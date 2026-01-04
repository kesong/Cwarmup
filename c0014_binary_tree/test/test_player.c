#include "test_player.h"
#include "log.h"
#include "print_ADT.h"

extern TreeNode *root_node;

/*
TreeNode *search_tree_node(TreeNode *start_node, TreeNode *search_node,
                           TreeNode *parent_node) {
  if (start_node == NULL) {
    return NULL;
  }
  bool return_left_flag = 0;
  bool return _right_flag = 0;
  // 这里要作修改，数据从NODE更改成TreeNode了, 数据多了一道封装，
  // TreeNode->tree_data->ptr_data = PLAYER;
  // 如果是NODE的话语，就是NODE->ptr_data = PLAYER；
  PLAYER *start_player = (PLAYER *)(start_node->ptr_data);
  PLAYER *search_player = (PLAYER *)(search_node->ptr_data);
  PLAYER *parent_left_player = (PLAYER *)(start_node->left->ptr_data);
  PLAYER *parent_right_player = (PLAYER *)(start_node->right->ptr_data);
  if (!strcmp(parent_left_player->pname, search_player->pname)) {
    parent_node = start_node;
    return_left_flag = 1;
    return start_node->left;
  } else if (!strcmp(parent_left_player->pname, search_player->pname)) {
    parent_node = start_node;
    return_right_flag = 1;
    return start_node->right;
  }
  if (return_left_flag == 1) {
    return start_node->left;
  }
  if (return_right_flag == 1) {
    return start_node->right;
  }
  search_leaf(start_node->left, search_node);
  search_leaf(start_node->right, search_node);
}

// 查找左边子树的最右边的第一个空节点
TreeNode *search_left_first_right_null_node(TreeNode *start_node) {
  if (start_node == NULL) {
    return NULL;
  }
  while (start_node->right != NULL) {
    search_left_NULL_leaf(start_node->right);
  }
  return start_node;
}

// 查找左边子树最右边的空节点
TreeNode *search_left_most_right_null_node() { ; }

// 查找右边子树的最左边的第一个空节点
TreeNode *search_right_first_left_null_node(TreeNode *start_node) {
  if (start_node == NULL) {
    return NULL;
  }
  while (start_node->left != NULL) {
    search_right_null_node(start_node->left);
  }
  return start_node;
} */

// 第二个参数用来接收这个函数的运行结果，这里不用返回值是因为要返回的的值是在这个函数里面定义的局部变量，不可以将局部变量返回，同时该局部变量又是一个指针，
// 更不能将其作为返回值返回，又不太愿意用一个全局变量来作为返回值，所以在调用方创建一个指针变量作为函数参数用来接收执行函数结果。
// 这第二个参数必须使用二级指针，不能使用一级指针，为什么？重温一下指针的概念，怎么理解指针？
// 普通变量保存的是变量的值，指针变量保存的是变量的地址（操作系统为变量分配的内存地址）；
// 一级指针保存的是变量的地址，二级指针保存的是一个保存了变量地址的地址，指针解引用的时候要用两个星号（**)。
// 本函数中的第二个参数，如果使用TreeNode
// *result_node这个一级指针，指向的是dep_node->qn_data这个值，但是deq_node->qn_data是个函数内的局部变量，
// 这个局部变量在函数结束的时候就会从栈里面弹出被销毁,地址也就同时被系统回收了，result_node指向的地址被回收，指针的值就变成了NULL,无法实现接收函数执行结果的功能了
// 如果使用二级指针，TreeNode**result_node，首先在函数调用前，会在调用函数中创建一个
// TreeNode
// **的变量，这个变量是保存在调用函数的栈中的，不是在下面这个被调用的函数栈里面，而C语言又是值传递，
// 这个指针指就复制了dep_node->qn_data的地址，只要qn_data里面的数据没有被释放或者销毁，即这个的数据的地址没有被系统回收,
// 其他指针只要拿到了他的地址依然可以读取其中的内容。所以使用二级指针作为接收方的时候，这个二级指针复制了接收的变量地址，
// 所以函数调用完成，依然可以获取到被调用函数中的指针变量的值。
TreeNode *find_deepest_node(TreeNode *start_node, TreeNode **result_node_ptr) {
  if (start_node == NULL) {
    return NULL;
  }
  Queue *queue = create_queue();
  enqueue(queue, start_node);

  QueueNode *deq_node = NULL;
  TreeNode *result_node = NULL;
  while (!is_queue_empty(queue)) {
    dequeue(queue, &deq_node);
    if (deq_node == NULL) {
      break;
    }
    result_node = (TreeNode *)deq_node->qn_data;
    *result_node_ptr = result_node;
    if (result_node != NULL) {
      if (result_node->left != NULL) {
        enqueue(queue, result_node->left);
      }
      if (result_node->right != NULL) {
        enqueue(queue, result_node->right);
      }
    }
  }
  free(queue);
  return start_node;
}

TreeNode *delete_deepest_node(TreeNode *start_node, TreeNode *del_node) {
  if (start_node == NULL) {
    return NULL;
  }

  Queue *queue = create_queue();
  enqueue(queue, start_node);
  QueueNode *deq_node = NULL;
  TreeNode *current_node = NULL;
  while (!is_queue_empty(queue)) {
    dequeue(queue, &deq_node);
    current_node = (TreeNode *)deq_node->qn_data;
    if (current_node == NULL) {
      break;
    }
    PLAYER *current_player = (PLAYER *)current_node->tree_data;
    PLAYER *del_player = (PLAYER *)del_node->tree_data;
    if (current_player != NULL && del_player != NULL &&
        current_player->pname != NULL && del_player->pname != NULL &&
        !strcmp(current_player->pname, del_player->pname)) {
      current_node->tree_data = NULL;
      break;
    }

    if (current_node->left != NULL) {
      enqueue(queue, current_node->left);
    }
    if (current_node->right != NULL) {
      enqueue(queue, current_node->right);
    }
  }

  free(queue);
  return start_node;
}

// 删除目标节点，然后将树里面最深的那个节点的值替换掉被删除的节点的值，注意不是节点替换，是节点里面的值替换
void delete_tree_node(TreeNode *root_node, void *del_targ) {
  if (root_node == NULL || root_node->tree_data == NULL) {
    log_e("Cannot delete from empty tree");
    return;
  }
  TreeNode *wrap_node = (TreeNode *)malloc(sizeof(TreeNode));
  if (wrap_node == NULL) {
    log_e("Failed to allocate memory for wrap_node");
    return;
  }
  wrap_node->tree_data = del_targ;
  wrap_node->left = NULL;
  wrap_node->right = NULL;
  PLAYER *player = (PLAYER *)root_node->tree_data;
  PLAYER *targ_player = (PLAYER *)wrap_node->tree_data;
  if (root_node->left == NULL && root_node->right == NULL) {
    if (!strcmp(player->pname, targ_player->pname)) {
      root_node = NULL;
    }
    return;
  }
  Queue *queue = create_queue();
  enqueue(queue, root_node);

  // 结构体指针作为局部变量，如果只是临时用来接收另一个结构体指针的地址，以及传递地址给其他结构体指针，无需使用malloc分配空间，指向NULL完成初始化就可以。
  // 如果需要接收其他结构体传递过来的数据，需要使用malloc分配空间，否则无法接收其他结构体指针中的数据，没有为结构体指针分配空间，那么结构体成员也就无法接收数据
  // 使用完要将这个结构体指针的局部变量释放掉，能在本函数内直接释放的就在函数内释放，函数内无法释放的就在调用函数完成后释放。
  // 这里只是用来接收各个节点的地址，不能用malloc分配空间，比如某个接收TreeNode地址的指针使用malloc分配空间后，接收的就只是节点地址了，无法保持树的连接关系
  QueueNode *deq_node = NULL;
  TreeNode *current_node = NULL;
  bool del_targ_found = false;
  while (!is_queue_empty(queue)) {
    dequeue(queue, &deq_node);
    current_node = (TreeNode *)deq_node->qn_data;

    PLAYER *current_player = (PLAYER *)current_node->tree_data;
    if (current_player != NULL && current_player->pname != NULL &&
        targ_player != NULL && targ_player->pname != NULL &&
        !strcmp(current_player->pname, targ_player->pname)) {
      del_targ_found = true;
      wrap_node = current_node;
      break;
    }

    if (current_node->left != NULL) {
      enqueue(queue, current_node->left);
    }
    if (current_node->right != NULL) {
      enqueue(queue, current_node->right);
    }
  }

  if (!del_targ_found) {
    log_e("target node to delete not found.");
  }

  TreeNode *deepest_node = NULL;
  TreeNode *temp_node = NULL;
  temp_node = (TreeNode *)malloc(sizeof(TreeNode));
  temp_node->tree_data = NULL;
  find_deepest_node(root_node, &deepest_node);
  if (deepest_node == NULL) {
    log_e("node to delete not found.");
    return;
  }
  temp_node->tree_data = wrap_node->tree_data;
  wrap_node->tree_data = deepest_node->tree_data;
  deepest_node->tree_data = temp_node->tree_data;

  delete_deepest_node(root_node, deepest_node);
  free(queue);
}

// 对于普通二叉树节点的删除有如下几种情况，普通二叉树的节点由于没有二叉搜索树那种组织规律，很难做到通用，要将目标节点与每个树的节点去比较
// 找到要删除的节点，所以必须知道节点的，具体数据类型，通用的void*无法进行匹配和查找
// 删除节点的几种情况：
// 1. 节点没有子节点，直接删除；
// 2. 节点只有一个左子节点，左子节点替代当前删除的节点；
// 3. 节点只有一个右子节点，右子节点替代当前删除的节点；
// 4. 左右两个节点，左节点替代删除节点，右节点成为新节点的右节点；
// 5. 节点有两个左右子树（左右各不止一个节点）：
//   5.1
//   被删除的节点为父节点的左子节点，被删除节点的左子节点替代被删除节点的位置，成为父节点的左子节点；
//   5.2
//   右子树（右子节点以及他的一系列子节点）则向被删除节点的左边子树寻找，找到左边子树的最右边的空节点，右子树替代这个空节点成为右节点；
//   5.3
//   被删除的节点为父节点的右子节点，被删除节点的右子节点替代被删除节点的位置，成为父节点的右子节点；
//   5.4
//   左子树向被删除节点的右边子树寻找，找到右边子树最左边的空节点，左子树替代空节点成为左节点。
//   普通二叉树的删除存在一定的困难，有如下几个难点：
//   1. 节点删除的情况比较多，上面已经列出；
//   2.
//   这些情况要做到完全分离存在难度，比如左节点是子树包含在左节点是节点里面，删除节点的时候可能将子树也一并操作，程序会运行错误；
//   3. 删除节点的有左右子树时，节点位置放置哪个节点没有固定的规则，可以自定义；
//   所以删除普通二叉树的节点，选择将该节点及其子树全部删除，简单删除的操作
/*
void delete_tree_node(TreeNode *targ_node) {
  TreeNode *parent_root_right_leaf = NULL;
  if (root_node == NULL || root_node->ptr_data == NULL) {
    log_e("%s", "root node null, nothing to delete.");
    return NULL;
  }
  if (targ_node == NULL || targ_node->ptr_data == NULL) {
    log_e("%s", "target will delete is null.");
    return NULL;
  }
  TreeNode *parent_node = NULL;
  TreeNode *child_node = NULL;
  TreeNode *del_node = NULL;
  PLAYER *targ_player = (PLAYER *)(targ_node->ptr_data);
  PLAYER *root_player = (PLAYER *)(root_node->ptr_data);
  // 要删除的节点为根节点
  // 1. 没有左右子节点，直接置为NULL；
  // 2. 只有一个左节点，左节点成为根节点；
  // 3. 只有一个右节点，右节点成为根节点；
  // 4. 左右节点都不为空，左节点成为根节点，右节点变成新树的右节点
  // 5. 左边不止一个节点，为子树,左子树的根节点成为新树的根节点
  //   5.1 右边为空，同情形2
  //   5.2 右边为一个节点，在左子树的最右边的空节点位置替换掉这个空节点
  //   5.3 右边为子树，同5.2
  //
所以第5点综合起来就一个情况，右边节点或者子树取代左子树最右侧的空节点，成为左子树的一个节点或者子树，跟函数前的几种情况完全一样
  if (targ_node == root_node ||
      !strcmp(targ_player->pname, root_player->pname)) {
    if (targ_node->left->left != NULL || targ_node->left - right != NULL ||
        targ_node->right->left != NULL || targ_node->right->right != NULL) {
      ;
    } else {
      // 只有右节点，右节点成为根节点
      if (root_node->left == NULL && root_node->right != NULL) {
        root_node = root_node->right;
        return NULL;
        // 只有左节点，左节点成为根节点
      } else if (root_node->left != NULL && root_node->right == NULL) {
        root_node = root_node->left;
        return NULL;
        // 左右节点都不为空
      } else if (root_node->left != NULL && root_node->right != NULL) {
        if (root_node->left->left == NULL) {
          root_node = root_node->right;
        }
        parent_root_right_leaf = search_left_NULL_leaf(root_node->left);
        if (parent_root_right_leaf != NULL) {
          parent_root_right_leaf->right = root_node->right;
          root_node = root_node->left;
          return NULL;
        } else {
          log_e("%s", "error occured when find the left null leaf.");
          return NULL;
        }
      }
    }
  }
  TreeNode *left_child_node = NULL;
  TreeNode *right_child_node = NULL;
  PLAYER *left_child_player = NULL;
  PLAYER *right_child_player = NULL;
  parent_node = search_tree_node(root_node, targ_node);
  if (parent_node == NULL) {
    log_e("%s", "search node fail.");
    return NULL;
  }
  if (parent_node->left == NULL && parent_node->right == NULL) {
    parent_node->ptr_data = NULL;
    parent_node = NULL;
    return NULL;
  } else if (parent_node->left != NULL && parent_node->right == NULL) {
    parent_node = parent_node->left;
    return NULL;
  } else if (parent_node->left == NULL && parent_node->right != NULL) {
    parent_node = parent_node->right;
    return NULL;
  } else if (parent_node->left != NULL && parent_node->right != NULL) {
    left_child_node = parent_node->left;
    left_child_player = (PLAYER *)(left_child_node->ptr_data);
    right_child_node = parent_node->right;
    right_child_player = (PLAYER *)(right_child_node->ptr_data);
    if (strcmp(left_child_player->pname, right_child_player->pname) > 0) {
      // parent_node->left->right = parent_node->right;
      // parent_node = parent_node->left;
      left_child_node->right = right_child_node;
      parent_node = left_child_node;
      return NULL;
    } else if (strcmp(left_child_player->pname, right_child_player->pname) <
               0) {
      parent_node->right->left = parent_node->left;
      parent_node = parent_node->right;
      return NULL;
    }
  }
} */

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
  jordan->pname = "Jordan", jordan->pnumber = 8, jordan->salary = 3000,
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
  // dunken_node->ptr_data = dunken, dunken_node->left = NULL,dunken_node->right
  // = NULL; dunken_node->node_t = PLAYER_NODE;

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
  // jimmy_node->ptr_data = jimmy, jimmy_node->left = NULL, jimmy_node->right =
  // NULL; jimmy_node->node_t = PLAYER_NODE;

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
  // jokic_node->ptr_data = jokic, jokic_node->left = NULL, jokic_node->right =
  // NULL; jokic_node->node_t = PLAYER_NODE;

  /* player node initialized complete.*/
}

TreeNode *build_player_tree() {
  root_node = build_tree();
  init_player_data();
  insert_tree_node(root_node, jordan);
  insert_tree_node(root_node, jokic);
  insert_tree_node(root_node, yi);
  insert_tree_node(root_node, rodman);
  insert_tree_node(root_node, jimmy);
  insert_tree_node(root_node, book);
  insert_tree_node(root_node, dunken);
  insert_tree_node(root_node, camelo);
  insert_tree_node(root_node, paul);
  insert_tree_node(root_node, curry);
  insert_tree_node(root_node, yao);
  insert_tree_node(root_node, kobe);
  return root_node;
}

void test_preorder_traversal_without_recurse() {
  TreeNode *test_start_node = build_player_tree();
  log_i("(VLR)preorder traversal without recurse result is (first method): \n");
  print_tree_in_specified_order(test_start_node,
                                &preorder_traversal_without_recurse);
}

void test_preorder_traversal_without_recurse_2() {
  TreeNode *test_start_node = build_player_tree();
  log_i(
      "(VLR)preorder traversal without recurse result is (second method): \n");
  print_tree_in_specified_order(test_start_node,
                                &preorder_traversal_without_recurse_2);
}

void test_inorder_traversal() {
  TreeNode *test_start_node = build_player_tree();
  log_i("(LVR)inorder traversal result is: \n");
  print_tree_in_specified_order(test_start_node, &inorder_traversal);
}

void test_inorder_traversal_without_recurse() {
  TreeNode *test_start_node = build_player_tree();
  log_i("(LVR)inorder traversal without recurse result is: \n");
  print_tree_in_specified_order(test_start_node,
                                &inorder_traversal_without_recurse);
}

void test_postorder_traversal() {
  TreeNode *test_start_node = build_player_tree();
  log_i("(LRV)postorder traversal result is: \n");
  print_tree_in_specified_order(test_start_node, &postorder_traversal);
}

void test_postorder_traversal_without_recurse() {
  TreeNode *test_start_node = build_player_tree();
  log_i("(LRV)postorder traversal without recurse result is: \n");
  print_tree_in_specified_order(test_start_node,
                                &postorder_traversal_without_recurse);
}

void test_postorder_traversal_without_recurse_2() {
  TreeNode *test_start_node = build_player_tree();
  log_i("(LRV)postorder traversal without recurse result is: \n");
  print_tree_in_specified_order(test_start_node,
                                &postorder_traversal_without_recurse_2);
}

void test_mixedorder_traversal_without_recurse() {
  TreeNode *test_start_node = build_player_tree();
  log_i("(LRV)mixedorder traversal without recurse result is: \n");
  print_tree_in_specified_order(test_start_node,
                                &mixedorder_traversal_without_recurse);
}

void test_level_traversal() {
  TreeNode *test_start_node = build_player_tree();
  log_i("level traversal result is: \n");
  print_tree_in_specified_order(test_start_node, &level_traversal);
}

void test_player_tree() {
  init_player_data();
  int print_count = 0;
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_tree(root_node);

  insert_tree_node(root_node, jordan);

  insert_tree_node(root_node, jokic);

  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_tree(root_node);

  delete_tree_node(root_node, jordan);

  insert_tree_node(root_node, yi);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_tree(root_node);

  insert_tree_node(root_node, rodman);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_tree(root_node);

  insert_tree_node(root_node, jimmy);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_tree(root_node);

  insert_tree_node(root_node, book);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_tree(root_node);

  insert_tree_node(root_node, dunken);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_tree(root_node);

  insert_tree_node(root_node, camelo);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_tree(root_node);

  delete_tree_node(root_node, rodman);

  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_tree(root_node);

  delete_tree_node(root_node, yi);
  delete_tree_node(root_node, jimmy);
  delete_tree_node(root_node, yao);

  insert_tree_node(root_node, kobe);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_tree(root_node);

  insert_tree_node(root_node, yao);
  delete_tree_node(root_node, kobe);
  delete_tree_node(root_node, yao);
  delete_tree_node(root_node, jordan);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_tree(root_node);

  delete_tree_node(root_node, yao);

  insert_tree_node(root_node, dunken);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_tree(root_node);

  insert_tree_node(root_node, paul);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_tree(root_node);

  insert_tree_node(root_node, book);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_tree(root_node);

  insert_tree_node(root_node, jordan);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_tree(root_node);

  insert_tree_node(root_node, camelo);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_tree(root_node);

  delete_tree_node(root_node, book);
  delete_tree_node(root_node, book);
  delete_tree_node(root_node, book);
  delete_tree_node(root_node, book);
  delete_tree_node(root_node, book);
  delete_tree_node(root_node, book);
  delete_tree_node(root_node, book);
  delete_tree_node(root_node, book);
  delete_tree_node(root_node, book);
  delete_tree_node(root_node, book);
  delete_tree_node(root_node, book);
  delete_tree_node(root_node, book);
  insert_tree_node(root_node, curry);
  insert_tree_node(root_node, jimmy);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_tree(root_node);
  delete_tree_node(root_node, kobe);
  delete_tree_node(root_node, yao);
  delete_tree_node(root_node, yi);
  delete_tree_node(root_node, camelo);
  delete_tree_node(root_node, book);
  delete_tree_node(root_node, jimmy);
  delete_tree_node(root_node, dunken);
  delete_tree_node(root_node, jordan);
  delete_tree_node(root_node, jordan);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_tree(root_node);

  delete_tree_node(root_node, jordan);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_tree(root_node);

  delete_tree_node(root_node, jordan);
  delete_tree_node(root_node, jordan);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_tree(root_node);

  insert_tree_node(root_node, kobe);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_tree(root_node);

  delete_tree_node(root_node, jordan);
  delete_tree_node(root_node, jordan);
  delete_tree_node(root_node, jordan);
  delete_tree_node(root_node, jordan);
  delete_tree_node(root_node, jordan);
  delete_tree_node(root_node, jordan);
  delete_tree_node(root_node, jordan);
  delete_tree_node(root_node, jordan);
  delete_tree_node(root_node, jordan);
  delete_tree_node(root_node, jordan);
  insert_tree_node(root_node, rodman);
  insert_tree_node(root_node, book);
  insert_tree_node(root_node, jokic);
  insert_tree_node(root_node, jimmy);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_tree(root_node);
  delete_tree_node(root_node, jordan);
  delete_tree_node(root_node, jordan);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_tree(root_node);

  free(kobe), free(jordan), free(yao), free(yi), free(camelo), free(dunken);
  free(curry), free(jimmy), free(book), free(paul), free(rodman), free(jokic);

  free(root_node);
  printf("~~~~~~~~~~~~~~~~~ end ~~~~~~~~~~~~~~~~~~~~~~~");
}
