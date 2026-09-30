#include "single_circular_linkedlist.h"

NODE *sc_head = NULL;
NODE *sc_tail = NULL;
int size_count = 0;

NODE *init_single_circular_linkedlist() {
  sc_tail = sc_head;
  return sc_head;
}

bool is_empty_scll() {
  if (sc_head == NULL) {
    return true;
  }
  return false;
}

bool is_node_in_single_circular_linkedlist(NODE *search_node) {
  NODE *targ_node = NULL;
  targ_node = sc_head;
  do {
    if (targ_node == search_node) {
      return true;
    }
    targ_node = targ_node->next;
  } while (targ_node != sc_head);

  return false;
}

int size_of_single_circular_linkedlist() {
  NODE *size_node = sc_head;
  if (sc_head == NULL) {
    return 0;
  }
  do {
    size_count++;
    size_node = size_node->next;
  } while (size_node != sc_head);
  return size_count;
}

NODE *insert_node_as_head_in_single_circular_linkedlist(NODE *in_node) {
  in_node->next = sc_head;
  sc_head = in_node;
  sc_tail->next = sc_head;
  size_count++;
  return sc_head;
}

NODE *insert_node_after_head_in_single_circular_linkedlist(NODE *in_node) {
  if (in_node == NULL) {
    return sc_head;
  }
  in_node->next = sc_head->next;
  sc_head->next = in_node;
  size_count++;
  return sc_head;
}

NODE *insert_node_in_middle_single_circular_linkedlist(NODE *in_node,
                                                       int insert_pos) {
  NODE *middle_node = sc_head;
  NODE *found_node = NULL;
  if (in_node == NULL) {
    return sc_head;
  }
  if (insert_pos > size_count) {
    insert_node_after_head_in_single_circular_linkedlist(in_node);
    return sc_head;
  } else if (insert_pos < 0) {
    return sc_head;
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
  size_count++;
  return sc_head;
}

NODE *insert_node_as_tail_in_single_circular_linkedlist(NODE *in_node) {
  if (in_node == NULL) {
    return sc_head;
  }
  if (sc_tail == sc_head) {
    sc_tail = in_node;
    sc_head->next = sc_tail;
    sc_tail->next = sc_head;
  } else {
    sc_tail->next = in_node;
    in_node->next = sc_head;
    sc_tail = in_node;
  }
  size_count++;
  return sc_head;
}

NODE *insert_node_in_single_circular_linkedlist(NODE *in_node) {
  if (sc_head == NULL) {
    sc_head = in_node;
    sc_tail = sc_head;
    sc_head->next = sc_tail;
    sc_tail->next = sc_head;
    size_count++;
    return sc_head;
  }
  sc_tail->next = in_node;
  sc_tail = in_node;
  sc_tail->next = sc_head;
  size_count++;
  return sc_head;
}

NODE *get_node_position_in_single_circular_linkedlist(NODE *node_pos) {
  NODE *found_node = sc_head;
  if (is_empty_scll()) {
    return NULL;
  }
  if (node_pos == NULL) {
    return sc_head;
  }
  if (!is_node_in_single_circular_linkedlist(node_pos)) {
    return sc_head;
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
  return sc_head;
}

NODE *get_previous_node_in_single_circular_linkedlist(NODE *targ_node,
                                                      NODE *prev_node) {
  if (targ_node == NULL) {
    return NULL;
  }
  if (is_empty_scll() && !is_node_in_single_circular_linkedlist(targ_node)) {
    return NULL;
  }
  if (sc_head == sc_tail) {
    return sc_head;
  }
  while (prev_node->next != targ_node) {
    prev_node = prev_node->next;
    if (prev_node == sc_head) {
      return NULL;
    }
  }
  return prev_node;
}

NODE *delete_node_in_single_circular_linkedlist(NODE *del_node) {
  NODE *prev_node = NULL;
  if (del_node == NULL) {
    return sc_head;
  }

  if (!is_node_in_single_circular_linkedlist(del_node)) {
    printf("delete error: the node plan to delete not exist in the list.\n");
    return sc_head;
  }

  // 链表只有一个节点
  if (sc_head == sc_tail) {
    sc_head = NULL;
    sc_tail = NULL;
    return sc_head;
  }

  // 删除节点为头节点
  if (del_node == sc_head) {
    sc_tail->next = sc_head->next;
    sc_head = sc_head->next;
    return sc_head;
  }

  // 删除节点为其他节点和尾节点
  prev_node = sc_head;
  prev_node =
      get_previous_node_in_single_circular_linkedlist(del_node, prev_node);
  prev_node->next = del_node->next;
  if (del_node == sc_tail) {
    sc_tail = prev_node;
  }
  return sc_head;
}
