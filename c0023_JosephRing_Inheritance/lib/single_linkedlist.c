#include "single_linkedlist.h"
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
                                   NODE *tail, int sll_size) {
  sllist->head = head;
  sllist->tail = tail;
  sllist->sll_size = sll_size;
  sllist->insert_node_sll = insert_node;
  sllist->insert_at_the_end = NULL;
  sllist->delete_node_sll = delete_node;
  sllist->destroy_sll = destroy_single_linkedlist;
}

bool is_empty(SingleLinkedlist *sllist) {
  return sllist->head == NULL ? true : false;
};

// lib/single_linkedlist.c|10 col 27-28 error| Incompatible function pointer
// types assigning to 'insert_node_into_linkedlist' (aka 'void *(*)(void *, void
// *)') from 'SingleLinkedlist *(SingleLinkedlist *, NODE *)' (aka 'struct
// single_linkedlist *(struct single_linkedlist *, struct node *)')
bool is_node_in_single_linkedlist(SingleLinkedlist *sllist, NODE *t_node) {
  NODE *targ_node = sllist->head;
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

int size_of_linklist(SingleLinkedlist *sllist) { return sllist->sll_size; }

SingleLinkedlist *insert_node_as_head(SingleLinkedlist *sllist, NODE *in_node) {
  in_node->next = sllist->head;
  sllist->head = in_node;
  sllist->sll_size++;
  return sllist;
}

SingleLinkedlist *insert_node_after_head(SingleLinkedlist *sllist,
                                         NODE *in_node) {
  if (in_node == NULL) {
    return sllist;
  }
  in_node->next = sllist->head->next;
  sllist->head->next = in_node;
  sllist->sll_size++;
  return sllist;
}

SingleLinkedlist *insert_node_in_middle(SingleLinkedlist *sllist, NODE *in_node,
                                        int insert_pos) {
  NODE *middle_node = sllist->head;
  NODE *found_node = NULL;
  if (in_node == NULL) {
    return sllist;
  }
  if (insert_pos > sllist->sll_size) {
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
  (sllist->sll_size)++;
  return sllist;
}

SingleLinkedlist *insert_node_as_tail(SingleLinkedlist *sllist, NODE *in_node) {
  sllist->tail = get_tail(sllist);
  if (in_node == NULL) {
    return sllist;
  }
  sllist->tail->next = in_node;
  in_node->next = NULL;
  sllist->tail = in_node;
  sllist->sll_size++;
  return sllist;
}

SingleLinkedlist *insert_node(SingleLinkedlist *sllist, NODE *insert_node) {
  if (sllist->head == NULL) {
    sllist->head = insert_node;
    sllist->tail = sllist->head;
    return sllist;
  }
  sllist->tail->next = insert_node;
  sllist->tail = insert_node;
  sllist->tail->next = NULL;
  return sllist;
}

NODE *get_node_position(SingleLinkedlist *sllist, NODE *node_pos) {
  NODE *found_node = NULL;
  found_node = sllist->head;
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
  NODE *prev_node = NULL;
  prev_node = sllist->head;
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

NODE *get_tail(SingleLinkedlist *sllist) {
  NODE *tail_node = NULL;
  tail_node = sllist->head;
  if (sllist->tail == NULL) {
    printf("get error: empty list");
  }
  while (tail_node->next != NULL) {
    tail_node = tail_node->next;
    if (tail_node->next == NULL) {
      return sllist->tail;
    }
  }
  return sllist->tail;
}

SingleLinkedlist *delete_node(SingleLinkedlist *sllist, NODE *del_node) {
  NODE *pre_node = NULL;
  if (del_node == NULL) {
    return sllist;
  }

  // 链表只有一个节点
  if (sllist->head != NULL && sllist->head->next == NULL) {
    sllist->head = NULL;
    sllist->tail = NULL;
    return sllist;
  }

  // 被删除节点为头节点
  if (del_node == sllist->head) {
    sllist->head = sllist->head->next;
    return sllist;
  }

  // 被删除节点为尾节点或者其他节点
  pre_node = get_previous_node(sllist, del_node);
  pre_node->next = pre_node->next->next;
  if (del_node == sllist->tail) {
    sllist->tail = pre_node;
  }
  return sllist;
}

void destroy_single_linkedlist(SingleLinkedlist *sllist) {
  memset(sllist, 0, sizeof(SingleLinkedlist));
  free(sllist);
}
