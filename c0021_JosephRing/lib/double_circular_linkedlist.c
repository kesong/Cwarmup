#include "double_circular_linkedlist.h"

NODE_DLL *dc_head = NULL;
NODE_DLL *dc_tail = NULL;
int dc_size_count = 0;

NODE_DLL *init_double_circular_linkedlist() {
  dc_tail = dc_head;
  dc_head->prev = dc_tail;
  dc_head->next = dc_tail;
  return dc_head;
}

bool is_empty_dcll() { return dc_head == NULL ? true : false; }

bool is_node_in_dcll(NODE_DLL *in_node) {
  NODE_DLL *targ_node = dc_head;
  while (targ_node != dc_tail) {
    if (in_node == targ_node) {
      return true;
    }
    if (targ_node->next != dc_tail) {
      targ_node = targ_node->next;
    } else
      break;
  }
  return false;
}

int size_of_dcll() {
  NODE_DLL *d_size_node = dc_head;
  // dc_size_count为全局变量，获取链表节点数量可以直接获取dc_size_count的值，调用这个函数来获取的话，要先将dc_size_count置为0
  dc_size_count = 0;
  if (dc_head == NULL) {
    return 0;
  }
  while (d_size_node != dc_tail) {
    dc_size_count++;
    d_size_node = d_size_node->next;
  }
  if (d_size_node == dc_tail) {
    return dc_size_count += 1;
  }
  return 0;
}

NODE_DLL *insert_node_as_head_dcll(NODE_DLL *in_node) {
  in_node->next = dc_head;
  in_node->prev = dc_tail;
  dc_head = in_node;
  dc_size_count++;
  return dc_head;
}

NODE_DLL *insert_node_after_head_dcll(NODE_DLL *in_node) {
  if (in_node == NULL) {
    return dc_head;
  }
  in_node->next = dc_head->next;
  in_node->prev = dc_head;
  dc_head->next = in_node;
  dc_size_count++;
  return dc_head;
}

NODE_DLL *insert_node_in_middle_dcll(NODE_DLL *in_node, int insert_pos) {
  NODE_DLL *middle_node = dc_head;
  NODE_DLL *found_node = NULL;
  if (in_node == NULL) {
    return dc_head;
  }
  if (insert_pos > dc_size_count) {
    insert_node_after_head_dcll(in_node);
    return dc_head;
  } else if (insert_pos < 0) {
    return dc_head;
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
  dc_size_count++;
  return dc_head;
}

NODE_DLL *insert_node_as_tail_dcll(NODE_DLL *in_node) {
  if (in_node == NULL) {
    return dc_head;
  }
  dc_tail->next = in_node;
  in_node->prev = dc_tail;
  in_node->next = dc_head;
  dc_tail = in_node;
  dc_size_count++;
  return dc_head;
}

NODE_DLL *insert_node_dcll(NODE_DLL *in_node) {
  if (dc_head == NULL) {
    dc_head = in_node;
    dc_tail = dc_head;
    dc_head->prev = dc_head;
    dc_head->next = dc_tail;
    dc_tail = dc_head;
    return dc_head;
  }
  if (in_node == NULL) {
    return dc_head;
  }
  dc_tail->next = in_node;
  dc_head->prev = in_node;
  in_node->prev = dc_tail;
  in_node->next = dc_head;
  dc_tail = in_node;
  dc_size_count++;
  return dc_head;
}

NODE_DLL *get_node_position_dcll(NODE_DLL *node_pos) {
  NODE_DLL *found_node = NULL;
  found_node = dc_head;
  if (is_empty_dcll()) {
    return NULL;
  }
  if (node_pos == NULL) {
    return NULL;
  }
  while (node_pos != dc_tail) {
    if (node_pos == found_node) {
      return found_node;
    }
    found_node = found_node->next;
  }
  if (node_pos == dc_tail) {
    return dc_tail;
  }
  return NULL;
}

NODE_DLL *delete_node_dcll(NODE_DLL *del_node) {
  if (del_node == NULL) {
    return dc_head;
  }

  // 链表只有一个节点
  if (dc_head == dc_tail) {
    dc_head->prev = NULL;
    dc_head->next = NULL;
    dc_head = NULL;
    return dc_head;
  }

  // 被删除节点为头节点
  if (del_node == dc_head) {
    dc_tail->next = dc_head->next;
    dc_head = dc_head->next;
    dc_head->prev = dc_tail;
    return dc_head;
  }

  // 被删除节点为其他节点或者尾节点
  del_node->next->prev = del_node->prev;
  del_node->prev->next = del_node->next;
  if (del_node == dc_tail) {
    dc_head->prev = dc_tail->prev;
    dc_tail->prev->next = dc_head;
    dc_tail = dc_tail->prev;
  }
  return dc_head;
}
