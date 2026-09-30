#include "single_circular_linkedlist.h"
#include "single_linkedlist.h"
#include <stdlib.h>
#include <string.h>

SCLinkedlist *create_single_circular_linkedlist() {
  SCLinkedlist *scllist = (SingleLinkedlist *)malloc(sizeof(SingleLinkedlist));
  memset(scllist, 0, sizeof(SingleLinkedlist));
  scllist->super = create_single_linkedlist();
  memset(scllist->super, 0, sizeof(SingleLinkedlist));
  return scllist;
}

void single_circular_linkedlist_constructor(SCLinkedlist *scllist, NODE *head,
                                            NODE *tail, int scll_size,
                                            SingleLinkedlist *sllist) {

  single_linkedlist_constructor(sllist, head, tail, scll_size);
  sllist->insert_node_sll = insert_node_in_scll;
  sllist->insert_at_the_end = insert_node_as_tail_in_scll;
  sllist->delete_node_sll = delete_node_in_scll;
  sllist->destroy_sll = destroy_single_circular_linkedlist;
}

bool is_node_in_scll(SCLinkedlist *scllist, NODE *search_node) {
  NODE *targ_node = NULL;
  targ_node = scllist->super->head;
  do {
    if (targ_node == search_node) {
      return true;
    }
    targ_node = targ_node->next;
  } while (targ_node != scllist->super->head);

  return false;
}

SCLinkedlist *insert_node_as_head_in_scll(SCLinkedlist *scllist,
                                          NODE *in_node) {
  in_node->next = scllist->super->head;
  scllist->super->head = in_node;
  scllist->super->tail->next = scllist->super->head;
  scllist->super->sll_size++;
  return scllist;
}

SCLinkedlist *insert_node_after_head_in_scll(SCLinkedlist *scllist,
                                             NODE *in_node) {
  if (in_node == NULL) {
    return scllist;
  }
  in_node->next = scllist->super->head->next;
  scllist->super->head->next = in_node;
  scllist->super->sll_size++;
  return scllist;
}

SCLinkedlist *insert_node_in_middle_scll(SCLinkedlist *scllist, NODE *in_node,
                                         int insert_pos) {
  NODE *middle_node = scllist->super->head;
  NODE *found_node = NULL;
  if (in_node == NULL) {
    return scllist;
  }
  if (insert_pos > scllist->super->sll_size) {
    insert_node_after_head_in_scll(scllist, in_node);
    return scllist;
  } else if (insert_pos < 0) {
    return scllist;
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
  scllist->super->sll_size++;
  return scllist;
}

SCLinkedlist *insert_node_as_tail_in_scll(SCLinkedlist *scllist,
                                          NODE *in_node) {
  if (in_node == NULL) {
    return scllist;
  }
  if (scllist->super->tail == scllist->super->head) {
    scllist->super->tail = in_node;
    scllist->super->head->next = scllist->super->tail;
    scllist->super->tail->next = scllist->super->head;
  } else {
    scllist->super->tail->next = in_node;
    in_node->next = scllist->super->head;
    scllist->super->tail = in_node;
  }
  scllist->super->sll_size++;
  return scllist;
}

SCLinkedlist *insert_node_in_scll(SCLinkedlist *scllist, NODE *in_node) {
  if (scllist->super->head == NULL) {
    scllist->super->head = in_node;
    scllist->super->tail = scllist->super->head;
    scllist->super->head->next = scllist->super->tail;
    scllist->super->tail->next = scllist->super->head;
    scllist->super->sll_size++;
    return scllist;
  }
  scllist->super->tail->next = in_node;
  scllist->super->tail = in_node;
  scllist->super->tail->next = scllist->super->head;
  scllist->super->sll_size++;
  return scllist;
}

NODE *get_node_position_in_scll(SCLinkedlist *scllist, NODE *node_pos) {
  NODE *found_node = scllist->super->head;
  if (is_empty((SingleLinkedlist *)scllist)) {
    return NULL;
  }
  if (node_pos == NULL) {
    return scllist->super->head;
  }
  if (!is_node_in_scll(scllist, node_pos)) {
    return scllist->super->head;
  }
  while (found_node != NULL) {
    if (found_node == node_pos) {
      return found_node;
    } else if (found_node->next != NULL) {
      found_node = found_node->next;
    } else {
      break;
    }
  }
  return scllist->super->head;
}

NODE *get_previous_node_in_scll(SCLinkedlist *scllist, NODE *targ_node,
                                NODE *prev_node) {
  if (targ_node == NULL) {
    return NULL;
  }
  if (is_empty((SingleLinkedlist *)scllist) &&
      !is_node_in_scll(scllist, targ_node)) {
    return NULL;
  }
  if (scllist->super->head == scllist->super->tail) {
    return scllist->super->head;
  }
  while (prev_node->next != targ_node) {
    prev_node = prev_node->next;
    if (prev_node == scllist->super->head) {
      return NULL;
    }
  }
  return prev_node;
}

SCLinkedlist *delete_node_in_scll(SCLinkedlist *scllist, NODE *del_node) {
  NODE *prev_node = NULL;
  if (del_node == NULL) {
    return scllist;
  }

  if (!is_node_in_scll(scllist, del_node)) {
    printf("delete error: the node plan to delete not exist in the list.\n");
    return scllist;
  }

  // 链表只有一个节点
  if (scllist->super->head == scllist->super->tail) {
    scllist->super->head = NULL;
    scllist->super->tail = NULL;
    return scllist;
  }

  // 删除节点为头节点
  if (del_node == scllist->super->head) {
    scllist->super->tail->next = scllist->super->head->next;
    scllist->super->head = scllist->super->head->next;
    return scllist;
  }

  // 删除节点为其他节点和尾节点
  prev_node = scllist->super->head;
  prev_node = get_previous_node_in_scll(scllist, del_node, prev_node);
  prev_node->next = del_node->next;
  if (del_node == scllist->super->tail) {
    scllist->super->tail = prev_node;
  }
  return scllist;
}

void destroy_single_circular_linkedlist(SCLinkedlist *scllist) {
  destroy_single_linkedlist(scllist->super);
  memset(scllist, 0, sizeof(SCLinkedlist));
  free(scllist);
}
