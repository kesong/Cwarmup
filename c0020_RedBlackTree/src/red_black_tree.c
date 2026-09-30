#include "red_black_tree.h"
#include "../test/test_player.h"
#include <assert.h>
#include <stdlib.h>
#include <time.h>

// release版本可以将如下这行注释取消，取消后就禁用了assert宏
// #define NDEBUG

TreeNode *root_node = NULL;
TreeNode *root_node_bak = NULL;

TreeNode *build_tree() {
  root_node = (TreeNode *)malloc(sizeof(TreeNode));
  if (root_node == NULL) {
    log_e("error, malloc for root node failed.");
  }
  root_node->tree_data = NULL;
  root_node->left = NULL;
  root_node->right = NULL;
  root_node->node_color = BLACK_NODE;
  root_node_bak = root_node;
  return root_node;
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

TreeNode *left_rotate(TreeNode *start_node) {
  if (start_node == NULL) {
    return NULL;
  }
  TreeNode *start_node_bak = start_node;
  start_node = start_node->right;
  start_node_bak->right = start_node->left;
  start_node->left = start_node_bak;
  start_node_bak->node_color = start_node->node_color;
  start_node->node_color = BLACK_NODE;
  return start_node;
}

TreeNode *right_rotate(TreeNode *start_node) {
  if (start_node == NULL) {
    return NULL;
  }
  TreeNode *start_node_bak = start_node;
  start_node = start_node->left;
  start_node_bak->left = start_node->right;
  start_node->right = start_node_bak;
  start_node_bak->node_color = start_node->node_color;
  start_node->node_color = BLACK_NODE;
  return start_node;
}

// 插入的节点（grandchild_node）在父节点（child_node）的右子树，child_node在父节点（parent_node）的左子树；
// 先将child_node进行左旋转，不改变节点颜色，再将parent_node进行右旋转，需要改变节点颜色。
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

// 插入的节点（grandchild_node）在父节点（child_node）的左子树，child_node在父节点（parent_node）的右子树；
// 先将child_node进行右旋转，不改变节点颜色，再将parent_node进行左旋转，需要改变节点颜色。
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
}

TreeNode *flip_color(TreeNode *start_node) {
  if (start_node == NULL) {
    return NULL;
  }
  if (start_node->node_color == BLACK_NODE) {
    start_node->node_color = RED_NODE;
    start_node->left->node_color = BLACK_NODE;
    start_node->right->node_color = BLACK_NODE;
  }
  return start_node;
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

bool is_root_node(TreeNode *search_node) {
  if (root_node == NULL) {
    log_e("Root node is NULL.");
    return false;
  }
  if (search_node == NULL) {
    log_e("The node will searching is NULL.");
    return false;
  }
  int compare_to_root_node = compare_node_by_name(root_node, search_node);
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
  bool check_root_node = is_root_node(search_node);
  if (check_root_node == 0) {
    log_i("Search node is root node, searching completed.");
    return root_node;
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

// 插入节点后的颜色检查，即插入节点的颜色跟父节点的颜色均为红色
// 从插入节点开始检查，完成插入节点的检查后，将插入节点的入节点作为新的插入节点，继续向上检查，直到不出现父子均为红色节点或者到根节点结束
// 这里颜色检查采用递归调用，也可以使用循环，使用递归代码逻辑清晰，结构简单，容易理解，但是要注意，递归调用的时候每一次递归调用其实就是一次新的函数调用，
// return语句只会退出当前这一层的调用，会继续执行递归调用语句下面的代码，所以递归调用里面的退出非常重要，避免出席那无限递归导致栈溢出，以及递归调用返回到
// 上一层级的递归函数后执行的代码并不是期望执行的位置。
TreeNode *check_color_and_modify(TreeNode *child_node,
                                 TreeNode *grandchild_node) {
  if (grandchild_node == NULL || child_node == NULL) {
    return root_node;
  }
  if (child_node == root_node) {
    return root_node;
  }
  // 只有连续的两个节点为红才需要继续，否则返回根节点
  if (child_node->node_color == RED_NODE &&
      grandchild_node->node_color == RED_NODE) {
  } else {
    return root_node;
  }

  TreeNode *parent_node = get_parent_node_without_stack(root_node, child_node);
  TreeNode *grandp_node = NULL;
  LeftOrRight lr_parent = -2;
  LeftOrRight lr_child = -2;
  LeftOrRight lr_gchild = -2;

  // 说明child_node为根节点，根节点置黑，返回根节点；
  if (parent_node == NULL) {
    child_node->node_color = BLACK_NODE;
    return root_node;
  }

  if (parent_node != NULL && parent_node != root_node) {
    grandp_node = get_parent_node_without_stack(root_node, parent_node);
    lr_parent = child_is_left_or_right(grandp_node, parent_node);
  }

  if (parent_node != NULL) {
    lr_child = child_is_left_or_right(parent_node, child_node);
  }

  lr_gchild = child_is_left_or_right(child_node, grandchild_node);

  if (child_node == root_node) {
    child_node->node_color = BLACK_NODE;
    return root_node;
  }

  // 插入节点或者待检查节点的父节点和叔节点均为红色，父节点和叔节点变黑，爷节点变红，爷节点作为待检查节点，继续向上检查
  if (parent_node->left != NULL & parent_node->right != NULL) {
    if (parent_node->left->node_color == RED_NODE &&
        parent_node->right->node_color == RED_NODE) {
      parent_node = flip_color(parent_node);
      if (parent_node == root_node) {
        parent_node->node_color = BLACK_NODE;
        return parent_node;
      }
      grandp_node = get_parent_node_without_stack(root_node, parent_node);
      child_node = check_color_and_modify(grandp_node, parent_node);
      if (child_node == root_node) {
        return root_node;
      }
    }
  }

  // LL型，插入节点或者待检查节点为孙节点，子节点，孙节点都在左子树，父节点左旋
  if (lr_child == LEFT_NODE && lr_gchild == LEFT_NODE) {
    if (parent_node == root_node) {
      root_node = right_rotate(parent_node);
      return root_node;
    }
    parent_node = right_rotate(parent_node);
    if (parent_node == root_node) {
    }
    if (lr_parent == LEFT_NODE) {
      grandp_node->left = parent_node;
    } else {
      grandp_node->right = parent_node;
    }
    grandp_node = get_parent_node_without_stack(root_node, parent_node);
    child_node = check_color_and_modify(grandp_node, parent_node);
    if (child_node == root_node) {
      return root_node;
    }
  }

  // LR型，孙节点在子节点的右子树，子节点在左子树，先子节点左旋，再父节点右旋
  if (lr_child == LEFT_NODE && lr_gchild == RIGHT_NODE) {
    if (parent_node == root_node) {
      root_node = left_rotate_then_right(parent_node, child_node);
      return root_node;
    }
    parent_node = left_rotate_then_right(parent_node, child_node);
    if (lr_parent == LEFT_NODE) {
      grandp_node->left = parent_node;
    } else {
      grandp_node->right = parent_node;
    }
    grandp_node = get_parent_node_without_stack(root_node, grandp_node);
    child_node = check_color_and_modify(grandp_node, parent_node);
    if (child_node == root_node) {
      return root_node;
    }
  }

  // RR型，子节点和孙节点均在右子树，父节点左旋
  if (lr_child == RIGHT_NODE && lr_gchild == RIGHT_NODE) {
    if (parent_node == root_node) {
      root_node = left_rotate(parent_node);
      return root_node;
    }
    parent_node = left_rotate(parent_node);
    if (lr_parent == LEFT_NODE) {
      grandp_node->left = parent_node;
    } else {
      grandp_node->right = parent_node;
    }
    grandp_node = get_parent_node_without_stack(root_node, parent_node);
    child_node = check_color_and_modify(grandp_node, parent_node);
    if (child_node == root_node) {
      return root_node;
    }
  }

  // RL型，孙节点在左子树，子节点在右子树，先子节点左旋，再父节点右旋
  if (lr_child == RIGHT_NODE && lr_gchild == LEFT_NODE) {
    if (parent_node == root_node) {
      root_node = right_rotate_then_left(parent_node, child_node);
      return root_node;
    }
    parent_node = right_rotate_then_left(parent_node, child_node);
    if (lr_parent == LEFT_NODE) {
      grandp_node->left = parent_node;
    } else {
      grandp_node->right = parent_node;
    }
    grandp_node = get_parent_node_without_stack(root_node, grandp_node);
    child_node = check_color_and_modify(grandp_node, parent_node);
    if (child_node == root_node) {
      return root_node;
    }
  }
  return root_node;
}

// 插入节点的几种情况，红黑树插入的节点(grandchild_node)一定是红色，所以grandchild_node一定是红色
// 红黑树插入节点之前一定是符合红黑树特点的（平衡的，没有连续的两个红色节点），所以只有插入位置的节点（child_node）也是红色才需要调整，其他位置直接插入即可。
// child_node是红色，那么根据红黑树的特点parent_node一定是黑色，插入的位置可能是parent_node的左子树或者右子树，先看插入在parent_node左子树的情况
// 1.插入的节点比左子树小（child_node）（LL型），插入为左子树的左节点child_node->left(grandchild_node)，插入后出现连续的两个红色节点，需要调整，针对parent_node进行右旋转，
// 然后child_node被旋转到父节点位置，parent_node变成child_node的右节点，child_node和parent_node颜色交换；（还需要将parent_node变成红色，child_node变成黑色）；
// 2.插入的节点比左子树大（child_node）（LR型），插入为左子树的右节点child_node->right（right_grandchild_node）,插入后也是连续的两个红色节点，先将child_node进行左旋转，
// right_grandchild_node和child_node互换位置（变成LL型），再以parent_node为轴进行右旋转，跟上面的步骤一样，将parent_node变成红色，child_node位置变成right_grandchild_node
// 所以right_grandchild_node要变成黑色；
// 3.插入的节点比右子树大（RR型），插入为右子树的右节点right_grandchild_node，插入后出现连续两个红色节点，以parent_node为轴左旋转，
// 将parent_node变成红色，child_node变成黑色；
// 4.插入的节点比右子树小（RL型），插入为有子树的左节点left_grandchild_node，先以child_node为轴进行右旋转，right_grandchild_node和child_node互换位置（变成RR型），
// 然后再以parent_node左旋转，将parent_node变成红色，right_grandchild_node变成黑色；
// 5.不管插入在parent_node的左子树还是右子树，只要parent_node的左右子树都是红色，只需要将左右子树都变成黑色，parent_node变成红色就行了，然后可能会破坏
// 红黑树的平衡，将parent_node设置为新的需要检查的节点（视为新插入的节点），进一步向上回溯看是否有两个连续的红色节点，进行旋转或者变色转换，直至上升到根根节点(root_node)，
// 如果回溯的结果是要将根节点变为红色，不采取任何操作，调整结束。
// 如果一直向上到根节点，根节点无需变红，保持黑色，整个红黑树依然是平衡的，不会有两个连续的红色节点。
// 6.对于子节点中没有包含指向父节点指针的红黑树，如何找到parent_node，child_node和grandchild_node就是关键所在了。
TreeNode *insert_tree_node(TreeNode *start_node, TreeNode *inst_node) {
  TreeNode *current_node = start_node;

  if (root_node == NULL) {
    root_node = inst_node;
    root_node_bak = root_node;
    root_node->node_color = BLACK_NODE;
    return root_node;
  }
  if (root_node->tree_data == NULL) {
    root_node->tree_data = inst_node->tree_data;
    return root_node;
  }
  if (start_node == NULL || start_node->tree_data == NULL) {
    return root_node;
  }
  if (inst_node == NULL) {
    return root_node;
  }

  // 未给left_or_right赋初始值的时候，编译器默认赋值为N_EQUAL；
  CompareResult left_or_right;
  TreeNode *current_node_parent = NULL;

  while (current_node != NULL) {
    left_or_right = compare_node(current_node, inst_node, compare_node_by_name);
    if (left_or_right == N_SMALLER) {
      if (current_node->left == NULL) {
        current_node->left = inst_node;
        break;
      }
      current_node_parent = current_node;
      current_node = current_node->left;
    } else if (left_or_right == N_GREATER) {
      if (current_node->right == NULL) {
        current_node->right = inst_node;
        break;
      }
      current_node_parent = current_node;
      current_node = current_node->right;
    } else if (left_or_right == N_EQUAL) {
      log_e("Node already exist in the tree, cannot insert node.");
      return root_node;
    }
  }
  root_node = check_color_and_modify(current_node, inst_node);
  return root_node;
}

TreeNode *insert_node(TreeNode *insert_node) {
  root_node = insert_tree_node(root_node, insert_node);
  return root_node;
}

// 删除某个节点的子树中最小的节点（即以这个节点为根节点的树的最左边的节点）
TreeNode *delete_tree_node_min(TreeNode *start_node) {
  if (start_node == NULL) {
    return NULL;
  }

  if (start_node->left == NULL) {
    return start_node->right;
  }
  start_node->left = delete_tree_node_min(start_node->left);
  return start_node;
}

// 删除某个节点的子树中最大的节点（即以这个节点为根节点的树的最右边的节点）
TreeNode *delete_tree_node_max(TreeNode *start_node) {
  if (start_node == NULL) {
    return NULL;
  }
  if (start_node->right == NULL) {
    return start_node->left;
  }
  start_node->right = delete_tree_node_max(start_node->right);
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

// 二叉搜索树的删除逻辑（二叉搜索树的Hibbard删除法）
// 1.被删除节点没有子节点（子树），直接删除；
// 2.被删除的节点只有一个左节点，左节点取代被删除节点；
// 3.被删除的节点只有一个右节点，右节点取代被删除节点；
// 4.被删除的节点有左右两个子树，用左子树的最右边的节点（没有子节点），或者右子树的最左边的节点替代被删除节点，这两个节点刚好是中序遍历二叉树时，
// 分别排列在被删除节点前面和后面的节点，所以用这两个节点替代被删除节点也不会打破二叉搜索树的平衡；
// 5.取代被删除的节点要先与树断开连接关系；
// 6.根据二叉搜索树的中间节点大于左边节点，小于右边节点的特性，中序遍历二叉搜索树得到的正好是从小到大排列的一组数据，上一步就是用排列在被删除节点前后的两个节点替代它；

// 基于二叉搜索树的删除逻辑进行红黑树的删除
// 1.被删除节点没有子节点，有五种情况：
//  1.1被删除节点为红色，父节点为黑色，不影响树的平衡，直接删除；
//  1.2被删除节点del为黑色（在父节点p的左子树），父节点为红色，违反了红黑树的各子树黑色节点数目相同的规则，需要调整；
//   （1）兄弟节点bro，bro只有一个左子节点（bro-l），bro右旋，bro和bro-l颜色互换，再按照1.2.2的步骤进行调整；
//   （2）兄弟节点bro，bro只有一个右子节点（bro-r），p左旋，bro染红，p和bro-r染黑；
//   （3）兄弟节点bro，bro有左(bro-l)右(bro-r)两个子节点，同1.2.2；
//   （4）兄弟节点bro，bro没有子节点，bro染红，p染黑（p和bro交换颜色）；
//   （5）没有兄弟节点，也就是红色的父节点只有一个黑色子节点，这不符合红黑树的特性（违反了所有子树的黑色节点数目相同的规则），不需要考虑这种情况；
//  1.3被删除节点del为黑色（在父节点p的右子树），父节点为黑色，违反了红黑树的各子树黑色节点数目相同的规则，需要调整；
//    （1）兄弟节点bro为红色，bro的右子树（bro-r）没有子节点，p节点右旋（bro染黑，p染红），p和bro-r颜色交换；
//    （2）兄弟节点bro为红色，bro的右子树（bro-r，黑色）有一个左子节点（bro-r-l），p右旋（bro染黑，p染红），p右旋，bro-r节点染红，bro-r-l和p节点染黑；
//    （3）兄弟节点bro为红色，bro的右子树（bro-r，黑色）有一个右子节点（bro-r-r），bro-r左旋（bro-r和bro-r-r颜色互换），就转变成了1.3.2中的情况了；
//    （4）兄弟节点bro为红色，bro节点的右子树（bro-r，黑色）有左（bro-r-l）右（bro-r-r）两个子节点，同1.3.2中的情况；
//    总结：兄弟节点为红色，被删除节点在右子树的情况下，兄弟节点的左子树有无节点不影响删除后对树的调整，只有兄弟节点的右子树的子节点会影响树的调整；
//    （5）兄弟节点bro为黑色，bro没有子节点（双黑节点场景），递归向上来调平红黑树，先将bro染红，递归的思路为设置p为虚拟删除的节点（即将p作为x节点一样的性质的待删除节点），
//    然后看是属于已有这些场景的哪种情况，进行节点旋转和颜色变换；
//    （6）兄弟节点bro为黑色，bro只有一个左子节点（bro-l，红色），p右旋，bro-l染黑；
//    （7）兄弟节点bro为黑色，bro只有一个右子节点（bro-r，红色），bro左旋（bro与bro-r的颜色互换），就转变成了上面1.3.6的情况了；
//    （8）兄弟节点bro为黑色，bro有左（bro-l）右（bro-r）两个子节点，p右旋，bro-l染黑，同上面1.3.6；
//     总结：
//  1.4被删除节点del为黑色（在父节点p的右子树），父节点为红色；
//    （1）兄弟节点bro，bro只有一个左节点（bro-l），与1.2.2互为镜像，旋转方向相反，p右旋，bro染红，p和bro-l染黑；
//    （2）兄弟节点bro，bro只有一个右节点（bro-r），与1.2.1互为镜像，bro左旋，bro染红，bro-r染黑，再按照1.4.1的步骤调整；
//    （3）兄弟节点bro，有左（bro-l）右（bro-r）两个子节点，同1.4.1；；
//    （4）兄弟节点没有子节点，同1.2.4；
//  1.5被删除的节点del为黑色（在父节点p的左子树），父节点p为黑色；
//    （1）兄弟节点bro为红色，bro的左子树（bro-l）只有左节点bro-l-l，bro-l右旋，bro-l和bro-l-l颜色互换，转换成1.5.2的情形；
//    （2）兄弟节点bro为红色，bro的左子树（bro-l）只有右节点bro-l-r，p左旋，bro染黑，p染红，p左旋，bro-l染红，p和bro-l-r染黑；
//    （3）兄弟节点bro为红色，bro的左子树（bro-l）没有子节点，父节点p左旋，p和bro交换颜色（p染红，bro染黑），p和bro-l交换颜色（p染黑，bro-l染红）；
//    （4）兄弟节点bro为红色，bro的左子树（bro-l）有左（bro-l-l）右（bro-l-r）两个子节点，同1.5.2；
//    总结：兄弟节点为红色，bro的右子树是否有子节点不影响删除节点后的调整，只有bro的左子树的节点会影响树的调整；
//    （5）兄弟节点bro为黑色，bro没有子节点（双黑节点场景），bro染红，再将父节点假设为被删除节点，看看属于删除场景中的哪种情况，继续调整，一直到根节点或者红色的父节点结束；
//    （6）兄弟节点bro为黑色，bro有左子树（bro-l），bro右旋（bro和bro-l颜色互换）,转变成1.5.7场景；
//    （7）兄弟节点bro为黑色，bro有右子树（bro-r），p左旋，bro-r染黑；
//    （8）兄弟节点bro为黑色，bro有左（bro-l）右（bro-r）两个子树，同1.5.7场景；
// 分析与合并：
// 场景一：被删除节点del为黑色，没有子节点，在父节点的左子树，兄弟节点为黑色；
// （1）1.2.2和1.5.7，p和bro交换颜色，p左旋，bro-r染黑；
// （2）1.2.1和1.5.6，bro右旋，bro和bro-l交换颜色，p与p-r（此时p的右子节点变成了bro-l，bro成为bro-l的右节点）交换颜色，转换成（1）；
// （3）1.2.3和1.5.8，同（1）；
// （4）1.2.4和1.4.4，p和bro交换颜色；
// （5）1.5.5，父节点（p），左（bro-l）右（bro-r）子节点均为黑色，左右子节点均无子节点，删除左右子节点中的任意一个，此种情况称之为双黑，就是将被删除的黑色节点
// 的黑色继续上移到父节点，然后将被删除节点的兄弟节点染红，父节点带着两个黑色，将父节点假设为被删除节点（带着被删除节点的黑色），不考虑已经变成红色的兄弟节点
// 的存在，看父节点的删除属于哪种情况；
// 场景二：被删除节点del为黑色，没有子节点，在父节点的左子树，兄弟节点为红色；
// （1）1.5.1，p和bro交换颜色，p左旋，转换成场景一的（2）；
// （2）1.5.2，p和bro交换颜色，p左旋，转换成场景一的（1）；
// （3）1.5.3，p和bro交换颜色，p左旋，转换成场景一的（4）；
// （4）1.5.4，p和bro交换颜色，p左旋，转换成场景一的（3）；
// 场景三：被删除节点del为黑色，没有子节点，在父节点的右子树，兄弟节点为黑色；
// （1）1.3.6和1.4.1，p和bro交换颜色，p右旋，bro-l染黑；
// （2）1.3.7和1.4.2，bro和bro-r交换颜色，bro左旋，p与p-l交换颜色，转换成（1）；
// （3）1.3.8和1.4.3，同（1）；
// （4）1.3.5，双黑场景，同1.5.5；
// 场景四：被删除节点del为黑色，没有子节点，在父节点的右子树，兄弟节点为红色；
// （1）1.3.1，p和bro交换颜色，p右旋，bro-r成为del的兄弟节点，且都是黑节点，他们的父节点是红色，转换成场景一的（4）；
// （2）1.3.2，p和bro交换颜色，p右旋，转换成场景三的（1）；
// （3）1.3.3，p和bro交换颜色，p右旋，转换成场景三的（2）；
// （4）1.3.4，p和bro交换颜色，p右旋，转换成场景三的（3）；
// 2.被删除的节点只有一个左子树，被删除的节点只能是黑色，左节点只能是红色，其他情况不符合红黑树特性，左节点取代被删除节点，并将左节点染黑；
// 3.被删除的节点只有一个右子树，被删除的节点只能是黑色，右节点只能是红色，其他情况不符合红黑树特性，右节点取代被删除节点，并将右节点染黑；
// 4.被删除的节点有左右两个子树，后继节点替换被删除节点（也可以使用前驱节点），然后删除后继节点，问题就变成了删除后继节点了，后继节点没有左子树
// （如果是前驱节点替代被删除节点，则是前驱节点没有右子树），问题就又简化成上面第一种或者第三种情况。
//
// 红黑树删除场景整理：
// 1.被删除节点（del）有左右两个子节点，后继节点替代被删除节点，后继节点一定是没有左子树的，删除操作转化成删除没有子节点或者只有一个子节点的操作（见下方）；
// 2.被删除节点（del）只有一个子节点，根据红黑树特性，被删除节点只能是黑色，后继节点必然是红色，有左右子节点两种情况：
//  2.1后继节点在左子节点，左节点取代被删除的节点，并染黑；
//  2.2后继节点在右子节点，右节点取代被删除的节点，并染黑；
// 3.被删除的节点（del）没有子节点，此种包含的情况最多，不仅跟被删除节点的颜色，节点所在的是左边子节点还是右边子节点有关，还与兄弟节点的颜色有关，
// 甚至会跟父节点与兄弟节点的子节点的颜色有关，有如下几种场景：
//  3.1被删除节点为红色，红色节点删除不影响红黑树的特征，直接删除；
//  3.2被删除节点为黑色，为父节点（p）的左子节点，根据兄弟节点（bro）的颜色区分红黑，又分为如下几种情况：
//    3.2.1兄弟节点为黑色，根据兄弟节点的子节点的情况，又分为如下几种情况：
//      3.2.1.1兄弟节点没有子节点：
//        3.2.1.1.1父节点为红色，父节点和兄弟节点交换颜色；
//        3.2.1.1.2父节点为黑色（双黑场景）,此时被删除节点为黑色，其兄弟节点和父节点均为黑色；
//          （1）设置父节点为双黑节点（节点颜色取特殊值，比如灰色来表示）；
//          （2）双黑节点可以视作一个虚假的要被删除的节点，且该节点没有子节点（即便有子节点也是假设子节点不存在），按照节点删除的规则对红黑树进行调整，调整规则如下：
//              a.如果双黑节点是根节点，根节点保持黑色，双黑取消，调整完成；
//              b.双黑节点的兄弟节点没有红色子节点，将双黑节点的兄弟节点变为红色，设置双黑节点的父节点为新的双黑节点，继续向上判断；
//              c.双黑节点的兄弟节点为红色，参考兄弟节点为红色的场景进行调整（见3.2.2规则）；
//              d.双黑节点的兄弟节点为黑色，参考兄弟节点为黑色的场景进行调整（见3.2.1.2等几个规则）；
//      3.2.1.2兄弟节点右子节点（bro-r）为红色（RR型），父节点（p）和兄弟节点（bro）交换颜色，父节点左旋，旋转后的兄弟节点的右子节点染黑；
//      3.2.1.3兄弟节点左子节点（bro-l）为红色（RL），兄弟节点（bro）和兄弟节点的左子节点（bro-l）交换颜色，兄弟节点右旋，转换成3.2.1.2；
//      3.2.1.4兄弟节点有左（bro-l）右（bro-r）两个节点为红色，同3.2.1.2；
//    3.2.2兄弟节点为红色，变换的核心思想是通过染色和旋转，将删除节点的兄弟节点为红色的转换成删除节点的兄弟节点为黑色，复用已有的删除方案，分为如下几种情况：
//      3.2.2.1兄弟节点的左节点（bro-l）没有子节点，父节点（p）和兄弟节点（bro）交换颜色，父节点左旋，转换成3.2.1.1.1；
//      3.2.2.2兄弟节点的左节点（bro-l）只有左节点（bro-l-l），父节点和兄弟节点交换颜色，父节点左旋，变成3.2.1.3；
//      3.2.2.3兄弟节点的左节点（bro-l）只有右节点（bro-l-r），父节点和兄弟节点交换颜色，父节点左旋，变成3.2.1.2；
//      3.2.2.4兄弟节点的左节点（bro）有左右两个子子节点，父节点和兄弟节点交换颜色，父节点左旋，变成3.2.1.4，同3.2.2.3，最后均按照3.2.1.2进行调整；
//      注：兄弟节点为红色，其必有左右两个子节点，bro的右节点以及右节点是否有子节点不影响树的调整，所以只考虑兄弟节点的左节点情况；
//  3.3被删除节点为黑色，为父节点的右子节点
//    3.3.1兄弟节点为黑色
//      3.3.1.1兄弟节点没有子节点
//        3.3.1.1.1父节点为红色，父节点和兄弟节点交换颜色，同3.2.1.1.1；
//        3.3.1.1.2父节点为黑色（双黑场景），同3.2.1.1.2；
//      3.3.1.2兄弟节点左子节点（bro-l）为红色（LL型），父节点（p）和兄弟节点（bro）交换颜色，父节点右旋，旋转后的兄弟节点的左子节点染黑；
//      3.3.1.3兄弟节点右子节点（bro-r）为红色（LR型），兄弟节点（bro）和兄弟节点的子节点（bro-r）交换颜色，bro左旋，转换成3.3.1.2；
//      3.3.1.4兄弟节点有左（bro-l）右（bro-r）两个子节点均为红色，同3.3.1.2；
//    3.3.2兄弟节点为红色
//      3.3.2.1兄弟节点的右节点（bro-r）没有子节点，父节点和兄弟节点交换颜色，父节点右旋，变成3.3.1.1.1；
//      3.3.2.2兄弟节点的右节点只有左节点（bro-r-l），父节点和兄弟节点交换颜色，父节点右旋，变成3.3.1.2；
//      3.3.2.3兄弟节点的右节点只有右节点（bro-r-r），父节点和兄弟节点交换颜色，父节点右旋，变成3.3.1.3；
//      3.3.2.4兄弟节点的右节点有左右两个子节点，父节点和兄弟节点交换颜色，父节点右旋，变成3.3.1.4，同3.3.2.2,最后均按照3.3.1.2进行调整；
//      注：被删除节点在为父节点的右子节点，兄弟节点为红色，bro的左节点及左节点是否有子节点不影响树的调整；

// 树的两个节点交换，采用交换内容的方式，就是交换节点这个结构体里面的data，以及right，left指针，不改变树的结构，实现相对简单
TreeNode *swap_node(TreeNode *origin_node, TreeNode *replace_node) {
  void *temp_data = origin_node->tree_data;
  assert(origin_node != NULL);
  assert(replace_node != NULL);
  origin_node->tree_data = replace_node->tree_data;
  replace_node->tree_data = temp_data;
  if (replace_node != NULL) {
    return replace_node;
  }
  return replace_node;
}

// 交换两个节点的颜色
void swap_node_color(TreeNode *first_node, TreeNode *second_node) {
  NODE_COLOR temp_node_color = first_node->node_color;
  first_node->node_color = second_node->node_color;
  second_node->node_color = temp_node_color;
}

// 节点左旋，节点颜色不随旋转产生变化
TreeNode *left_rotate_without_color_change(TreeNode *start_node) {
  if (start_node == NULL) {
    return NULL;
  }
  TreeNode *start_node_bak = start_node;
  start_node = start_node->right;
  start_node_bak->right = start_node->left;
  start_node->left = start_node_bak;
  return start_node;
}

// 节点右旋，节点颜色不随旋转产生变化
TreeNode *right_rotate_without_color_change(TreeNode *start_node) {
  if (start_node == NULL) {
    return NULL;
  }
  TreeNode *start_node_bak = start_node;
  start_node = start_node->left;
  start_node_bak->left = start_node->right;
  start_node->right = start_node_bak;
  return start_node;
}

// 2.1, 2.2（没有使用该函数）
//  被删除节点只有一个子节点，根据红黑树的特性，子节点一定是红色，被删除节点为黑色
//  子节点替代被删除节点即可，颜色变为黑色，以补充被删除的黑色节点
TreeNode *delete_single_child_node(TreeNode *del_node) {
  if (del_node == root_node) {
    if (del_node->left != NULL) {
      root_node = del_node->left;
      return root_node;
    } else if (del_node->right != NULL) {
      root_node = del_node->right;
      return root_node;
    }
  }
  TreeNode *parent_node = get_parent_node_without_stack(root_node, del_node);
  LeftOrRight left_or_right_child =
      node_is_left_or_right(parent_node, del_node);
  bool left_child_null = false;
  bool right_child_null = false;
  if (del_node->left == NULL && del_node->right != NULL) {
    left_child_null = true;
  }
  if (del_node->left != NULL && del_node->right == NULL) {
    right_child_null = true;
  }
  if (left_or_right_child == LEFT_NODE) {
    if (left_child_null) {
      parent_node->left = del_node->right;
      del_node->right->node_color = BLACK_NODE;
    } else if (right_child_null) {
      parent_node->left = del_node->left;
      del_node->left->node_color = BLACK_NODE;
    }
  } else if (left_or_right_child == RIGHT_NODE) {
    if (left_child_null) {
      parent_node->right = del_node->right;
      del_node->right->node_color = BLACK_NODE;
    } else if (right_child_null) {
      parent_node->right = del_node->left;
      del_node->left->node_color = BLACK_NODE;
    }
  }
  return parent_node;
}

// 3.1，被删除的节点没有子节点，且为红色，直接删除，不影响红黑树特性
TreeNode *delete_tree_node_is_red_without_child(TreeNode *parent_node,
                                                TreeNode *del_node,
                                                LeftOrRight node_branch) {
  if (del_node->node_color == RED_NODE) {
    if (node_branch == LEFT_NODE) {
      parent_node->left = NULL;
    } else if (node_branch == RIGHT_NODE) {
      parent_node->right = NULL;
    }
  }
  return parent_node;
}

// 3.2.1.1.1
//  被删除的节点为黑色，父节点为红色，兄弟节点为黑色，且没有子节点
TreeNode *
black_brother_node_without_child_and_red_father(TreeNode *parent_node,
                                                TreeNode *brother_node) {
  TreeNode *temp_node = NULL;
  if (parent_node->node_color == RED_NODE) {
    swap_node_color(parent_node, brother_node);
  }
  return parent_node;
}

// 获取兄弟节点
TreeNode *get_brother_node(TreeNode *origin_node, TreeNode *brother_node) {
  TreeNode *parent_node = NULL;
  parent_node = get_parent_node_without_stack(root_node, origin_node);
  // 没有获取到parent_node，为根节点；
  if (parent_node == NULL) {
    return NULL;
  }
  LeftOrRight node_branch = node_is_left_or_right(origin_node, parent_node);
  if (node_branch == LEFT_NODE && parent_node->right != NULL) {
    brother_node = parent_node->right;
  } else if (node_branch == RIGHT_NODE && parent_node->left != NULL) {
    brother_node = parent_node->left;
  } else {
    brother_node = NULL;
  }
  return brother_node;
}

// 3.2.1.2
//  被删除节点在左子树，被删除节点的兄弟节点为黑色，兄弟节点只有右子节点且为红色，RR型
TreeNode *black_brother_node_RR(TreeNode *parent_node, TreeNode *brother_node) {
  swap_node_color(parent_node, brother_node);
  TreeNode *parent_node_bak = parent_node;
  parent_node = left_rotate_without_color_change(parent_node);
  parent_node->right->node_color = BLACK_NODE;
  return parent_node;
}

// 3.2.1.3
//  被删除节点在左子树，被删除节点的兄弟节点为黑色，兄弟节点只有左子节点且为红色，RL型
TreeNode *black_brother_node_RL(TreeNode *parent_node, TreeNode *brother_node) {
  // 兄弟节点左子节点为红色
  LeftOrRight brother_l_r = node_is_left_or_right(brother_node, parent_node);
  swap_node_color(brother_node, brother_node->left);
  TreeNode *grand_parent = NULL;
  LeftOrRight parent_l_r = -1;
  TreeNode *parent_node_bak = parent_node;
  grand_parent = get_parent_node_without_stack(root_node, parent_node);
  parent_l_r = node_is_left_or_right(parent_node, grand_parent);
  parent_node->right = right_rotate_without_color_change(parent_node->right);
  parent_node = black_brother_node_RR(parent_node, parent_node->right);
  return parent_node;
}

// 3.2.1.2, 3.2.1.3, 3.2.1.4
// 被删除节点在左子树，兄弟节点为黑色
TreeNode *delete_node_at_left_and_the_brother_node_is_black(
    TreeNode *parent_node, TreeNode *brother_node, TreeNode *del_node) {
  LeftOrRight parent_l_r = -1;
  TreeNode *grand_parent = NULL;
  TreeNode *parent_node_bak = parent_node;
  if (brother_node->left == NULL && brother_node->right == NULL) {
    if (parent_node->node_color == RED_NODE) {
      parent_node = black_brother_node_without_child_and_red_father(
          parent_node, brother_node);
    } else {
      parent_node =
          black_brother_node_double_black(parent_node, brother_node, del_node);
    }
  } else if (brother_node->right != NULL &&
             brother_node->right->node_color == RED_NODE) {
    parent_node = black_brother_node_RR(parent_node, brother_node);
  } else {
    parent_node = black_brother_node_RL(parent_node, brother_node);
  }
  if (parent_node_bak == root_node) {
    root_node = parent_node;
    grand_parent = root_node;
  } else {
    grand_parent = get_parent_node_without_stack(root_node, parent_node_bak);
    parent_l_r = node_is_left_or_right(parent_node_bak, grand_parent);
    if (parent_l_r == LEFT_NODE) {
      grand_parent->left = parent_node;
    } else if (parent_l_r == RIGHT_NODE) {
      grand_parent->right = parent_node;
    }
  }
  return parent_node;
}

// 3.2.2.1, 3.2.2.2, 3.2.2.3, 3.2.2.4
// 被删除节点在左子树，兄弟节点为红色
TreeNode *delete_node_at_left_and_the_brother_node_is_red(
    TreeNode *parent_node, TreeNode *brother_node, TreeNode *del_node) {
  if (brother_node == NULL) {
    log_i("brother node is null, please check.");
    return root_node;
  }
  LeftOrRight brother_l_r = -1;
  LeftOrRight parent_l_r = -1;
  TreeNode *grand_parent = NULL;
  TreeNode *parent_node_bak = parent_node;
  swap_node_color(parent_node, brother_node);
  if (parent_node != root_node) {
    grand_parent = get_parent_node_without_stack(root_node, parent_node);
    parent_l_r = node_is_left_or_right(parent_node, grand_parent);
  }
  parent_node = left_rotate_without_color_change(parent_node);
  if (root_node == parent_node_bak) {
    root_node = parent_node;
  } else {
    if (parent_l_r == LEFT_NODE) {
      grand_parent->left = parent_node;
    } else {
      grand_parent->right = parent_node;
    }
  }
  brother_node = get_brother_node(del_node, brother_node);
  parent_node = get_parent_node_without_stack(root_node, brother_node);
  grand_parent = get_parent_node_without_stack(root_node, parent_node);
  parent_l_r = node_is_left_or_right(parent_node, grand_parent);
  parent_node = delete_node_at_left_and_the_brother_node_is_black(
      parent_node, brother_node, del_node);
  if (parent_l_r == LEFT_NODE) {
    grand_parent->left = parent_node;
  } else {
    grand_parent->right = parent_node;
  }
  return parent_node;
}

// 3.3.1.2
//  被删除节点在右子树，被删除节点的兄弟节点为黑色，兄弟节点只有左子节点且为红色，LL型
TreeNode *black_brother_node_LL(TreeNode *parent_node, TreeNode *brother_node) {
  TreeNode *parent_node_bak = parent_node;
  // 兄弟节点的左子节点为红色
  swap_node_color(parent_node, brother_node);
  parent_node = right_rotate_without_color_change(parent_node);
  parent_node->left->node_color = BLACK_NODE;
  return parent_node;
}

// 3.3.1.3
//  被删除节点在右子树，被删除节点的兄弟节点为黑色，兄弟节点只有右子节点且为红色，LR型
TreeNode *black_brother_node_LR(TreeNode *parent_node, TreeNode *brother_node) {
  // 兄弟节点的右子节点为红色
  swap_node_color(brother_node, brother_node->right);
  TreeNode *grand_parent = NULL;
  LeftOrRight parent_l_r = -1;
  TreeNode *parent_node_bak = parent_node;
  grand_parent = get_parent_node_without_stack(root_node, parent_node);
  parent_l_r = node_is_left_or_right(parent_node, grand_parent);
  parent_node->left = left_rotate_without_color_change(parent_node->left);
  parent_node = black_brother_node_LL(parent_node, parent_node->left);
  return parent_node;
}

// 3.3.1.2, 3.3.1.3, 3.3.1.4
// 被删除节点在右子树，和兄弟节点均为黑色，兄弟节点的子节点有三种情况，只有一个左子节点为红色和左右子节点均为红色的操作一样
// 还有一个就是只有一个右子节点为红色这三种情况，先判断只有一个右子节点为红色的状况，简化判断条件
TreeNode *delete_node_at_right_and_the_brother_node_is_black(
    TreeNode *parent_node, TreeNode *brother_node, TreeNode *del_node) {
  LeftOrRight parent_l_r = -1;
  TreeNode *grand_parent = NULL;
  TreeNode *parent_node_bak = parent_node;
  if (brother_node->left == NULL && brother_node->right == NULL) {
    if (parent_node->node_color == RED_NODE) {
      parent_node = black_brother_node_without_child_and_red_father(
          parent_node, brother_node);
    } else {
      parent_node =
          black_brother_node_double_black(parent_node, brother_node, del_node);
    }
  }
  if (brother_node->left != NULL &&
      brother_node->left->node_color == RED_NODE) {
    parent_node = black_brother_node_LL(parent_node, brother_node);
  } else {
    parent_node = black_brother_node_LR(parent_node, brother_node);
  }
  if (parent_node_bak == root_node) {
    root_node = parent_node;
    grand_parent = root_node;
  } else {
    grand_parent = get_parent_node_without_stack(root_node, parent_node_bak);
    parent_l_r = node_is_left_or_right(parent_node_bak, grand_parent);
    if (parent_l_r == LEFT_NODE) {
      grand_parent->left = parent_node;
    } else if (parent_l_r == RIGHT_NODE) {
      grand_parent->right = parent_node;
    }
  }
  return parent_node;
}

// 3.3.2.1, 3.3.2.2, 3.3.2.3, 3.3.2.4
// 被删除节点在右子树，兄弟节点为红色，兄弟节点的右节点的子节点对调整有影响
TreeNode *delete_node_at_right_and_the_brother_node_is_red(
    TreeNode *parent_node, TreeNode *brother_node, TreeNode *del_node) {
  if (brother_node == NULL) {
    log_i("brother node is null, please check.");
    return root_node;
  }
  LeftOrRight brother_l_r = -1;
  LeftOrRight parent_l_r = -1;
  TreeNode *grand_parent = NULL;
  TreeNode *parent_node_bak = parent_node;
  if (parent_node != root_node) {
    grand_parent = get_parent_node_without_stack(root_node, parent_node);
    parent_l_r = node_is_left_or_right(parent_node, grand_parent);
  }
  swap_node_color(parent_node, brother_node);
  parent_node = right_rotate_without_color_change(parent_node);
  if (parent_node_bak == root_node) {
    root_node = parent_node;
  } else {
    if (parent_l_r == LEFT_NODE) {
      grand_parent->left = parent_node;
    } else {
      grand_parent->right = parent_node;
    }
  }
  brother_node = get_brother_node(del_node, brother_node);
  parent_node = get_parent_node_without_stack(root_node, del_node);
  grand_parent = get_parent_node_without_stack(root_node, parent_node);
  parent_l_r = node_is_left_or_right(parent_node, grand_parent);
  if (parent_l_r == LEFT_NODE) {
    parent_node = delete_node_at_right_and_the_brother_node_is_black(
        parent_node, brother_node, del_node);
    grand_parent->left = parent_node;
  } else {
    parent_node = delete_node_at_right_and_the_brother_node_is_black(
        parent_node, brother_node, del_node);
    grand_parent->right = parent_node;
  }
  return parent_node;
}

// 3.2.1.1.2（双黑节点场景）
//  被删除的节点为黑色，在左子树，没有子节点，其父节点和兄弟节点均为黑色
//  由于被删除节点无法从兄弟节点或者兄弟节点的子节点那里借到黑色，只能将双黑向父节点上转移，继续看父节点的兄弟节点以及父节点兄弟节点的子节点是否有红色可借用
//  最终解决少了一个黑色节点的问题。
TreeNode *black_brother_node_double_black(TreeNode *parent_node,
                                          TreeNode *brother_node,
                                          TreeNode *del_node) {
  TreeNode *double_black_node = parent_node;
  TreeNode *double_black_brother_node = brother_node;
  // parent_node->node_color = DOUBLE_BLACK_NODE;
  brother_node->node_color = RED_NODE;
  if (parent_node == root_node) {
    parent_node->node_color = BLACK_NODE;
    return root_node;
  }

  TreeNode *grandp_node = get_parent_node_without_stack(root_node, parent_node);
  /*
  if (grandp_node != NULL && grandp_node->node_color == RED_NODE) {
    grandp_node->node_color = BLACK_NODE;
    return parent_node;
  }*/
  brother_node = get_brother_node(parent_node, brother_node);
  LeftOrRight parent_l_r = node_is_left_or_right(parent_node, grandp_node);
  if (brother_node->node_color == BLACK_NODE) {
    if (grandp_node->node_color == BLACK_NODE && brother_node->left == NULL &&
        brother_node->right == NULL) {
      parent_node = black_brother_node_double_black(grandp_node, brother_node,
                                                    parent_node);
    } else if (brother_node->left->node_color == BLACK_NODE &&
               brother_node->right->node_color == BLACK_NODE) {
      brother_node->node_color = RED_NODE;
      parent_node = black_brother_node_double_black(grandp_node, brother_node,
                                                    parent_node);
    }
    if (parent_node == root_node || parent_node->node_color == RED_NODE) {
      parent_node->node_color = BLACK_NODE;
      return parent_node;
    }
    if (parent_l_r == LEFT_NODE) {
      delete_node_at_left_and_the_brother_node_is_black(
          grandp_node, brother_node, parent_node);
    } else {
      delete_node_at_right_and_the_brother_node_is_black(
          grandp_node, brother_node, parent_node);
    }

  } else if (brother_node->node_color == RED_NODE) {
    if (parent_l_r == LEFT_NODE) {
      delete_node_at_left_and_the_brother_node_is_red(grandp_node, brother_node,
                                                      parent_node);
    } else {
      delete_node_at_right_and_the_brother_node_is_red(
          grandp_node, brother_node, parent_node);
    }
  }
  return parent_node;
}

// 被删除的节点有左右两个子节点，找到前驱或者后继节点替代被删除节点，转化成被删除节点没有子节点或者只有一个子节点的情况；
// 使用former_node表示前驱节点（min_tree_node），behind_node表示后继节点（max_tree_node），这里采用后继节点作为替代被删除节点
// 采用先调整，调整完成后交换被删除节点和后继节点，然后删除后继节点的做法，以降低程序复杂性
TreeNode *delete_tree_node(TreeNode *start_node, TreeNode *del_node) {
  CompareResult node_cmp =
      compare_node(start_node, del_node, compare_node_by_name);
  if (start_node == NULL || start_node->tree_data == NULL) {
    if (node_cmp != N_EQUAL) {
      log_i("The node going to delete not found in the tree.");
    }
    return NULL;
  }
  if (del_node->tree_data == NULL) {
    log_e("The node plan to delete is NULL.");
    return NULL;
  }

  NODE_COLOR del_node_color = del_node->node_color;
  TreeNode *del_node_parent = NULL;
  TreeNode *del_node_brother = NULL;
  TreeNode *del_node_parent_bak = NULL;
  TreeNode *del_node_brother_bak = NULL;
  TreeNode *behind_node_parent = NULL;
  TreeNode *behind_node_brother = NULL;
  TreeNode *behind_node = NULL;
  LeftOrRight behind_node_l_r = -2;
  TreeNode *del_node_bak = NULL;
  TreeNode *behind_node_bak = NULL;

  // 被删除节点为根节点，这里只处理没有子节点和有一个子节点的情况，两个子节点需要更多的操作，另外处理
  if (del_node == root_node) {
    if (del_node->left == NULL && del_node->right == NULL) {
      root_node = NULL;
      return root_node;
    } else if (del_node->left != NULL && del_node->right == NULL) {
      root_node = del_node->left;
      root_node->node_color = BLACK_NODE;
      return root_node;
    } else if (del_node->left == NULL && del_node->right != NULL) {
      root_node = del_node->right;
      root_node->node_color = BLACK_NODE;
      return root_node;
    }
  }

  // 使用后继节点来替代被删除节点（被删除节点右子树的最小节点）
  if (del_node != NULL && del_node->right != NULL) {
    behind_node = min_tree_node(del_node->right);
  }
  if (behind_node == NULL) {
    behind_node = del_node;
  }
  behind_node_parent = get_parent_node_without_stack(root_node, behind_node);
  behind_node_l_r = node_is_left_or_right(behind_node, behind_node_parent);
  // 备份被删除节点数据，后续还要找到完成删除；
  del_node_bak = del_node;
  behind_node_bak = behind_node;

  // 被删除节点有两个子节点的情况，采用后继节点替换被删除节点，转化成只有一个子节点或者没有子节点的情况
  if (del_node->left != NULL && del_node->right != NULL) {
    // 被删除节点有左右两个子节点时，才需要使用后继节点替换被删除节点
    del_node = behind_node;
  }

  LeftOrRight dnb_l_r = -1;
  LeftOrRight del_node_l_r = -1;

  // 被删除节点没有子节点的情况，被删除节点有两个子节点的代码执行完后会，继续执行被删除节点只有一个子节点或者没有子节点的代码，只不过被删除节点变化了,
  // 变成后继节点
  if (del_node->left == NULL && del_node->right == NULL) {
    del_node_parent = get_parent_node_without_stack(root_node, del_node);
    del_node_brother = get_brother_node(del_node, del_node_brother);
    behind_node_brother = get_brother_node(behind_node, behind_node_brother);
    if (del_node_brother != NULL) {
      dnb_l_r = node_is_left_or_right(del_node_brother, del_node_parent);
    }
    del_node_l_r = node_is_left_or_right(del_node, del_node_parent);
    if (del_node->node_color == RED_NODE) {
      // 有两种红色节点，一种是本来要删除的就是无子节点的红色节点，一种是本来要删除有两个子节点的黑色节点，其替代节点为红色节点；
      // 第二种是要交换节点内容的，第一种不需要，不管哪种都可以先交换，第一种自己跟自己交换不影响节点内容
      // 将红色节点的分支类型作为参数传入，避免因为节点值的交换导致在删除函数中再去判断节点分支类型的时候出现错误
      swap_node(del_node_bak, del_node);
      delete_tree_node_is_red_without_child(del_node_parent, del_node,
                                            del_node_l_r);
      return root_node;
    } else if (del_node->node_color == BLACK_NODE &&
               del_node_l_r == LEFT_NODE) {
      if (del_node_brother->node_color == BLACK_NODE) {
        if (del_node_brother->left == NULL && del_node_brother->right == NULL) {
          if (del_node_parent->node_color == RED_NODE) {
            swap_node_color(del_node_parent, del_node_brother);
          } else if (del_node_parent->node_color == BLACK_NODE) {
            black_brother_node_double_black(del_node_parent, del_node_brother,
                                            del_node);
          }
        } else {
          delete_node_at_left_and_the_brother_node_is_black(
              del_node_parent, del_node_brother, del_node);
        }
      } else if (del_node_brother->node_color == RED_NODE) {
        delete_node_at_left_and_the_brother_node_is_red(
            del_node_parent, del_node_brother, del_node);
      }
    } else if (del_node->node_color == BLACK_NODE &&
               del_node_l_r == RIGHT_NODE) {
      if (del_node_brother->node_color == BLACK_NODE) {
        if (del_node_brother->left == NULL && del_node_brother->right == NULL) {
          if (del_node_parent->node_color == RED_NODE) {
            swap_node_color(del_node_parent, del_node_brother);
          } else if (del_node_parent->node_color == BLACK_NODE) {
            black_brother_node_double_black(del_node_parent, del_node_brother,
                                            del_node);
          }
        } else {
          delete_node_at_right_and_the_brother_node_is_black(
              del_node_parent, del_node_brother, del_node);
        }
      } else if (del_node_brother->node_color == RED_NODE) {
        delete_node_at_right_and_the_brother_node_is_red(
            del_node_parent, del_node_brother, del_node);
      }
    }
    // 调整完成开始执行删除操作，被删除节点和后继节点交换节点内容
    TreeNode *behind_node_bak_parent =
        get_parent_node_without_stack(root_node, behind_node_bak);
    LeftOrRight behind_node_bak_l_r =
        node_is_left_or_right(behind_node_bak, behind_node_bak_parent);
    swap_node(del_node_bak, behind_node_bak);
    // 删除后继节点
    if (behind_node_bak->left == NULL && behind_node_bak->right == NULL) {
      if (behind_node_bak_l_r == LEFT_NODE) {
        behind_node_bak_parent->left = NULL;
      } else {
        behind_node_bak_parent->right = NULL;
      }
    }
  } else {
    TreeNode *del_node_bak_parent =
        get_parent_node_without_stack(root_node, del_node_bak);
    LeftOrRight del_node_bak_l_r =
        node_is_left_or_right(del_node_bak, del_node_bak_parent);
    TreeNode *behind_node_bak_parent =
        get_parent_node_without_stack(root_node, behind_node_bak);
    LeftOrRight behind_node_bak_l_r =
        node_is_left_or_right(behind_node_bak, behind_node_bak_parent);
    if (del_node_bak->left != NULL && del_node_bak->right != NULL) {
      swap_node(del_node_bak, behind_node_bak);
      if (behind_node_bak->right != NULL) {
        if (behind_node_bak_l_r == LEFT_NODE) {
          behind_node_bak_parent->left = behind_node_bak->right;
        } else {
          behind_node_bak_parent->right = behind_node_bak->right;
        }
        behind_node_bak->right->node_color = BLACK_NODE;
      } else if (behind_node_bak->left != NULL) {
        if (behind_node_bak_l_r == RIGHT_NODE) {
          behind_node_bak_parent->right = behind_node_bak->left;
        } else {
          behind_node_bak_parent->right = behind_node_bak->left;
        }
        behind_node_bak->left->node_color = BLACK_NODE;
      }
    } else if (del_node_bak->left == NULL && del_node_bak->right != NULL) {
      if (del_node_bak_l_r == LEFT_NODE) {
        del_node_bak_parent->left = del_node_bak->right;
      } else {
        del_node_bak_parent->right = del_node_bak->right;
      }
      del_node_bak->right->node_color = BLACK_NODE;
    } else if (del_node_bak->left != NULL && del_node_bak->right == NULL) {
      if (del_node_bak_l_r == LEFT_NODE) {
        del_node_bak_parent->left = del_node_bak->left;
      } else {
        del_node_bak_parent->right = del_node_bak->left;
      }
      del_node_bak->left->node_color = BLACK_NODE;
    }
  }
  return root_node;
}

void delete_node(TreeNode *delete_node) {
  if (delete_node == NULL) {
    log_e("Node not found.");
  }
  root_node = delete_tree_node(root_node, delete_node);
}

// 将树的所有节点入栈
TreeNode *push_node_to_stack(Stack *in_stack, TreeNode *in_node) {
  if (in_node == NULL) {
    return in_node;
  }
  push_node_to_stack(in_stack, in_node->left);
  push(in_stack, in_node);
  push_node_to_stack(in_stack, in_node->right);
}

// 清空树，并不清空树中的节点所携带的数据，本质就是断开每个节点与左右子树的链接关系，
// 中序遍历一棵树，将遍历的每个节点入栈，然后将每个节点的左右子树都置为NULL，树的每个节点变成孤立的节点
// 最后将root_node置为NULL；
TreeNode *clear_tree(TreeNode *start_node) {
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
                             int *index) {
  if (trav_node == NULL || trav_node->tree_data == NULL) {
    return NULL;
  }
  if (*index < MAX_SIZE) {
    trav_result[(*index)++] = trav_node;
  } else {
    log_e("%s %s", __func__, "node array is fulled.");
    return trav_node;
  }
  if (trav_node->left != NULL) {
    preorder_traversal(trav_node->left, trav_result, index);
  }
  if (trav_node->right != NULL) {
    preorder_traversal(trav_node->right, trav_result, index);
  }
  return root_node;
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
  return root_node;
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
  return root_node;
}

TreeNode *inorder_traversal(TreeNode *trav_node, TreeNode **trav_result,
                            int *index) {
  if (trav_node == NULL || trav_node->tree_data == NULL) {
    return NULL;
  }
  if (trav_node->left != NULL) {
    inorder_traversal(trav_node->left, trav_result, index);
  }
  if (*index < MAX_SIZE) {
    trav_result[(*index)++] = trav_node;
  } else {
    log_e("%s %s", __func__, "node array is fulled.");
    return trav_node;
  }
  if (trav_node->right != NULL) {
    inorder_traversal(trav_node->right, trav_result, index);
  }
  return root_node;
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
  return root_node;
}

TreeNode *postorder_traversal(TreeNode *trav_node, TreeNode **trav_result,
                              int *index) {
  if (trav_node != NULL && trav_node->left != NULL) {
    postorder_traversal(trav_node->left, trav_result, index);
    postorder_traversal(trav_node->right, trav_result, index);
  }
  if (*index < MAX_SIZE) {
    trav_result[(*index)++] = trav_node;
  } else {
    log_e("%s %s", __func__, "node array is fulled.");
    return trav_node;
  }
  if (trav_node == root_node) {
    return root_node;
  }
  return root_node;
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

  return root_node;
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

  return root_node;
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
