#include "test_double_linkedlist.h"
#include "test_and_validation.h"
#include <assert.h>
#include <stdlib.h>

// extern NODE_DLL *d_head;
// extern NODE_DLL *d_tail;

NODE_DLL *node_dll_0 = NULL;
NODE_DLL *node_dll_1 = NULL;
NODE_DLL *node_dll_3 = NULL;
NODE_DLL *node_dll_8 = NULL;
NODE_DLL *node_dll_10 = NULL;
NODE_DLL *node_dll_11 = NULL;
NODE_DLL *node_dll_14 = NULL;
NODE_DLL *node_dll_21 = NULL;
NODE_DLL *node_dll_23 = NULL;
NODE_DLL *node_dll_33 = NULL;
NODE_DLL *node_dll_45 = NULL;
NODE_DLL *node_dll_91 = NULL;
NODE_DLL *node_dll_321 = NULL;
NODE_DLL *node_dll_1024 = NULL;
NODE_DLL *node_dll_1201 = NULL;

void init_node_dll() {
  // 这些函数内定义的局部变量一定要添加static类型，否则在测试代码中，从init_node函数退出后这些变量的内存空间可能就被回收了，再用指针指向
  // 这些变量时，取的值往往是比较随机的整型值
  // 如果不想用静态变量，就用指针，用malloc为整型指针分配空间，使用完后记住释放空间
  // int *zero = (int*)malloc(sizeof(int));
  // zero = 0;
  static int zero = 0, one = 1, three = 3, eight = 8, ten = 10, eleven = 11,
             fourteen = 14, twenty_one = 21, twenty_three = 23,
             thirty_three = 33, fourty_five = 45, ninety_one = 91,
             juglans_regia = 321, programmer = 1024, pine_nut = 1201;
  node_dll_0 = (NODE_DLL *)malloc(sizeof(NODE_DLL));
  node_dll_0->node_data = &zero, node_dll_0->next = NULL,
  node_dll_0->prev = NULL;
  node_dll_1 = (NODE_DLL *)malloc(sizeof(NODE_DLL));
  node_dll_1->node_data = &one, node_dll_1->next = NULL,
  node_dll_1->prev = NULL;
  node_dll_3 = (NODE_DLL *)malloc(sizeof(NODE_DLL));
  node_dll_3->node_data = &three, node_dll_3->next = NULL,
  node_dll_3->prev = NULL;
  node_dll_8 = (NODE_DLL *)malloc(sizeof(NODE_DLL));
  node_dll_8->node_data = &eight, node_dll_8->next = NULL,
  node_dll_8->prev = NULL;
  node_dll_10 = (NODE_DLL *)malloc(sizeof(NODE_DLL));
  node_dll_10->node_data = &ten, node_dll_10->next = NULL,
  node_dll_10->prev = NULL;
  node_dll_11 = (NODE_DLL *)malloc(sizeof(NODE_DLL));
  node_dll_11->node_data = &eleven, node_dll_11->next = NULL,
  node_dll_11->prev = NULL;
  node_dll_14 = (NODE_DLL *)malloc(sizeof(NODE_DLL));
  node_dll_14->node_data = &fourteen, node_dll_14->next = NULL,
  node_dll_14->prev = NULL;
  node_dll_21 = (NODE_DLL *)malloc(sizeof(NODE_DLL));
  node_dll_21->node_data = &twenty_one, node_dll_21->next = NULL,
  node_dll_21->prev = NULL;
  node_dll_23 = (NODE_DLL *)malloc(sizeof(NODE_DLL));
  node_dll_23->node_data = &twenty_three, node_dll_23->next = NULL,
  node_dll_23->prev = NULL;
  node_dll_33 = (NODE_DLL *)malloc(sizeof(NODE_DLL));
  node_dll_33->node_data = &thirty_three, node_dll_33->next = NULL,
  node_dll_33->prev = NULL;
  node_dll_45 = (NODE_DLL *)malloc(sizeof(NODE_DLL));
  node_dll_45->node_data = &fourty_five, node_dll_45->next = NULL,
  node_dll_45->prev = NULL;
  node_dll_91 = (NODE_DLL *)malloc(sizeof(NODE_DLL));
  node_dll_91->node_data = &ninety_one, node_dll_91->next = NULL,
  node_dll_91->prev = NULL;
  node_dll_321 = (NODE_DLL *)malloc(sizeof(NODE_DLL));
  node_dll_321->node_data = &juglans_regia, node_dll_321->next = NULL,
  node_dll_321->prev = NULL;
  node_dll_1024 = (NODE_DLL *)malloc(sizeof(NODE_DLL));
  node_dll_1024->node_data = &programmer, node_dll_1024->next = NULL,
  node_dll_1024->prev = NULL;
  node_dll_1201 = (NODE_DLL *)malloc(sizeof(NODE_DLL));
  node_dll_1201->node_data = &pine_nut, node_dll_1201->next = NULL,
  node_dll_1201->prev = NULL;
}

int dll_v0;
int dll_v1;
int dll_v3;
int dll_v8;
int dll_v10;
int dll_v11;
int dll_v14;
int dll_v21;
int dll_v23;
int dll_v33;
int dll_v45;

void init_node_value_dll() {
  init_node_dll();
  dll_v0 = *(int *)node_dll_0->node_data;
  dll_v1 = *(int *)node_dll_1->node_data;
  dll_v3 = *(int *)node_dll_3->node_data;
  dll_v8 = *(int *)node_dll_8->node_data;
  dll_v10 = *(int *)node_dll_10->node_data;
  dll_v11 = *(int *)node_dll_11->node_data;
  dll_v14 = *(int *)node_dll_14->node_data;
  dll_v21 = *(int *)node_dll_21->node_data;
  dll_v23 = *(int *)node_dll_23->node_data;
  dll_v33 = *(int *)node_dll_33->node_data;
  dll_v45 = *(int *)node_dll_45->node_data;
}

void free_node_dll() {
  if (node_dll_0 != NULL) {
    free(node_dll_0);
  }
  if (node_dll_1 != NULL) {
    free(node_dll_1);
  }
  if (node_dll_3 != NULL) {
    free(node_dll_3);
  }
  if (node_dll_8 != NULL) {
    free(node_dll_8);
  }
  if (node_dll_10 != NULL) {
    free(node_dll_10);
  }
  if (node_dll_11 != NULL) {
    free(node_dll_11);
  }
  if (node_dll_14 != NULL) {
    free(node_dll_14);
  }
  if (node_dll_21 != NULL) {
    free(node_dll_21);
  }
  if (node_dll_23 != NULL) {
    free(node_dll_23);
  }
  if (node_dll_33 != NULL) {
    free(node_dll_33);
  }
  if (node_dll_45 != NULL) {
    free(node_dll_45);
  }
  if (node_dll_91 != NULL) {
    free(node_dll_91);
  }
  if (node_dll_321 != NULL) {
    free(node_dll_321);
  }
  if (node_dll_1024 != NULL) {
    free(node_dll_1024);
  }
  if (node_dll_1201 != NULL) {
    free(node_dll_1201);
  }
  node_dll_0 = NULL, node_dll_1 = NULL, node_dll_3 = NULL, node_dll_8 = NULL,
  node_dll_10 = NULL, node_dll_11 = NULL, node_dll_14 = NULL,
  node_dll_21 = NULL, node_dll_23 = NULL, node_dll_33 = NULL,
  node_dll_45 = NULL, node_dll_91 = NULL, node_dll_321 = NULL,
  node_dll_1024 = NULL, node_dll_1201 = NULL;
}

DoubleLinkedList d_linkedlist;
DoubleLinkedList init_double_linkedlist() {
  d_linkedlist.head_node = NULL;
  d_linkedlist.tail_node = NULL;
  d_linkedlist.init_head_of_linkedlist = init_head_of_linkedlist;
  d_linkedlist.is_empty_dll = NULL;
  d_linkedlist.is_node_in_list = NULL;
  d_linkedlist.size_of_dll = NULL;
  d_linkedlist.insert_node_as_head_dll = NULL;
  d_linkedlist.insert_node_after_head_dll = NULL;
  d_linkedlist.insert_node_in_middle_dll = NULL;
  d_linkedlist.insert_node_as_tail_dll = NULL;
  d_linkedlist.insert_node_dll = insert_node_dll;
  d_linkedlist.get_node_position_dll = NULL;
  d_linkedlist.delete_node_dll = delete_node_dll;
  return d_linkedlist;
}

DoubleLinkedList create_double_linkedlist() {
  init_node_dll();
  d_linkedlist.head_node = NULL;
  d_linkedlist.tail_node = NULL;

  d_linkedlist.insert_node_dll(d_linkedlist, node_dll_0);
  d_linkedlist.insert_node_dll(d_linkedlist, node_dll_1);
  d_linkedlist.insert_node_dll(d_linkedlist, node_dll_3);
  d_linkedlist.insert_node_dll(d_linkedlist, node_dll_8);
  d_linkedlist.insert_node_dll(d_linkedlist, node_dll_10);
  d_linkedlist.insert_node_dll(d_linkedlist, node_dll_11);
  d_linkedlist.insert_node_dll(d_linkedlist, node_dll_14);
  d_linkedlist.insert_node_dll(d_linkedlist, node_dll_21);
  d_linkedlist.insert_node_dll(d_linkedlist, node_dll_23);
  d_linkedlist.insert_node_dll(d_linkedlist, node_dll_33);
  d_linkedlist.insert_node_dll(d_linkedlist, node_dll_45);
  d_linkedlist.insert_node_dll(d_linkedlist, node_dll_91);
  d_linkedlist.insert_node_dll(d_linkedlist, node_dll_321);
  d_linkedlist.insert_node_dll(d_linkedlist, node_dll_1024);
  d_linkedlist.insert_node_dll(d_linkedlist, node_dll_1201);
  d_linkedlist.insert_node_dll(d_linkedlist, node_dll_0);
  d_linkedlist.insert_node_dll(d_linkedlist, node_dll_0);
  return d_linkedlist;
}

TestResult test_insert_node_to_empty_dll() {
  init_node_value_dll();
  d_linkedlist = init_double_linkedlist();
  d_linkedlist = d_linkedlist.insert_node_dll(d_linkedlist, node_dll_14);
  assert(d_linkedlist.head_node == node_dll_14);
  int headv = *(int *)(d_linkedlist.head_node)->node_data;
  assert(headv == dll_v14);
  free_node_dll();
  return TEST_PASSED;
}

TestResult test_insert_node_to_dll() {
  init_node_value_dll();
  d_linkedlist = init_double_linkedlist();

  d_linkedlist = d_linkedlist.insert_node_dll(d_linkedlist, node_dll_23);
  assert(d_linkedlist.head_node == node_dll_23);
  int headv = *(int *)d_linkedlist.head_node->node_data;
  assert(headv == dll_v23);

  d_linkedlist = d_linkedlist.insert_node_dll(d_linkedlist, node_dll_0);
  assert(d_linkedlist.tail_node == node_dll_0);
  int tailv = *(int *)d_linkedlist.tail_node->node_data;
  assert(tailv == dll_v0);

  d_linkedlist = d_linkedlist.insert_node_dll(d_linkedlist, node_dll_10);
  assert(d_linkedlist.tail_node == node_dll_10);
  tailv = *(int *)d_linkedlist.tail_node->node_data;
  assert(tailv == dll_v10);

  d_linkedlist = d_linkedlist.insert_node_dll(d_linkedlist, node_dll_33);
  assert(d_linkedlist.tail_node == node_dll_33);
  tailv = *(int *)d_linkedlist.tail_node->node_data;
  assert(tailv == dll_v33);

  free_node_dll();
  return TEST_PASSED;
}

TestResult test_delete_node_dll() {
  init_node_value_dll();
  DoubleLinkedList test_dll = init_double_linkedlist();
  test_dll = create_double_linkedlist();
  NODE_DLL *test_tail = d_linkedlist.tail_node;
  assert(test_dll.head_node == node_dll_0);
  assert(test_tail == node_dll_0);
  int headv = *(int *)d_linkedlist.head_node->node_data;
  assert(headv == dll_v0);

  d_linkedlist = d_linkedlist.delete_node_dll(d_linkedlist, node_dll_23);
  assert(node_dll_21->next == node_dll_33);
  int dll_v21n = *(int *)node_dll_21->next->node_data;
  assert(dll_v21n == dll_v33);

  d_linkedlist =
      d_linkedlist.delete_node_dll(d_linkedlist, d_linkedlist.head_node);
  assert(d_linkedlist.head_node == node_dll_1);

  d_linkedlist = d_linkedlist.delete_node_dll(d_linkedlist, node_dll_0);
  assert(node_dll_1201->next == node_dll_0);

  d_linkedlist = d_linkedlist.delete_node_dll(d_linkedlist, node_dll_0);
  assert(node_dll_1201->next == NULL);
  assert(d_linkedlist.tail_node == node_dll_1201);

  d_linkedlist =
      d_linkedlist.delete_node_dll(d_linkedlist, d_linkedlist.tail_node);
  assert(node_dll_1024->next == NULL);

  free_node_dll();
  return TEST_PASSED;
}
