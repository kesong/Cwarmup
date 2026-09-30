#include "double_linkedlist.h"

// 面向对象改造，将一个双向链表视为一个对象，按照C++或者java面向对象的方式进行操作，往双向链表中添加元素
// 从双向链表中删除一个元素等，这里每个链表操作函数的返回类型均为链表结构体，会比较消耗内存，尤其是链表比较大的时候。用结构体指针是更好的方式
// DoubleLinkedList *init_head_of_linkedlist(DoubleLinkedList *dllist);
// 在双向循环链表中使用结构体指针进行改造。
DoubleLinkedList init_head_of_linkedlist(DoubleLinkedList dllist) {
  dllist.head_node = NULL;
  dllist.tail_node = dllist.head_node;
  dllist.dll_size = 0;
  return dllist;
}

bool is_empty_dll(DoubleLinkedList dllist) {
  return dllist.head_node == NULL ? true : false;
}

bool is_node_in_dll(DoubleLinkedList dllist, NODE_DLL *in_node) {
  NODE_DLL *targ_node = dllist.head_node;
  while (targ_node != NULL) {
    if (in_node == targ_node) {
      return true;
    }
    if (targ_node->next != NULL) {
      targ_node = targ_node->next;
    } else
      break;
  }
  return false;
}

int size_of_dll(DoubleLinkedList dllist) { return dllist.dll_size; }

DoubleLinkedList insert_node_as_head_dll(DoubleLinkedList dllist,
                                         NODE_DLL *in_node) {
  in_node->next = dllist.head_node;
  in_node->prev = dllist.tail_node;
  dllist.head_node = in_node;
  dllist.dll_size++;
  return dllist;
}

DoubleLinkedList insert_node_after_head_dll(DoubleLinkedList dllist,
                                            NODE_DLL *in_node) {
  if (in_node == NULL) {
    return dllist;
  }
  in_node->next = dllist.head_node->next;
  in_node->prev = dllist.head_node;
  dllist.head_node->next = in_node;
  dllist.dll_size++;
  return dllist;
}

DoubleLinkedList insert_node_in_middle_dll(DoubleLinkedList dllist,
                                           NODE_DLL *in_node, int insert_pos) {
  NODE_DLL *middle_node = dllist.head_node;
  NODE_DLL *found_node = NULL;
  if (in_node == NULL) {
    return dllist;
  }
  if (insert_pos > dllist.dll_size) {
    insert_node_after_head_dll(dllist, in_node);
    return dllist;
  } else if (insert_pos < 0) {
    return dllist;
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
  dllist.dll_size++;
  return dllist;
}

DoubleLinkedList insert_node_as_tail_dll(DoubleLinkedList dllist,
                                         NODE_DLL *in_node) {
  if (in_node == NULL) {
    return dllist;
  }
  dllist.tail_node->next = in_node;
  in_node->prev = dllist.tail_node;
  in_node->next = dllist.head_node;
  dllist.tail_node = in_node;
  dllist.dll_size++;
  return dllist;
}

DoubleLinkedList insert_node_dll(DoubleLinkedList dllist, NODE_DLL *in_node) {
  if (dllist.head_node == NULL) {
    dllist.head_node = in_node;
    dllist.head_node->prev = NULL;
    dllist.head_node->next = NULL;
    dllist.tail_node = dllist.head_node;
    return dllist;
  }
  if (in_node == NULL) {
    return dllist;
  }
  dllist.tail_node->next = in_node;
  in_node->prev = dllist.tail_node;
  dllist.tail_node = in_node;
  dllist.dll_size++;
  return dllist;
}

DoubleLinkedList get_node_position_dll(DoubleLinkedList dllist,
                                       NODE_DLL *node_pos) {
  NODE_DLL *found_node = NULL;
  found_node = dllist.head_node;
  if (is_empty_dll(dllist)) {
    return dllist;
  }
  if (node_pos == NULL) {
    return dllist;
  }
  while (node_pos != NULL) {
    if (node_pos == found_node) {
      return dllist;
    }
    found_node = found_node->next;
  }
  return dllist;
}

DoubleLinkedList delete_node_dll(DoubleLinkedList dllist, NODE_DLL *del_node) {
  if (del_node == NULL) {
    return dllist;
  }

  // 链表只有一个节点
  if (dllist.head_node == dllist.tail_node) {
    dllist.head_node = NULL;
    return dllist;
  }

  // 被删除节点为头节点
  if (del_node == dllist.head_node) {
    dllist.head_node = dllist.head_node->next;
    dllist.head_node->prev = NULL;
    return dllist;
  }

  // 被删除节点为其他节点或者尾节点
  del_node->prev->next = del_node->next;
  del_node->next->prev = del_node->prev;
  if (del_node == dllist.tail_node) {
    dllist.tail_node = del_node->prev;
    dllist.tail_node->next = NULL;
  }
  return dllist;
}
