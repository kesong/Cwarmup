#include "single_linkedlist.h"
#include <stdbool.h>

NODE *head = NULL;
NODE *tail = NULL;
int sll_size_count = 0;

NODE *init_single_linkedlist() {
  tail = head;
  return head;
}

bool is_empty() { return head == NULL ? true : false; };

bool is_node_in_list(NODE *t_node) {
  NODE *targ_node = head;
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

int size_of_linklist() {
  NODE *size_node = head;
  if (head == NULL) {
    return 0;
  }
  while (size_node != NULL) {
    sll_size_count++;
    if (size_node->next == NULL) {
      return sll_size_count;
    }
    size_node = size_node->next;
  }
  return 0;
}

NODE *insert_node_as_head(NODE *in_node) {
  in_node->next = head;
  head = in_node;
  sll_size_count++;
  return head;
}

NODE *insert_node_after_head(NODE *in_node) {
  if (in_node == NULL) {
    return head;
  }
  in_node->next = head->next;
  head->next = in_node;
  sll_size_count++;
  return head;
}

NODE *insert_node_in_middle(NODE *in_node, int insert_pos) {
  NODE *middle_node = head;
  NODE *found_node = NULL;
  if (in_node == NULL) {
    return head;
  }
  if (insert_pos > sll_size_count) {
    insert_node_after_head(in_node);
    return head;
  } else if (insert_pos < 0) {
    return head;
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
  sll_size_count++;
  return head;
}

NODE *insert_node_as_tail(NODE *in_node) {
  tail = get_tail();
  if (in_node == NULL) {
    return head;
  }
  tail->next = in_node;
  in_node->next = NULL;
  tail = in_node;
  sll_size_count++;
  return head;
}

NODE *insert_node(NODE *insert_node) {
  if (head == NULL) {
    head = insert_node;
    tail = head;
    return head;
  }
  tail->next = insert_node;
  tail = insert_node;
  tail->next = NULL;
  return head;
}

NODE *get_node_position(NODE *node_pos) {
  NODE *found_node = NULL;
  found_node = head;
  if (is_empty()) {
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

NODE *get_previous_node(NODE *targ_node) {
  NODE *prev_node = NULL;
  prev_node = head;
  if (is_empty()) {
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

NODE *get_tail() {
  NODE *tail_node = NULL;
  tail_node = head;
  if (tail == NULL) {
    printf("get error: empty list");
  }
  while (tail_node->next != NULL) {
    tail_node = tail_node->next;
    if (tail_node->next == NULL) {
      return tail_node;
    }
  }
  return tail_node;
}

NODE *delete_node(NODE *del_node) {
  NODE *pre_node = NULL;
  if (del_node == NULL) {
    return head;
  }

  // 链表只有一个节点
  if (head != NULL && head->next == NULL) {
    head = NULL;
    tail = NULL;
    return head;
  }

  // 被删除节点为头节点
  if (del_node == head) {
    head = head->next;
    return head;
  }

  // 被删除节点为尾节点或者其他节点
  pre_node = get_previous_node(del_node);
  pre_node->next = pre_node->next->next;
  if (del_node == tail) {
    tail = pre_node;
  }
  return head;
}
