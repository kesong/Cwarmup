#include "double_circular_linkedlist.h"
#include "double_linkedlist.h"
#include "linkedlist.h"
#include "single_linkedlist.h"
#include <stdlib.h>
#include <string.h>

// C++,java等语言构造的对象都有一个隐式的指向对象自身的指针this，C语言没有这样一个指针，实现面向对象的时候就要显示的将这个对象本身作为参数传入函数
// 即这里的*dcllist指针。
DCLinkedList *create_double_circular_linkedlist() {
  DCLinkedList *dcllist = (DCLinkedList *)malloc(sizeof(DCLinkedList));
  memset(dcllist, 0, sizeof(DCLinkedList));
  return dcllist;
}

// 无法直接继承double_linkedlist，所以没有直接先使用父类的构造器构造
// 先是为父类成员分配空间，再调用父类构造器构造父类，如不先为父类成员分配空间，就会产生空指针异常
void double_circular_linkedlist_constructor(
    DCLinkedList *dcllist, char *description, char *serial_no, NODE_DLL *head,
    NODE_DLL *tail, int dlls_size, insert_node_to_ll insert_func,
    delete_node_from_ll delete_func, destroy_linkedlist_func destroy_func,
    char *name, set_name_poly set_name_func, get_name_poly get_name_func,
    polymorphism_toString toString) {
  dcllist->super = (Linkedlist *)malloc(sizeof(Linkedlist));
  linkedlist_constructor(dcllist->super, head, tail, dlls_size, insert_func,
                         delete_func, destroy_func, name, set_name_func,
                         get_name_func, toString);
  dcllist->description = description;
  dcllist->serial_no = serial_no;
}

bool is_empty_dcll(DCLinkedList *dcllist) {
  return dcllist->super->head == NULL ? true : false;
}

bool is_node_in_dcll(DCLinkedList *dcllist, NODE_DLL *in_node) {
  NODE_DLL *targ_node = dcllist->super->head;
  while (targ_node != dcllist->super->tail) {
    if (in_node == targ_node) {
      return true;
    }
    if (targ_node->next != dcllist->super->tail) {
      targ_node = targ_node->next;
    } else
      break;
  }
  return false;
}

int size_of_dcll(DCLinkedList *dcllist) {
  NODE_DLL *d_size_node = dcllist->super->head;
  dcllist->super->size_ll = 0;
  if (dcllist->super->head == NULL) {
    return 0;
  }
  while (d_size_node != dcllist->super->tail) {
    dcllist->super->size_ll++;
    d_size_node = d_size_node->next;
  }
  if (d_size_node == dcllist->super->tail) {
    return dcllist->super->size_ll += 1;
  }
  return 0;
}

DCLinkedList *insert_node_as_head_dcll(DCLinkedList *dcllist,
                                       NODE_DLL *in_node) {
  in_node->next = dcllist->super->head;
  in_node->prev = dcllist->super->tail;
  dcllist->super->head = in_node;
  dcllist->super->size_ll++;
  return dcllist;
}

DCLinkedList *insert_node_after_head_dcll(DCLinkedList *dcllist,
                                          NODE_DLL *in_node) {
  if (in_node == NULL) {
    return dcllist;
  }
  in_node->next = ((NODE_DLL *)dcllist->super->head)->next;
  in_node->prev = dcllist->super->head;
  ((NODE_DLL *)dcllist->super->head)->next = in_node;
  dcllist->super->size_ll++;
  return dcllist;
}

DCLinkedList *insert_node_in_middle_dcll(DCLinkedList *dcllist,
                                         NODE_DLL *in_node, int insert_pos) {
  NODE_DLL *middle_node = dcllist->super->head;
  NODE_DLL *found_node = NULL;
  if (in_node == NULL) {
    return dcllist;
  }
  if (insert_pos > dcllist->super->size_ll) {
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
  dcllist->super->size_ll++;
  return dcllist;
}

DCLinkedList *insert_node_as_tail_dcll(DCLinkedList *dcllist,
                                       NODE_DLL *in_node) {
  if (in_node == NULL) {
    return dcllist;
  }
  ((NODE_DLL *)dcllist->super->tail)->next = in_node;
  in_node->prev = dcllist->super->tail;
  in_node->next = dcllist->super->head;
  dcllist->super->tail = in_node;
  dcllist->super->size_ll++;
  return dcllist;
}

DCLinkedList *insert_node_dcll(DCLinkedList *dcllist, NODE_DLL *in_node) {
  if (dcllist->super->head == NULL) {
    dcllist->super->head = in_node;
    dcllist->super->tail = dcllist->super->head;
    ((NODE_DLL *)dcllist->super->head)->prev = dcllist->super->head;
    ((NODE_DLL *)dcllist->super->head)->next = dcllist->super->tail;
    dcllist->super->tail = dcllist->super->head;
    return dcllist;
  }
  if (in_node == NULL) {
    return dcllist;
  }
  ((NODE_DLL *)dcllist->super->tail)->next = in_node;
  ((NODE_DLL *)dcllist->super->head)->prev = in_node;
  in_node->prev = dcllist->super->tail;
  in_node->next = dcllist->super->head;
  dcllist->super->tail = in_node;
  dcllist->super->size_ll++;
  return dcllist;
}

DCLinkedList *get_node_position_dcll(DCLinkedList *dcllist,
                                     NODE_DLL *node_pos) {
  NODE_DLL *found_node = NULL;
  found_node = (NODE_DLL *)dcllist->super->head;
  if (is_empty_dcll(dcllist)) {
    return NULL;
  }
  if (node_pos == NULL) {
    return NULL;
  }
  while (node_pos != dcllist->super->tail) {
    if (node_pos == found_node) {
      return dcllist;
    }
    found_node = found_node->next;
  }
  if (node_pos == dcllist->super->tail) {
    return dcllist;
  }
  return NULL;
}

DCLinkedList *delete_node_dcll(DCLinkedList *dcllist, NODE_DLL *del_node) {
  if (del_node == NULL) {
    return dcllist;
  }

  // 链表只有一个节点
  if (dcllist->super->head == dcllist->super->tail) {
    ((NODE_DLL *)dcllist->super->head)->prev = NULL;
    ((NODE_DLL *)dcllist->super->head)->next = NULL;
    dcllist->super->head = NULL;
    return dcllist;
  }

  // 被删除节点为头节点
  if (del_node == dcllist->super->head) {
    ((NODE_DLL *)dcllist->super->tail)->next =
        ((NODE_DLL *)dcllist->super->head)->next;
    dcllist->super->head = ((NODE_DLL *)dcllist->super->head)->next;
    ((NODE_DLL *)dcllist->super->head)->prev = dcllist->super->tail;
    return dcllist;
  }

  // 被删除节点为其他节点或者尾节点
  del_node->next->prev = del_node->prev;
  del_node->prev->next = del_node->next;
  if (del_node == dcllist->super->tail) {
    ((NODE_DLL *)dcllist->super->head)->prev =
        ((NODE_DLL *)dcllist->super->tail)->prev;
    ((NODE_DLL *)dcllist->super->tail)->prev->next = dcllist->super->head;
    dcllist->super->tail = ((NODE_DLL *)dcllist->super->tail)->prev;
  }
  return dcllist;
}

void destroy_double_circular_linkedlist(DCLinkedList *dcllist) {
  free(dcllist->super);
  dcllist->super = NULL;
  memset(dcllist, 0, sizeof(DCLinkedList));
  free(dcllist);
  dcllist = NULL;
}

void set_name_dcll(DCLinkedList *dcllist, char *name) {
  ((Linkedlist *)dcllist)->name = name;
}

char *get_name_dcll(DCLinkedList *dcllist) {
  return ((Linkedlist *)dcllist)->name;
}

void _toString_dcll(void *receive_llist) {
  Linkedlist *llist = (Linkedlist *)receive_llist;
  printf("This is %s. \n", llist->name);
}

void dcll_toString(DCLinkedList *dcllist) { _toString_dcll(dcllist); }
