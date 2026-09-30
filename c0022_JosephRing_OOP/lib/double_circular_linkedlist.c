#include "double_circular_linkedlist.h"
#include "double_linkedlist.h"

// C++,java等语言构造的对象都有一个隐式的指向对象自身的指针this，C语言没有这样一个指针，实现面向对象的时候就要显示的将这个对象本身作为参数传入函数
// 即这里的*dcllist指针。
DCLinkedList *init_double_circular_linkedlist(DCLinkedList *dcllist) {
  dcllist->tail_node = dcllist->head_node;
  dcllist->head_node = NULL;
  return dcllist;
}

bool is_empty_dcll(DCLinkedList *dcllist) {
  return dcllist->head_node == NULL ? true : false;
}

bool is_node_in_dcll(DCLinkedList *dcllist, NODE_DLL *in_node) {
  NODE_DLL *targ_node = dcllist->head_node;
  while (targ_node != dcllist->tail_node) {
    if (in_node == targ_node) {
      return true;
    }
    if (targ_node->next != dcllist->tail_node) {
      targ_node = targ_node->next;
    } else
      break;
  }
  return false;
}

int size_of_dcll(DCLinkedList *dcllist) {
  NODE_DLL *d_size_node = dcllist->head_node;
  dcllist->dc_size = 0;
  if (dcllist->head_node == NULL) {
    return 0;
  }
  while (d_size_node != dcllist->tail_node) {
    dcllist->dc_size++;
    d_size_node = d_size_node->next;
  }
  if (d_size_node == dcllist->tail_node) {
    return dcllist->dc_size += 1;
  }
  return 0;
}

DCLinkedList *insert_node_as_head_dcll(DCLinkedList *dcllist,
                                       NODE_DLL *in_node) {
  in_node->next = dcllist->head_node;
  in_node->prev = dcllist->tail_node;
  dcllist->head_node = in_node;
  dcllist->dc_size++;
  return dcllist;
}

DCLinkedList *insert_node_after_head_dcll(DCLinkedList *dcllist,
                                          NODE_DLL *in_node) {
  if (in_node == NULL) {
    return dcllist;
  }
  in_node->next = dcllist->head_node->next;
  in_node->prev = dcllist->head_node;
  dcllist->head_node->next = in_node;
  dcllist->dc_size++;
  return dcllist;
}

DCLinkedList *insert_node_in_middle_dcll(DCLinkedList *dcllist,
                                         NODE_DLL *in_node, int insert_pos) {
  NODE_DLL *middle_node = dcllist->head_node;
  NODE_DLL *found_node = NULL;
  if (in_node == NULL) {
    return dcllist;
  }
  if (insert_pos > dcllist->dc_size) {
    insert_node_after_head_dcll(dcllist, in_node);
    return dcllist;
  } else if (insert_pos < 0) {
    return dcllist;
  }
  while (insert_pos > 0) {
    middle_node = middle_node->next;
    insert_pos--;
    if (insert_pos == 0) {
      found_node = middle_node;
      break;
    }
  }
  in_node->next = found_node->next;
  in_node->prev = found_node;
  found_node->next = in_node;
  dcllist->dc_size++;
  return dcllist;
}

DCLinkedList *insert_node_as_tail_dcll(DCLinkedList *dcllist,
                                       NODE_DLL *in_node) {
  if (in_node == NULL) {
    return dcllist;
  }
  dcllist->tail_node->next = in_node;
  in_node->prev = dcllist->tail_node;
  in_node->next = dcllist->head_node;
  dcllist->tail_node = in_node;
  dcllist->dc_size++;
  return dcllist;
}

DCLinkedList *insert_node_dcll(DCLinkedList *dcllist, NODE_DLL *in_node) {
  if (dcllist->head_node == NULL) {
    dcllist->head_node = in_node;
    dcllist->tail_node = dcllist->head_node;
    dcllist->head_node->prev = dcllist->head_node;
    dcllist->head_node->next = dcllist->tail_node;
    dcllist->tail_node = dcllist->head_node;
    return dcllist;
  }
  if (in_node == NULL) {
    return dcllist;
  }
  dcllist->tail_node->next = in_node;
  dcllist->head_node->prev = in_node;
  in_node->prev = dcllist->tail_node;
  in_node->next = dcllist->head_node;
  dcllist->tail_node = in_node;
  dcllist->dc_size++;
  return dcllist;
}

DCLinkedList *get_node_position_dcll(DCLinkedList *dcllist,
                                     NODE_DLL *node_pos) {
  NODE_DLL *found_node = NULL;
  found_node = dcllist->head_node;
  if (is_empty_dcll(dcllist)) {
    return NULL;
  }
  if (node_pos == NULL) {
    return NULL;
  }
  while (node_pos != dcllist->tail_node) {
    if (node_pos == found_node) {
      return dcllist;
    }
    found_node = found_node->next;
  }
  if (node_pos == dcllist->tail_node) {
    return dcllist;
  }
  return NULL;
}

DCLinkedList *delete_node_dcll(DCLinkedList *dcllist, NODE_DLL *del_node) {
  if (del_node == NULL) {
    return dcllist;
  }

  // 链表只有一个节点
  if (dcllist->head_node == dcllist->tail_node) {
    dcllist->head_node->prev = NULL;
    dcllist->head_node->next = NULL;
    dcllist->head_node = NULL;
    return dcllist;
  }

  // 被删除节点为头节点
  if (del_node == dcllist->head_node) {
    dcllist->tail_node->next = dcllist->head_node->next;
    dcllist->head_node = dcllist->head_node->next;
    dcllist->head_node->prev = dcllist->tail_node;
    return dcllist;
  }

  // 被删除节点为其他节点或者尾节点
  del_node->next->prev = del_node->prev;
  del_node->prev->next = del_node->next;
  if (del_node == dcllist->tail_node) {
    dcllist->head_node->prev = dcllist->tail_node->prev;
    dcllist->tail_node->prev->next = dcllist->head_node;
    dcllist->tail_node = dcllist->tail_node->prev;
  }
  return dcllist;
}
