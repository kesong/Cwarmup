#include "single_linkedlist.h"
#include "linkedlist.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

SingleLinkedlist *create_single_linkedlist() {
  SingleLinkedlist *sllist =
      (SingleLinkedlist *)malloc(sizeof(SingleLinkedlist));
  memset(sllist, 0, sizeof(SingleLinkedlist));
  return sllist;
}

void single_linkedlist_constructor(SingleLinkedlist *sllist, NODE *head,
                                   NODE *tail, int size_ll, char *symbol,
                                   insert_node_to_ll insert_func,
                                   delete_node_from_ll delete_func,
                                   destroy_linkedlist_func destroy_func,
                                   char *name, set_name_poly set_name_func,
                                   get_name_poly get_name_func,
                                   polymorphism_toString toString) {
  linkedlist_constructor((Linkedlist *)sllist, head, tail, size_ll, insert_func,
                         delete_func, destroy_func, name, set_name_func,
                         get_name_func, toString);
  sllist->symbol = symbol;
}

/*
 * 使用基类的函数，各个子类不再单独有自己的函数，子类函数也只是将对象转型为基类对象，这里就体现继承的优势
bool is_empty(SingleLinkedlist *sllist) {
  return ((Linkedlist *)sllist)->head == NULL ? true : false;
}

int size_of_linklist(SingleLinkedlist *sllist) {
  Linkedlist *llist = (Linkedlist *)sllist;
  return llist->size_ll;
}  */

bool is_node_in_single_linkedlist(SingleLinkedlist *sllist, NODE *t_node) {
  Linkedlist *llist = (Linkedlist *)sllist;
  NODE *targ_node = llist->head;
  while (targ_node != NULL) {
    if (targ_node == t_node) {
      return true;
    }
    if (targ_node->next != NULL) {
      targ_node = targ_node->next;
    }
  }
  return false;
}

SingleLinkedlist *insert_node_as_head(SingleLinkedlist *sllist, NODE *in_node) {
  Linkedlist *llist = (Linkedlist *)sllist;
  in_node->next = llist->head;
  llist->head = in_node;
  llist->size_ll++;
  return sllist;
}

SingleLinkedlist *insert_node_after_head(SingleLinkedlist *sllist,
                                         NODE *in_node) {
  Linkedlist *llist = (Linkedlist *)sllist;
  if (in_node == NULL) {
    return sllist;
  }
  in_node->next = ((NODE *)llist->head)->next;
  ((NODE *)llist->head)->next = in_node;
  llist->size_ll++;
  return sllist;
}

SingleLinkedlist *insert_node_in_middle(SingleLinkedlist *sllist, NODE *in_node,
                                        int insert_pos) {
  Linkedlist *llist = (Linkedlist *)sllist;
  NODE *middle_node = (NODE *)llist->head;
  NODE *found_node = NULL;
  if (in_node == NULL) {
    return sllist;
  }
  if (insert_pos > llist->size_ll) {
    insert_node_after_head(sllist, in_node);
    return sllist;
  } else if (insert_pos < 0) {
    return sllist;
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
  found_node->next = in_node;
  (llist->size_ll)++;
  return sllist;
}

SingleLinkedlist *insert_node_as_tail(SingleLinkedlist *sllist, NODE *in_node) {
  Linkedlist *llist = (Linkedlist *)sllist;
  llist->tail = get_tail_sll(sllist);
  if (in_node == NULL) {
    return sllist;
  }
  ((NODE *)llist->tail)->next = in_node;
  in_node->next = NULL;
  llist->tail = in_node;
  llist->size_ll++;
  return sllist;
}

SingleLinkedlist *insert_node_sll(SingleLinkedlist *sllist, NODE *insert_node) {
  Linkedlist *llist = (Linkedlist *)sllist;
  if (llist->head == NULL) {
    llist->head = insert_node;
    llist->tail = llist->head;
    return sllist;
  }
  ((NODE *)llist->tail)->next = insert_node;
  llist->tail = insert_node;
  ((NODE *)llist->tail)->next = NULL;
  return sllist;
}

NODE *get_node_position(SingleLinkedlist *sllist, NODE *node_pos) {
  Linkedlist *llist = (Linkedlist *)sllist;
  NODE *found_node = NULL;
  found_node = llist->head;
  if (is_empty(sllist)) {
    return NULL;
  }
  if (node_pos == NULL) {
    return NULL;
  }
  while (node_pos != NULL) {
    if (node_pos == found_node) {
      return found_node;
    }
    found_node = found_node->next;
  }
  return NULL;
}

NODE *get_previous_node(SingleLinkedlist *sllist, NODE *targ_node) {
  Linkedlist *llist = (Linkedlist *)sllist;
  NODE *prev_node = NULL;
  prev_node = llist->head;
  if (is_empty(sllist)) {
    return NULL;
  }
  if (targ_node == NULL) {
    return NULL;
  }
  while (prev_node->next != NULL) {
    if (prev_node->next == targ_node) {
      return prev_node;
    }
    prev_node = prev_node->next;
  }
  return NULL;
}

NODE *get_tail_sll(SingleLinkedlist *sllist) {
  Linkedlist *llist = (Linkedlist *)sllist;
  NODE *tail_node = NULL;
  tail_node = llist->head;
  if (llist->tail == NULL) {
    printf("get error: empty list");
  }
  while (tail_node->next != NULL) {
    tail_node = tail_node->next;
    if (tail_node->next == NULL) {
      return llist->tail;
    }
  }
  return llist->tail;
}

SingleLinkedlist *delete_node_sll(SingleLinkedlist *sllist, NODE *del_node) {
  Linkedlist *llist = (Linkedlist *)sllist;
  NODE *pre_node = NULL;
  if (del_node == NULL) {
    return sllist;
  }

  // 链表只有一个节点
  if (llist->head != NULL && ((NODE *)llist->head)->next == NULL) {
    llist->head = NULL;
    llist->tail = NULL;
    return sllist;
  }

  // 被删除节点为头节点
  if (del_node == llist->head) {
    llist->head = ((NODE *)llist->head)->next;
    return sllist;
  }

  // 被删除节点为尾节点或者其他节点
  pre_node = get_previous_node(sllist, del_node);
  pre_node->next = pre_node->next->next;
  if (del_node == llist->tail) {
    llist->tail = pre_node;
  }
  return sllist;
}

void destroy_single_linkedlist(SingleLinkedlist *sllist) {
  destroy_linkedlist((Linkedlist *)sllist);
  sllist = NULL;
}

void set_name_sll(SingleLinkedlist *sllist, char *name) {
  ((Linkedlist *)sllist)->name = name;
}

char *get_name_sll(SingleLinkedlist *sllist) {
  return ((Linkedlist *)sllist)->name;
}

void _toString_sll(void *receive_llist) {
  Linkedlist *llist = (Linkedlist *)receive_llist;
  printf("This is %s. \n", llist->name);
}

void sll_toString(SingleLinkedlist *sllist) { _toString_sll(sllist); }
