#include "double_linkedlist.h"
#include "linkedlist.h"
#include "single_linkedlist.h"
#include <stdlib.h>
#include <string.h>

// 面向对象改造，将一个双向链表视为一个对象，按照C++或者java面向对象的方式进行操作，往双向链表中添加元素
// 从双向链表中删除一个元素等，这里每个链表操作函数的返回类型均为链表结构体，会比较消耗内存，尤其是链表比较大的时候。用结构体指针是更好的方式
// DoubleLinkedList *init_head_of_linkedlist(DoubleLinkedList *dllist);
// 在双向循环链表中使用结构体指针进行改造。
DoubleLinkedList *create_double_linkedlist() {
  DoubleLinkedList *dllist =
      (DoubleLinkedList *)malloc(sizeof(DoubleLinkedList));
  memset(dllist, 0, sizeof(DoubleLinkedList));
  return dllist;
}

void double_linkedlist_constructor(DoubleLinkedList *dllist, NODE_DLL *head,
                                   NODE_DLL *tail, int size_ll, char charactor,
                                   insert_node_to_ll insert_func,
                                   delete_node_from_ll delete_func,
                                   destroy_linkedlist_func destroy_func,
                                   char *name, set_name_poly set_name_func,
                                   get_name_poly get_name_func,
                                   polymorphism_toString toStirng) {
  dllist->super = (Linkedlist *)malloc(sizeof(Linkedlist));
  linkedlist_constructor(dllist->super, head, tail, size_ll, insert_func,
                         delete_func, destroy_func, name, set_name_func,
                         get_name_func, toStirng);
  dllist->charactor = charactor;
}

bool is_empty_dll(DoubleLinkedList *dllist) {
  return dllist->super->head == NULL ? true : false;
}

int size_of_dll(DoubleLinkedList *dllist) { return dllist->super->size_ll; }

bool is_node_in_dll(DoubleLinkedList *dllist, NODE_DLL *in_node) {
  NODE_DLL *targ_node = (NODE_DLL *)dllist->super->head;
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

DoubleLinkedList *insert_node_as_head_dll(DoubleLinkedList *dllist,
                                          NODE_DLL *in_node) {
  in_node->next = (NODE_DLL *)dllist->super->head;
  in_node->prev = (NODE_DLL *)dllist->super->tail;
  dllist->super->head = in_node;
  dllist->super->size_ll++;
  return dllist;
}

DoubleLinkedList *insert_node_after_head_dll(DoubleLinkedList *dllist,
                                             NODE_DLL *in_node) {
  if (in_node == NULL) {
    return dllist;
  }
  in_node->next = ((NODE_DLL *)dllist->super->head)->next;
  in_node->prev = dllist->super->head;
  ((NODE_DLL *)dllist->super->head)->next = in_node;
  dllist->super->size_ll++;
  return dllist;
}

DoubleLinkedList *insert_node_in_middle_dll(DoubleLinkedList *dllist,
                                            NODE_DLL *in_node, int insert_pos) {
  NODE_DLL *middle_node = (NODE_DLL *)dllist->super->head;
  NODE_DLL *found_node = NULL;
  if (in_node == NULL) {
    return dllist;
  }
  if (insert_pos > dllist->super->size_ll) {
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
  dllist->super->size_ll++;
  return dllist;
}

DoubleLinkedList *insert_node_as_tail_dll(DoubleLinkedList *dllist,
                                          NODE_DLL *in_node) {
  if (in_node == NULL) {
    return dllist;
  }
  ((NODE_DLL *)dllist->super->tail)->next = in_node;
  in_node->prev = (NODE_DLL *)dllist->super->tail;
  in_node->next = (NODE_DLL *)dllist->super->head;
  dllist->super->tail = in_node;
  dllist->super->size_ll++;
  return dllist;
}

DoubleLinkedList *insert_node_dll(DoubleLinkedList *dllist, NODE_DLL *in_node) {
  if (dllist->super->head == NULL) {
    dllist->super->head = in_node;
    ((NODE_DLL *)dllist->super->head)->prev = NULL;
    ((NODE_DLL *)dllist->super->head)->next = NULL;
    dllist->super->tail = dllist->super->head;
    return dllist;
  }
  if (in_node == NULL) {
    return dllist;
  }
  ((NODE_DLL *)dllist->super->tail)->next = in_node;
  in_node->prev = (NODE_DLL *)dllist->super->tail;
  dllist->super->tail = in_node;
  dllist->super->size_ll++;
  return dllist;
}

DoubleLinkedList *get_node_position_dll(DoubleLinkedList *dllist,
                                        NODE_DLL *node_pos) {
  NODE_DLL *found_node = NULL;
  found_node = (NODE_DLL *)dllist->super->head;
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

DoubleLinkedList *delete_node_dll(DoubleLinkedList *dllist,
                                  NODE_DLL *del_node) {
  if (del_node == NULL) {
    return dllist;
  }

  // 链表只有一个节点
  if (dllist->super->head == dllist->super->tail) {
    dllist->super->head = NULL;
    return dllist;
  }

  // 被删除节点为头节点
  if (del_node == dllist->super->head) {
    dllist->super->head = ((NODE_DLL *)dllist->super->head)->next;
    ((NODE_DLL *)dllist->super->head)->prev = NULL;
    return dllist;
  }

  // 被删除节点为其他节点或者尾节点
  del_node->prev->next = del_node->next;
  del_node->next->prev = del_node->prev;
  if (del_node == dllist->super->tail) {
    dllist->super->tail = del_node->prev;
    ((NODE_DLL *)dllist->super->tail)->next = NULL;
  }
  return dllist;
}

void destroy_double_linkedlist(DoubleLinkedList *dllist) {
  memset(dllist->super, 0, sizeof(Linkedlist));
  free(dllist->super);
  dllist->super = NULL;
  memset(dllist, 0, sizeof(DoubleLinkedList));
  free(dllist);
  dllist = NULL;
}

void set_name_dll(DoubleLinkedList *dllist, char *name) {
  ((Linkedlist *)dllist)->name = name;
}

char *get_name_dll(DoubleLinkedList *dllist) {
  return ((Linkedlist *)dllist)->name;
}

void _toString_dll(void *receive_llist) {
  Linkedlist *llist = (Linkedlist *)receive_llist;
  printf("This is %s. \n", llist->name);
}

void dll_toString(DoubleLinkedList *dllist) { _toString_dll(dllist); }
