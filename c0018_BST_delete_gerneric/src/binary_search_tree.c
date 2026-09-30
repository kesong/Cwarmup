#include "binary_search_tree.h"
#include "../test/test_player.h"
#include <stdlib.h>
#include <string.h>

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
}

int search_tree_node(TreeNode *start_node, TreeNode *search_node,
                     TreeNode **result_node, TreeNode **result_parent_node) {
  TreeNode *current_node = start_node;
  if (start_node == root_node && root_node == NULL) {
    log_e("Tree is empty, please check.");
    return -1;
  }
  if (start_node == NULL || start_node->tree_data == NULL) {
    log_e("Search tree complete, not found.");
    return -1;
  }

  CompareResult node_cmp =
      compare_node(current_node, search_node, compare_node_by_name);
  if (node_cmp == N_EQUAL) {
    *result_node = current_node;
    return 0;
  }
  *result_parent_node = current_node;

  if (node_cmp == N_SMALLER)
    search_tree_node(current_node->left, search_node, result_node,
                     result_parent_node);
  if (node_cmp == N_GREATER)
    search_tree_node(current_node->right, search_node, result_node,
                     result_parent_node);
}

// 取要删除的节点的左节点（中序遍历排在被删除节点前一个的节点，也叫被删除节点的前驱），用来替换被删除的节点。
// 也就是被删除节点的左子树的最右边一个节点，该节点没有右子树；
TreeNode *get_most_right_node_from_left_tree(TreeNode *start_node) {
  if (start_node == NULL) {
    return NULL;
  }
  if (start_node->right == NULL) {
    return start_node;
  }
  get_most_right_node_from_left_tree(start_node->right);
}

// 取要删除的节点的右节点（中序遍历排在被删除节点后一个的节点，也叫被删除节点的后继），用来替换被删除的节点。
// 也就是被删除节点的右子树的最左边一个节点，该节点没有左子树；
TreeNode *get_most_left_node_from_right_tree(TreeNode *start_node) {
  if (start_node == NULL) {
    return NULL;
  }
  if (start_node->left == NULL) {
    return start_node;
  }
  get_most_left_node_from_right_tree(start_node->left);
}

// we always pass root node to the start_node
TreeNode *insert_tree_node(TreeNode *start_node, TreeNode *insert_node) {
  TreeNode *current_node = start_node;

  if (root_node == NULL) {
    root_node = insert_node;
    root_node_bak = root_node;
    return root_node;
  }
  if (root_node->tree_data == NULL) {
    root_node->tree_data = insert_node->tree_data;
    return root_node;
  }
  if (start_node == NULL || start_node->tree_data == NULL) {
    return root_node;
  }
  if (insert_node == NULL) {
    return root_node;
  }

  // 未给left_or_right赋初始值的时候，编译器默认赋值为N_EQUAL；
  CompareResult left_or_right;

  // left_or_right is true, the in_node smaller tha the right tree, so the
  // in_node must be a node of the left tree.
  // 插入的缺点是插入的节点多了以后二叉搜索树可能变得不平衡，需要增加旋转和平衡性判断
  while (current_node != NULL && current_node->tree_data != NULL) {
    left_or_right =
        compare_node(current_node, insert_node, compare_node_by_name);
    if (left_or_right == N_SMALLER) {
      if (current_node->left != NULL) {
        current_node = current_node->left;
      } else {
        current_node->left = insert_node;
        return root_node;
      }
    } else if (left_or_right == N_GREATER) {
      if (current_node->right != NULL) {
        current_node = current_node->right;
      } else {
        current_node->right = insert_node;
        return root_node;
      }
    } else if (left_or_right == N_EQUAL) {
      log_e("Node already exist in the tree, cannot insert node.");
      return root_node;
    }
  }
  return root_node;
}

TreeNode *insert_node(TreeNode *insert_node) {
  root_node = insert_tree_node(root_node, insert_node);
  return root_node;
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
void delete_tree_node(TreeNode *start_node, TreeNode *del_node) {
  if (start_node == NULL || start_node->tree_data == NULL) {
    log_e("Cannot delete from empty tree");
    return;
  }
  if (del_node->tree_data == NULL) {
    log_e("The node plan to delete is NULL.");
    return;
  }

  int result_value = -1;
  TreeNode *search_result_node = NULL;
  TreeNode *search_result_node_parent = NULL;

  result_value = search_tree_node(root_node, del_node, &search_result_node,
                                  &search_result_node_parent);
  bool node_is_left = false;
  bool node_is_right = false;
  TreeNode *replace_node = NULL;

  if (search_result_node == NULL) {
    log_e("Node not found.");
    return;
  }

  if (search_result_node != NULL && search_result_node_parent != NULL) {
    LeftOrRight node_left_or_right =
        node_is_left_or_right(search_result_node, search_result_node_parent);
    if (node_left_or_right == LEFT_NODE) {
      node_is_left = true;
    } else if (node_left_or_right == RIGHT_NODE) {
      node_is_right = true;
    }
  }

  if (search_result_node == NULL || result_value != 0) {
    log_e("Node is going to delete is not in the tree.");
    return;
  }

  if (search_result_node->left == NULL && search_result_node->right == NULL) {
    if (search_result_node == root_node) {
      // free(root_node);
      root_node = root_node_bak;
      return;
    }
    if (node_is_left) {
      search_result_node_parent->left = NULL;
    } else if (node_is_right) {
      search_result_node_parent->right = NULL;
    }
    return;
  } else if (search_result_node->left != NULL &&
             search_result_node->right == NULL) {
    if (search_result_node == root_node) {
      root_node = search_result_node->left;
      search_result_node->left = NULL;
      return;
    }
    if (node_is_left) {
      search_result_node_parent->left = search_result_node->left;
      search_result_node->left = NULL;
      return;
    }
    if (node_is_right) {
      search_result_node_parent->right = search_result_node->left;
      search_result_node->left = NULL;
      return;
    }
  } else if (search_result_node->left == NULL &&
             search_result_node->right != NULL) {
    if (search_result_node == root_node) {
      root_node = search_result_node->right;
      search_result_node->right = NULL;
      return;
    }
    if (node_is_left) {
      search_result_node_parent->left = search_result_node->right;
      search_result_node->right = NULL;
      return;
    }
    if (node_is_right) {
      search_result_node_parent->right = search_result_node->right;
      search_result_node->right = NULL;
      return;
    }
  } else if (search_result_node->left != NULL &&
             search_result_node->right != NULL) {
    replace_node = get_most_right_node_from_left_tree(search_result_node->left);
    if (search_result_node == root_node) {
      replace_node->right = root_node->right;
      root_node = replace_node;
      return;
    }
    if (node_is_left) {
      search_result_node_parent->left = replace_node;
      replace_node->right = search_result_node->right;
      search_result_node->left = NULL;
      search_result_node->right = NULL;
      return;
    }
    if (node_is_right) {
      search_result_node_parent->right = replace_node;
      replace_node->right = search_result_node->right;
      search_result_node->left = NULL;
      search_result_node->right = NULL;
      return;
    }
  }
}

void delete_node(TreeNode *delete_node) {
  delete_tree_node(root_node, delete_node);
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
    return trav_node;
  }
  if (*index < MAX_SIZE) {
    trav_result[(*index)++] = trav_node;
  } else {
    log_e("%s %s", __func__, "node array is fulled.");
    return trav_node;
  }
  preorder_traversal(trav_node->left, trav_result, index);
  preorder_traversal(trav_node->right, trav_result, index);
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
    return trav_node;
  }
  inorder_traversal(trav_node->left, trav_result, index);
  if (*index < MAX_SIZE) {
    trav_result[(*index)++] = trav_node;
  } else {
    log_e("%s %s", __func__, "node array is fulled.");
    return trav_node;
  }
  inorder_traversal(trav_node->right, trav_result, index);
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
  if (trav_node == NULL || trav_node->tree_data == NULL) {
    return trav_node;
  }
  postorder_traversal(trav_node->left, trav_result, index);
  postorder_traversal(trav_node->right, trav_result, index);
  if (*index < MAX_SIZE) {
    trav_result[(*index)++] = trav_node;
  } else {
    log_e("%s %s", __func__, "node array is fulled.");
    return trav_node;
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
