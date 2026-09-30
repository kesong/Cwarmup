#include "double_linkedlist.h"

NODE_DLL *d_head = NULL;
NODE_DLL *d_tail = NULL;
int d_size_count = 0;

NODE_DLL *init_double_linkedlist() {
  d_tail = d_head;
  return d_head;
}

bool is_empty_dll() { return d_head == NULL ? true : false; }

bool is_node_in_dll(NODE_DLL *in_node) {
  NODE_DLL *targ_node = d_head;
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

int size_of_dll() {
  NODE_DLL *d_size_node = d_head;
  d_size_count = 0;
  if (d_head == NULL) {
    return 0;
  }
  while (d_size_node != NULL) {
    d_size_count++;
    if (d_size_node->next == NULL) {
      return d_size_count;
    }
    d_size_node = d_size_node->next;
  }
  return 0;
}

NODE_DLL *insert_node_as_head_dll(NODE_DLL *in_node) {
  in_node->next = d_head;
  in_node->prev = d_tail;
  d_head = in_node;
  d_size_count++;
  return d_head;
}

NODE_DLL *insert_node_after_head_dll(NODE_DLL *in_node) {
  if (in_node == NULL) {
    return d_head;
  }
  in_node->next = d_head->next;
  in_node->prev = d_head;
  d_head->next = in_node;
  d_size_count++;
  return d_head;
}

NODE_DLL *insert_node_in_middle_dll(NODE_DLL *in_node, int insert_pos) {
  NODE_DLL *middle_node = d_head;
  NODE_DLL *found_node = NULL;
  if (in_node == NULL) {
    return d_head;
  }
  if (insert_pos > d_size_count) {
    insert_node_after_head_dll(in_node);
    return d_head;
  } else if (insert_pos < 0) {
    return d_head;
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
  d_size_count++;
  return d_head;
}

NODE_DLL *insert_node_as_tail_dll(NODE_DLL *in_node) {
  if (in_node == NULL) {
    return d_head;
  }
  d_tail->next = in_node;
  in_node->prev = d_tail;
  in_node->next = d_head;
  d_tail = in_node;
  d_size_count++;
  return d_head;
}

NODE_DLL *insert_node_dll(NODE_DLL *in_node) {
  if (d_head == NULL) {
    d_head = in_node;
    d_head->prev = NULL;
    d_head->next = NULL;
    d_tail = d_head;
    return d_head;
  }
  if (in_node == NULL) {
    return d_head;
  }
  d_tail->next = in_node;
  in_node->prev = d_tail;
  d_tail = in_node;
  d_size_count++;
  return d_head;
}

NODE_DLL *get_node_position_dll(NODE_DLL *node_pos) {
  NODE_DLL *found_node = NULL;
  found_node = d_head;
  if (is_empty_dll()) {
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

NODE_DLL *delete_node_dll(NODE_DLL *del_node) {
  if (del_node == NULL) {
    return d_head;
  }

  // 链表只有一个节点
  if (d_head == d_tail) {
    d_head = NULL;
    return d_head;
  }

  // 被删除节点为头节点
  if (del_node == d_head) {
    d_head = d_head->next;
    d_head->prev = NULL;
    return d_head;
  }

  // 被删除节点为其他节点或者尾节点
  del_node->prev->next = del_node->next;
  del_node->next->prev = del_node->prev;
  if (del_node == d_tail) {
    d_tail = del_node->prev;
    d_tail->next = NULL;
  }
  return d_head;
}
