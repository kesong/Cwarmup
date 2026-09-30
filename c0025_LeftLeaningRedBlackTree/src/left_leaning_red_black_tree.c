#include "left_leaning_red_black_tree.h"
#include "../test/test_player.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 更常规红黑树不同的是，左倾红黑树只有左边的连接是红色，即红色节点只存在每个子树的左节点
// 父节点为黑色，左节点为红色，就说左边
//  release版本可以将如下这行注释取消，取消后就禁用了assert宏
//  #define NDEBUG

// TreeNode *root_node = NULL;
// TreeNode *root_node_bak = NULL;

LLRBTree *create_llrbtree() {
  LLRBTree *llrbtree = (LLRBTree *)malloc(sizeof(LLRBTree));
  if (llrbtree != NULL) {
    memset(llrbtree, 0, sizeof(LLRBTree));
  }
  return llrbtree;
}

bool is_tree_empty(TreeNode *root) {
  if (root->tree_data == NULL || root == NULL) {
    log_i("%s", "empty tree.");
    return true;
  }
  return false;
}

CompareResult compare_node(TreeNode *node_in_tree, TreeNode *node_input,
                           func_compare compare_func) {
  if (node_in_tree == NULL) {
    log_e("Node in tree is NULL.");
    return -1;
  }
  if (node_input == NULL) {
    log_e("Input a null node.");
    return -1;
  }
  int compare_value = compare_func(node_in_tree, node_input);
  if (compare_value == -1)
    return N_SMALLER;
  else if (compare_value == 0)
    return N_EQUAL;
  else if (compare_value == 1)
    return N_GREATER;

  return N_ERROR;
}

TreeNode *rotate_left(TreeNode *parent_node) {
  if (parent_node == NULL) {
    return NULL;
  }
  TreeNode *child_node = parent_node->right;
  parent_node->right = child_node->left;
  child_node->left = parent_node;
  child_node->node_color = parent_node->node_color;
  parent_node->node_color = RED_NODE;
  return child_node;
}

// 插入的时候，可能会出现两个连续的红色节点，此时就需要先右旋转，然后旋转后的左右两个子节点颜色翻转
TreeNode *rotate_right(TreeNode *parent_node) {
  if (parent_node == NULL) {
    return NULL;
  }
  TreeNode *child_node = parent_node->left;
  parent_node->left = child_node->right;
  child_node->right = parent_node;
  child_node->node_color = parent_node->node_color;
  parent_node->node_color = RED_NODE;
  return child_node;
}

/*
//
插入的节点（grandchild_node）在父节点（child_node）的右子树，child_node在父节点（parent_node）的左子树；
//
先将child_node进行左旋转，不改变节点颜色，再将parent_node进行右旋转，需要改变节点颜色。
TreeNode *left_rotate_then_right(TreeNode *parent_node, TreeNode *child_node) {
  if (parent_node == NULL) {
    return NULL;
  }
  if (child_node == NULL) {
    return NULL;
  }
  TreeNode *child_node_bak = child_node;
  child_node = child_node->right;
  child_node_bak->right = child_node->left;
  child_node->left = child_node_bak;

  parent_node->left = child_node;
  parent_node = right_rotate(parent_node);
  return parent_node;
}

//
插入的节点（grandchild_node）在父节点（child_node）的左子树，child_node在父节点（parent_node）的右子树；
//
先将child_node进行右旋转，不改变节点颜色，再将parent_node进行左旋转，需要改变节点颜色。
TreeNode *right_rotate_then_left(TreeNode *parent_node, TreeNode *child_node) {
  if (parent_node == NULL) {
    return NULL;
  }
  if (child_node == NULL) {
    return NULL;
  }
  TreeNode *child_node_bak = child_node;
  child_node = child_node->left;
  child_node_bak->left = child_node->right;
  child_node->right = child_node_bak;

  parent_node->right = child_node;
  parent_node = left_rotate(parent_node);
  return parent_node;
}  */

// 父节点和左右两个子节点的颜色翻转
TreeNode *flip_color(TreeNode *parent_node) {
  if (parent_node == NULL) {
    return NULL;
  }
  parent_node->node_color = !parent_node->node_color;
  parent_node->left->node_color = !parent_node->left->node_color;
  parent_node->right->node_color = !parent_node->right->node_color;
  return parent_node;
}

bool is_red(TreeNode *cur_node) {
  if (cur_node == NULL) {
    return false;
  }
  if (cur_node->node_color == RED_NODE) {
    return true;
  }
  return false;
}

LeftOrRight child_is_left_or_right(TreeNode *parent_node,
                                   TreeNode *child_node) {
  if (parent_node == NULL) {
    return -1;
  }
  if (child_node == NULL) {
    return -1;
  }
  int result_left = -2;
  int result_right = -2;
  if (parent_node->left != NULL) {
    result_left = compare_node_by_name(parent_node->left, child_node);
  }
  if (parent_node->right != NULL) {
    result_right = compare_node_by_name(parent_node->right, child_node);
  }
  if (result_left == 0) {
    return LEFT_NODE;
  }
  if (result_right == 0) {
    return RIGHT_NODE;
  }
  return -1;
}

bool is_root_node(TreeNode *start_node, TreeNode *search_node) {
  if (search_node == NULL) {
    log_e("The node will searching is NULL.");
    return false;
  }
  int compare_to_root_node = compare_node_by_name(start_node, search_node);
  if (compare_to_root_node == 0) {
    return true;
  }
  return false;
}

// 获取某个节点的父节点，从根节点开始将查询路径上的每一个节点都压入栈中，找到要查询的节点后开始从栈中弹出数据，弹出的第一个数据就是被查询节点的父节点
// 父节点作为参数传入，而且是以NULL传入；
TreeNode *get_parent_node(TreeNode *start_node, TreeNode *search_node,
                          TreeNode *parent_node) {
  if (search_node == NULL) {
    return NULL;
  }
  TreeNode *current_node = start_node;
  TreeNode *child_node = NULL;
  Stack *stack = create_stack();
  bool check_root_node = is_root_node(start_node, search_node);
  if (check_root_node == 0) {
    log_i("Search node is root node, searching completed.");
    return start_node;
  }
  for (;;) {
    while (current_node != NULL) {
      int search_result = compare_node_by_name(current_node, search_node);
      if (search_result == -1) {
        push(stack, current_node);
        current_node = current_node->left;
      } else if (search_result == 1) {
        push(stack, current_node);
        current_node = current_node->right;
      } else if (search_result == 0) {
        break;
      }
    }

    if (current_node != NULL) {
      child_node = current_node;
    }
    pop(stack, &parent_node);
    if (parent_node == NULL) {
      log_i("The parent of node not found.");
      break;
    }
    return parent_node;
  }
  return NULL;
}

// 不使用栈，从根节点开始直接判断根节点的左右节点是否与查询节点相同，如果与左节点或者右节点相同，这个左右节点的父节点就是备被查询节点的父节点
TreeNode *get_parent_node_without_stack(TreeNode *start_node,
                                        TreeNode *search_node) {
  int compare_result = -2;
  compare_result = compare_node_by_name(start_node, search_node);
  if (compare_result == 0) {
    return NULL;
  }
  if (compare_result == -1) {
    if (start_node->left != NULL) {
      compare_result = compare_node_by_name(start_node->left, search_node);
      if (compare_result == 0) {
        return start_node;
      }
    }
    start_node = get_parent_node_without_stack(start_node->left, search_node);
  } else if (compare_result == 1) {
    if (start_node->right != NULL) {
      compare_result = compare_node_by_name(start_node->right, search_node);
      if (compare_result == 0) {
        return start_node;
      }
    }
    start_node = get_parent_node_without_stack(start_node->right, search_node);
  }
  if (start_node->left == NULL && start_node->right == NULL) {
    return NULL;
  }
  return start_node;
}

// 左倾红黑树插入节点与红黑树稍有差别，相同的是插入的节点颜色也一定是红色，左倾红黑树引入了2-3-4树的理念，
// 2节点：单个黑色节点。
// 3节点：父节点为黑色只有一个左子节点或者只有一个右子节点，左子节点或者右子节点为红色。
// 4节点：父节点为黑色，左右子节点均为为红色。
// 插入的思想，最下方的节点为3节点时插入新的红色节点，会变成一个4节点，4节点需要分裂成两个黑色节点和一个红色父节点，以红色父节点当作新的插入节点
// 继续向上判断是否有两个连续的红色节点。
// 所以左倾红黑树也是从下向上生长，同普通红黑树，4节点不断分裂，向上生长。
// 左倾红黑树的插入有如下几种情况
// 1. 插入节点在左子树，父节点为黑色，直接插入；
// 2.
// 插入节点在左子树，父节点为红色，就出现了连续的两个红色分支，父节点右旋（父节点染黑，爷节点染红），旋转后父节点的左右两个节点染黑，父节点染红；
// 3. 插入节点在右子树，兄弟节点为黑色，插入后父节点左旋；
// 4. 插入节点在右子树，兄弟节点为红色，父节点和左右子节点颜色翻转；
// 5.
// 插入节点在右子树，父节点为红色（父节点一定在左子树），父节点左旋，转化成情况2；
// 6. 第2和第4种情况需要将变为红色的父节点看作新插入的节点，继续向上递归；
TreeNode *insert_tree_node(TreeNode *root_node, TreeNode *start_node,
                           TreeNode *inst_node) {
  TreeNode *current_node = start_node;

  if (inst_node == NULL) {
    return start_node;
  }

  if (root_node == NULL) {
    root_node = inst_node;
    TreeNode *root_node_bak = root_node;
    root_node->node_color = BLACK_NODE;
    return root_node;
  }
  if (root_node->tree_data == NULL) {
    root_node->tree_data = inst_node->tree_data;
    return root_node;
  }

  // 插入节点
  if (start_node == NULL) {
    start_node = inst_node;
  }

  int compare_result = compare_node_by_name(start_node, inst_node);
  if (compare_result == 0) {
    // return root_node;
  } else if (compare_result == -1) {
    start_node->left = insert_tree_node(root_node, start_node->left, inst_node);
  } else if (compare_result == 1) {
    start_node->right =
        insert_tree_node(root_node, start_node->right, inst_node);
  }

  /*
  // 节点已经插入，获取start_node的父节点（inst_node的爷爷节点）
  TreeNode *parent_node = NULL;
  TreeNode *grandp_node = NULL;
  if (start_node != root_node) {
    parent_node = get_parent_node_without_stack(root_node, start_node);
    if (parent_node != NULL) {
      grandp_node = get_parent_node_without_stack(root_node, parent_node);
    }
  } */
  if (!is_red(start_node->left) && is_red(start_node->right)) {
    start_node = rotate_left(start_node);
  }
  if (start_node->left != NULL) {
    if (is_red(start_node->left) && is_red(start_node->left->left)) {
      start_node = rotate_right(start_node);
    }
  }
  if (is_red(start_node->left) && is_red(start_node->right)) {
    start_node = flip_color(start_node);
  }

  return start_node;
}

TreeNode *insert_node(TreeNode *root_node, TreeNode *insert_node) {
  root_node = insert_tree_node(root_node, root_node, insert_node);
  if (root_node->node_color == RED_NODE) {
    root_node->node_color = BLACK_NODE;
  }
  return root_node;
}

// 左倾红黑树的删除，可以看作插入的逆过程，还是用2-3-4树的概念。
// 删除一个2节点，就是普通的黑色节点，会导致这个分支少了一个黑色节点，因此不平衡，删除一个3节点或者4节点中的节点（红色），直接删除，不影响树的平衡
// 所以左倾红黑树的删除就是从根节点开始沿左边向下将最左边（选择最小的节点来替代被删除节点）的节点变成红色，即一个3节点，然后删除。
// 2-3-4树插入红色节点后向上生长，直至根节点，那么向下变红的操作就是将根节点的左右子节点变红，调整结束的标志是最左边的节点（最小树节点）为红色，
// 或者最左边的节点的父节点为红色。
// 在从上往下将节点变红的过程中，只有start_node->left，和start_node->left->left均为黑色时候需要调整，此时会有两种情况
// 1.
// start_node->right->left为黑色，只需要将start_node和左右子节点翻转颜色即可；
// 2.
// start_node->right->left为红色，start_node->right右旋转，再将start_node左旋转；
TreeNode *move_red_left(TreeNode *root_node, TreeNode *start_node) {
  flip_color(start_node);
  if (start_node->right != NULL && start_node->right->left != NULL) {
    if (is_red(start_node->right->left)) {
      start_node->right = rotate_right(start_node->right);
      start_node = rotate_left(start_node);
      flip_color(start_node);
    }
  }
  return start_node;
}

// 通过move_red_left，将最左边的节点调整为红色，再将它删除。
// 删除树中的最小节点（与普通红黑树一样，以待删除节点的右节点为根节点，这棵子树的最左边节点或者叫最小节点就是被删除节点的后继节点），可以用来替代被删除节点
TreeNode *delete_tree_node_min(TreeNode *root_node, TreeNode *start_node) {
  if (start_node == NULL) {
    return NULL;
  }

  if (start_node->left == NULL) {
    return NULL;
  }

  if (!is_red(start_node) && is_red(start_node->left->left)) {
    move_red_left(root_node, start_node);
  }
  if (start_node->left != NULL) {
    start_node->left = delete_tree_node_min(root_node, start_node->left);
  }
  return start_node;
}

// 被删除节点在右边的时候就需要一个函数能够将右边的节点变红，也是从根节点开始，根节点（start_node）的左右子节点变红，再将变红的右节点（start_node->right）变黑，
// 再将start_node->right的左右子节点变红，以此递归往下进行调整，直至找到待删除节点，并且待删除节点或者待删除节点的右节点为红色；
TreeNode *move_red_right(TreeNode *root_node, TreeNode *start_node) {
  flip_color(start_node);
  if (start_node->left != NULL && start_node->left->left != NULL) {
    if (is_red(start_node->left->left)) {
      start_node = rotate_right(start_node);
      start_node->node_color = RED_NODE;
      start_node->left->node_color = BLACK_NODE;
      flip_color(start_node);
    }
  }
  return start_node;
}

// 删除某个节点的子树中最大的节点（即以这个节点为根节点的树的最右边的节点）
TreeNode *delete_tree_node_max(TreeNode *root_node, TreeNode *start_node) {
  if (start_node == NULL) {
    return NULL;
  }
  if (start_node->right == NULL) {
    return start_node->left;
  }
  if (is_red(start_node->left)) {
    start_node->right = NULL;
    start_node = rotate_right(start_node);
    start_node->node_color = BLACK_NODE;
  }
  if (!is_red(start_node) && !is_red(start_node->right->left)) {
    move_red_right(root_node, start_node);
  }
  start_node->right = delete_tree_node_max(root_node, start_node->right);
  return start_node;
}

// 获取某个节点的左子树最大子节点（前驱节点，节点左子树最右边的节点）
TreeNode *max_tree_node(TreeNode *start_node) {
  if (start_node == NULL) {
    return NULL;
  }
  if (start_node->right == NULL) {
    return start_node;
  }
  return min_tree_node(start_node->right);
}

// 获取某个节点右子树的最小子节点（后继节点，节点右子树最左边的节点）
TreeNode *min_tree_node(TreeNode *start_node) {
  if (start_node == NULL) {
    return NULL;
  }
  if (start_node->left == NULL) {
    return start_node;
  }
  return max_tree_node(start_node->left);
}

// 左倾红黑树的删除逻辑
TreeNode *delete_tree_node(TreeNode *root_node, TreeNode *start_node,
                           TreeNode *del_node) {
  TreeNode *temp_node = NULL;
  int compare_result = compare_node_by_name(start_node, del_node);
  if (compare_result < 0) {
    if (!is_red(start_node) && is_red(start_node->left->left)) {
      move_red_left(root_node, start_node);
    }
    start_node->left = delete_tree_node(root_node, start_node->left, del_node);
  } else {
    if (compare_result == 0 && start_node->right == NULL) {
      return NULL;
    }
    if (!is_red(start_node) && !is_red(start_node->right->left)) {
      move_red_right(root_node, start_node);
    }
    if (compare_result == 0) {
      temp_node = min_tree_node(start_node->right);
      del_node->tree_data = temp_node->tree_data;
      start_node->right = delete_tree_node_min(root_node, start_node->right);
    }
    start_node = delete_tree_node(root_node, start_node, del_node->right);
  }
  return root_node;
}

void delete_node(TreeNode *root_node, TreeNode *delete_node) {
  if (delete_node == NULL) {
    log_e("Node not found.");
  }
  root_node = delete_tree_node(root_node, root_node, delete_node);
}

// 将树的所有节点入栈
TreeNode *push_node_to_stack(Stack *in_stack, TreeNode *in_node) {
  if (in_node == NULL) {
    return in_node;
  }
  push_node_to_stack(in_stack, in_node->left);
  push(in_stack, in_node);
  push_node_to_stack(in_stack, in_node->right);
  return NULL;
}

// 清空树，并不清空树中的节点所携带的数据，本质就是断开每个节点与左右子树的链接关系，
// 中序遍历一棵树，将遍历的每个节点入栈，然后将每个节点的左右子树都置为NULL，树的每个节点变成孤立的节点
// 最后将root_node置为NULL；
TreeNode *clear_tree(TreeNode *root_node, TreeNode *start_node) {
  Stack *stack = create_stack();
  push_node_to_stack(stack, start_node);
  while (!is_stack_empty(stack)) {
    TreeNode *poped_node = NULL;
    pop(stack, &poped_node);
    if (poped_node == NULL) {
      break;
    }
    poped_node->left = NULL;
    poped_node->right = NULL;
  }
  root_node = NULL;
  free(stack);
  return root_node;
}

// 用V表示二叉树的中间节点，L表示左节点，R表示右节点
// 二叉树的前序遍历（节点遍历顺序为VLR），递归遍历，递归遍历法在调试的时候可以很明显的看到函数最后两个递归语句的第一个递归（left子树递归）在执行到return语句
// 后只会退出当前left递归函数（退出第一个栈），然后开始执行right分支递归（第二个栈操作），return并不会直接退出整个函数。
// 也证明了递归函数执行其实就是调用了系统的栈，将递归函数的每一个执行步骤都压入栈中，然后再不断的从栈中弹出执行，
// 类似树这种数据结构的递归，如果树的深度很深，不停的调用系统栈进行压栈，最终会导致栈溢出，尤其是这种递归出现在函数尾部的函数，
// 很可能就产生了尾递归效应，导致栈的溢出。
// 为了让二叉树更有普遍性，可以作为库函数被其他程序调用，在二叉树的遍历中不要使用打印遍历节点的操作
// 将遍历的结果放入一个数组，链表，栈或者队列，返回保存遍历结果的数据结构的首地址，再使用打印函数去打印遍历结果
// 同时，将遍历结果放入一个数据结构中的好处是方便进行树的其他操作，比如比较两个树是否相同，可以将遍历结果保存在数组里面，
// 就成了比较两个数组是否相同了。
TreeNode *preorder_traversal(TreeNode *trav_node, TreeNode **trav_result,
                             void *index) {
  int *temp_index = (int *)index;
  if (trav_node == NULL || trav_node->tree_data == NULL) {
    return NULL;
  }
  if (*temp_index < MAX_SIZE) {
    trav_result[(*temp_index)++] = trav_node;
  } else {
    log_e("%s %s", __func__, "node array is fulled.");
    return trav_node;
  }
  if (trav_node->left != NULL) {
    preorder_traversal(trav_node->left, trav_result, temp_index);
  }
  if (trav_node->right != NULL) {
    preorder_traversal(trav_node->right, trav_result, temp_index);
  }
  return trav_node;
}

/* 前序遍历二，原理同上，只不过用指针来进行寻址，根据指针和指针数组的概念，*(trav_result)
= trav_result[0], *(trav_result + 1) = trav_result[1]。
 * 但在这里使用这种方法，无法将树里面的数据正确保存到trav_result数组中。原因是递归导致，递归本质是一种压栈行为，
 * 所以第一个递归语句执行的时候，如果trav_node->left不为空，会将trav_result的地址压入栈中（addrA），随着树的左分支的遍历，
 * trav_result的会增加，增加的数目是左边子树的节点个数，左分支遍历完成，进行出栈，进入右分支的时候读取的是此前压入栈中的地址，还是addrA，那么中间
 * 遍历过程中trav_result地址增加的部分会被此次遍历覆盖，其中保存的节点也就被覆盖了，导致最后打印的数据不完整。
TreeNode *preorder_traversal(TreeNode *trav_node, TreeNode **trav_result) {
  if (trav_node == NULL || trav_node->tree_data == NULL) {
    return trav_node;
  }
  *trav_result = trav_node;
  trav_result += 1;
  preorder_traversal(trav_node->left, trav_result);       //第一个递归语句
  preorder_traversal(trav_node->right, trav_result);      //第二个递归语句
  return root_node;
} */

// 前序遍历，非递归遍历方法一，遍历思路：
// 始终向左，同时将有节点压入栈中，直到作左节点为空，此时已经到达最左边的节点了
// 然后从栈里面弹出，此时是最左边的节点的右子节点，继续重复上面的步骤，先左，压栈，弹栈，最终完成遍历
// 遍历的每个节点放入数组，函数的第二个参数传入一个空数组指针，用来接受遍历的结果，数组元素的顺序就是遍历的结果
TreeNode *preorder_traversal_without_recurse(TreeNode *trav_node,
                                             TreeNode **result_array,
                                             void *none_ptr) {
  TreeNode *temp_node = NULL;
  Stack *stack = create_stack();
  while (true) {
    while (trav_node != NULL) {
      // 根节点入数组，下一轮循环就是左右子节点的父节点入数组了
      *result_array = trav_node;
      result_array += 1;
      if (trav_node->right != NULL) {
        push(stack, trav_node->right);
      }
      if (trav_node->left == NULL) {
        break;
      }
      trav_node = trav_node->left;
    }
    if (is_stack_empty(stack)) {
      break;
    }
    // 弹出右节点保存在temp_node中
    pop(stack, &temp_node);
    if (temp_node == NULL) {
      break;
    }
    trav_node = temp_node;
  }
  free(stack);
  return trav_node;
}

// 前序遍历，非递归方法二，还是用栈，少一个循环语句,将二叉树只看作一个最多有三个节点的小树（左节点L，中间节点V，右节点R），前序遍历的顺序是VLR，
// 根据栈先进后出的逻辑，将右节点最先入栈，然后将左节点入栈，将中间节点保存到数组中，然后向左边子树深入重复这一动作，直到左节点为空，再从栈中弹出节点，
// 判断节点，此时弹出的节点应该是中间节点，判断右子树是否为空，不为空就进入右子树，重复以上过程
TreeNode *preorder_traversal_without_recurse_2(TreeNode *trav_node,
                                               TreeNode **result_array,
                                               void *none_ptr) {
  TreeNode *temp_node = NULL;
  Stack *stack = create_stack();
  push(stack, trav_node);
  while (!is_stack_empty(stack)) {
    pop(stack, &temp_node);
    if (temp_node == NULL) {
      log_e("error!");
    }
    *result_array = temp_node;
    result_array += 1;
    if (temp_node->right != NULL) {
      push(stack, temp_node->right);
    }
    if (temp_node->left != NULL) {
      push(stack, temp_node->left);
    }
  }
  free(stack);
  return trav_node;
}

TreeNode *inorder_traversal(TreeNode *trav_node, TreeNode **trav_result,
                            void *index) {
  int *temp_index = (int *)index;
  if (trav_node == NULL || trav_node->tree_data == NULL) {
    return NULL;
  }
  if (trav_node->left != NULL) {
    inorder_traversal(trav_node->left, trav_result, temp_index);
  }
  if (*temp_index < MAX_SIZE) {
    trav_result[(*temp_index)++] = trav_node;
  } else {
    log_e("%s %s", __func__, "node array is fulled.");
    return trav_node;
  }
  if (trav_node->right != NULL) {
    inorder_traversal(trav_node->right, trav_result, temp_index);
  }
  return trav_node;
}

// 中序遍历，非递归遍历方法一，中序遍历的顺序是LVR，根据这个顺序，遍历思路就是先遍历根节点左边的子树，将左边的节点全部压入栈中
// 到左边最后一个节点后，开始出栈，第一个出栈的就是左边子树的最左边的节点，也是整个树遍历出来排在第一个的节点，将该节点放入结果数组的第一个元素的位置，
// 然后判断该节点是否有右边子树，如果有就进入右边子树，开始遍历右边子树的左边节点，重复一开始的遍历步骤。将整个栈中的数据处理完，整棵树的中序遍历就完成了。
TreeNode *inorder_traversal_without_recurse(TreeNode *trav_node,
                                            TreeNode **trav_result,
                                            void *none_ptr) {
  Stack *stack = create_stack();
  TreeNode *poped_node = NULL;
  TreeNode *temp_node = NULL;
  temp_node = trav_node;
  for (;;) {
    for (; temp_node; temp_node = temp_node->left) {
      if (temp_node != NULL) {
        push(stack, temp_node);
      }
    }
    if (is_stack_empty(stack)) {
      break;
    }
    pop(stack, &poped_node);
    if (poped_node != NULL) {
      *trav_result = poped_node;
      trav_result += 1;
    }
    if (poped_node->right != NULL) {
      poped_node = poped_node->right;
      temp_node = poped_node;
    }
  }
  free(stack);
  return trav_node;
}

TreeNode *postorder_traversal(TreeNode *trav_node, TreeNode **trav_result,
                              void *index) {
  int *temp_index = (int *)index;
  if (trav_node != NULL && trav_node->left != NULL) {
    postorder_traversal(trav_node->left, trav_result, temp_index);
    postorder_traversal(trav_node->right, trav_result, temp_index);
  }
  if (*temp_index < MAX_SIZE) {
    trav_result[(*temp_index)++] = trav_node;
  } else {
    log_e("%s %s", __func__, "node array is fulled.");
    return trav_node;
  }
  return trav_node;
}

// 后序遍历，非递归遍历方法，前序遍历的顺序为VLR，后序遍历的顺序为LRV，前序遍历中先将有子树压入了栈中，这里将前序遍历中的左子树先压入栈中，遍历顺序就变成了VRL，然后
// 将VRL的遍历结果逆序，就变成了LRV了。
//
TreeNode *postorder_traversal_without_recurse(TreeNode *trav_node,
                                              TreeNode **trav_result,
                                              void *none_ptr) {
  if (trav_node == NULL) {
    return NULL;
  }
  Stack *stack = create_stack();
  TreeNode *poped_node = NULL;
  TreeNode *temp_node = NULL;
  TreeNode *reverse_trav_result = NULL;
  temp_node = trav_node;
  push(stack, temp_node);
  int count = 0;
  while (!is_stack_empty(stack)) {
    pop(stack, &poped_node);
    if (poped_node == NULL) {
      break;
    }
    *trav_result = poped_node;
    trav_result += 1;
    count++;
    if (poped_node->left != NULL) {
      push(stack, poped_node->left);
    }
    if (poped_node->right != NULL) {
      push(stack, poped_node->right);
    }
  }
  // 将结果trav_result逆序，就得到后序遍历的结果了
  trav_result -= 1;
  int j = 0;
  for (int i = count - 1; i >= (count / 2); i--, j++) {
    reverse_trav_result = *(trav_result - i);
    *(trav_result - i) = *(trav_result - j);
    *(trav_result - j) = reverse_trav_result;
  }
}

// 不知道顺序的遍历方法，留个笔记在这里，就先不删掉了
TreeNode *postorder_traversal_without_recurse_2(TreeNode *trav_node,
                                                TreeNode **trav_result,
                                                void *none_ptr) {
  if (trav_node == NULL) {
    return NULL;
  }
  Stack *stack = create_stack();
  Stack *temp_stack = create_stack();
  TreeNode *poped_node = NULL;
  TreeNode *temp_node = NULL;
  TreeNode *temp_poped = NULL;
  temp_node = trav_node;
  push(stack, temp_node);
  while (true) {
    for (; temp_node; temp_node = temp_node->left) {
      if (temp_node->right != NULL) {
        push(stack, temp_node->right);
      }
      if (temp_node->left != NULL) {
        push(stack, temp_node->left);
      }
    }
    if (is_stack_empty(stack)) {
      break;
    }
    pop(stack, &poped_node);
    if (poped_node != NULL) {
      if (poped_node->left == NULL && poped_node->right == NULL) {
        *trav_result = poped_node;
        trav_result += 1;
      }
    }
    if (poped_node->right != NULL) {
      push(temp_stack, poped_node);
      temp_node = poped_node->right;
    }
    if (temp_node != NULL) {
      while (!is_stack_empty(temp_stack)) {
        pop(temp_stack, &temp_poped);
        if (temp_poped != NULL) {
          *trav_result = temp_poped;
          trav_result += 1;
        }
      }
    }
  }

  return trav_node;
}

// 混合遍历，非递归遍历，实现后序遍历非递归方法的时候未能正确实现后序遍历，但也能正常遍历完二叉树，遍历方法也比较简单，
// 打印的节点顺序缺少一个稳定的规律，实际中可能无法使用，记录这个发现。
TreeNode *mixedorder_traversal_without_recurse(TreeNode *trav_node,
                                               TreeNode **trav_result,

                                               void *none_ptr) {
  if (trav_node == NULL) {
    return NULL;
  }
  Stack *stack = create_stack();
  TreeNode *poped_node = NULL;
  TreeNode *temp_node = NULL;
  temp_node = trav_node;
  push(stack, temp_node);
  while (true) {
    for (; temp_node; temp_node = temp_node->left) {
      if (temp_node->right != NULL) {
        push(stack, temp_node->right);
      }
      if (temp_node->left != NULL) {
        push(stack, temp_node->left);
      }
    }
    if (is_stack_empty(stack)) {
      break;
    }
    pop(stack, &poped_node);
    if (poped_node != NULL) {
      *trav_result = poped_node;
      trav_result += 1;
    }
    if (poped_node->right != NULL) {
      temp_node = poped_node->right;
    }
  }

  return trav_node;
}

// 层序遍历,遍历思路：
// 从根节点开始每个节点都放入队列，
TreeNode *level_traversal(TreeNode *trav_node, TreeNode **trav_result,
                          void *none_ptr) {
  Queue *queue = create_queue();
  QueueNode *deq_node = NULL;
  TreeNode *temp_node = NULL;
  temp_node = trav_node;
  // 根节点入列
  enqueue(queue, temp_node);
  // 出列的每个节点地址都保存在level_trav_result数组中，最后返回这个数组的首地址就是二叉树的层序遍历结果，所以这里用了二阶指针，或者叫二重指针
  // 这里根节点也可以不用出列，但我们为了保持队列为空，在每一层子节点入列出列的过程中不受队列里面原有数据的干扰
  // dequeue(queue, &deq_node);
  //*trav_result = (TreeNode *)deq_node->qn_data;
  // trav_result += 1;
  // int *que_size = NULL;
  // size_of_queue(queue, que_size);
  // 队列一边有节点入列，一边有节点出列，这里只用一层子节点遍历完成入列后计算的队列里面数据的多少，不用判断队列是否为空或者队首节点是否为空来判断
  while (!is_queue_empty(queue)) {
    dequeue(queue, &deq_node);
    if (deq_node == NULL) {
      break;
    }
    temp_node = (TreeNode *)deq_node->qn_data;
    *trav_result = (TreeNode *)deq_node->qn_data;
    trav_result += 1;
    // 左子节点入列
    if (temp_node->left != NULL) {
      enqueue(queue, temp_node->left);
    }
    // 右子节点入列
    if (temp_node->right != NULL) {
      enqueue(queue, temp_node->right);
    }
  }
  return trav_node;
}
