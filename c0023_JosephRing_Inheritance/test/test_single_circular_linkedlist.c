#include "test_single_circular_linkedlist.h"
#include "../lib/single_circular_linkedlist.h"
#include "test_and_validation.h"
#include <assert.h>
#include <stdlib.h>

NODE *node_0 = NULL;
NODE *node_1 = NULL;
NODE *node_3 = NULL;
NODE *node_8 = NULL;
NODE *node_10 = NULL;
NODE *node_11 = NULL;
NODE *node_14 = NULL;
NODE *node_21 = NULL;
NODE *node_23 = NULL;
NODE *node_33 = NULL;
NODE *node_45 = NULL;
NODE *node_91 = NULL;
NODE *node_321 = NULL;
NODE *node_1024 = NULL;
NODE *node_1201 = NULL;

void init_node() {
  // 这些函数内定义的局部变量一定要添加static类型，否则在测试代码中，从init_node函数退出后这些变量的内存空间可能就被回收了，再用指针指向
  // 这些变量时，取的值往往是比较随机的整型值
  // 如果不想用静态变量，就用指针，用malloc为整型指针分配空间，使用完后记住释放空间
  // int *zero = (int*)malloc(sizeof(int));
  // zero = 0;
  static int zero = 0, one = 1, three = 3, eight = 8, ten = 10, eleven = 11,
             fourteen = 14, twenty_one = 21, twenty_three = 23,
             thirty_three = 33, fourty_five = 45, ninety_one = 91,
             juglans_regia = 321, programmer = 1024, pine_nut = 1201;
  node_0 = (NODE *)malloc(sizeof(NODE));
  node_0->node_data = &zero, node_0->next = NULL;
  node_1 = (NODE *)malloc(sizeof(NODE));
  node_1->node_data = &one, node_1->next = NULL;
  node_3 = (NODE *)malloc(sizeof(NODE));
  node_3->node_data = &three, node_3->next = NULL;
  node_8 = (NODE *)malloc(sizeof(NODE));
  node_8->node_data = &eight, node_8->next = NULL;
  node_10 = (NODE *)malloc(sizeof(NODE));
  node_10->node_data = &ten, node_10->next = NULL;
  node_11 = (NODE *)malloc(sizeof(NODE));
  node_11->node_data = &eleven, node_11->next = NULL;
  node_14 = (NODE *)malloc(sizeof(NODE));
  node_14->node_data = &fourteen, node_14->next = NULL;
  node_21 = (NODE *)malloc(sizeof(NODE));
  node_21->node_data = &twenty_one, node_21->next = NULL;
  node_23 = (NODE *)malloc(sizeof(NODE));
  node_23->node_data = &twenty_three, node_23->next = NULL;
  node_33 = (NODE *)malloc(sizeof(NODE));
  node_33->node_data = &thirty_three, node_33->next = NULL;
  node_45 = (NODE *)malloc(sizeof(NODE));
  node_45->node_data = &fourty_five, node_45->next = NULL;
  node_91 = (NODE *)malloc(sizeof(NODE));
  node_91->node_data = &ninety_one, node_91->next = NULL;
  node_321 = (NODE *)malloc(sizeof(NODE));
  node_321->node_data = &juglans_regia, node_321->next = NULL;
  node_1024 = (NODE *)malloc(sizeof(NODE));
  node_1024->node_data = &programmer, node_1024->next = NULL;
  node_1201 = (NODE *)malloc(sizeof(NODE));
  node_1201->node_data = &pine_nut, node_1201->next = NULL;
}

void free_node() {
  if (node_0 != NULL) {
    free(node_0);
  }
  if (node_1 != NULL) {
    free(node_1);
  }
  if (node_3 != NULL) {
    free(node_3);
  }
  if (node_8 != NULL) {
    free(node_8);
  }
  if (node_10 != NULL) {
    free(node_10);
  }
  if (node_11 != NULL) {
    free(node_11);
  }
  if (node_14 != NULL) {
    free(node_14);
  }
  if (node_21 != NULL) {
    free(node_21);
  }
  if (node_23 != NULL) {
    free(node_23);
  }
  if (node_33 != NULL) {
    free(node_33);
  }
  if (node_45 != NULL) {
    free(node_45);
  }
  if (node_91 != NULL) {
    free(node_91);
  }
  if (node_321 != NULL) {
    free(node_321);
  }
  if (node_1024 != NULL) {
    free(node_1024);
  }
  if (node_1201 != NULL) {
    free(node_1201);
  }
  node_0 = NULL, node_1 = NULL, node_3 = NULL, node_8 = NULL, node_10 = NULL,
  node_11 = NULL, node_14 = NULL, node_21 = NULL, node_23 = NULL,
  node_33 = NULL, node_45 = NULL, node_91 = NULL, node_321 = NULL,
  node_1024 = NULL, node_1201 = NULL;
}

SCLinkedlist *init_single_circular_linkedlist() {
  init_node();
  SCLinkedlist *scllist = create_single_circular_linkedlist();
  single_circular_linkedlist_constructor(scllist, NULL, NULL, 0,
                                         scllist->super);
  scllist->super->insert_node_sll(scllist, node_0);
  scllist->super->insert_node_sll(scllist, node_1);
  scllist->super->insert_node_sll(scllist, node_3);
  scllist->super->insert_node_sll(scllist, node_8);
  scllist->super->insert_node_sll(scllist, node_10);
  scllist->super->insert_node_sll(scllist, node_11);
  scllist->super->insert_node_sll(scllist, node_14);
  scllist->super->insert_node_sll(scllist, node_21);
  scllist->super->insert_node_sll(scllist, node_23);
  scllist->super->insert_node_sll(scllist, node_33);
  scllist->super->insert_node_sll(scllist, node_45);
  scllist->super->insert_node_sll(scllist, node_91);
  scllist->super->insert_node_sll(scllist, node_321);
  scllist->super->insert_node_sll(scllist, node_1024);
  scllist->super->insert_node_sll(scllist, node_1201);
  return scllist;
}

TestResult test_is_empty() {
  SCLinkedlist *scllist = create_single_circular_linkedlist();
  single_circular_linkedlist_constructor(scllist, NULL, NULL, 0,
                                         scllist->super);
  assert(scllist->super->head == NULL);
  assert(scllist->super->tail == NULL);
  scllist->super->destroy_sll(scllist);
  return TEST_PASSED;
}

TestResult test_insert_node() {
  init_node();
  SCLinkedlist *scllist = create_single_circular_linkedlist();
  single_circular_linkedlist_constructor(scllist, NULL, NULL, 0,
                                         scllist->super);
  scllist->super->insert_node_sll(scllist, node_23);
  assert(scllist->super->head == node_23);
  assert(scllist->super->tail == scllist->super->head);
  scllist->super->insert_at_the_end(scllist, node_10);
  assert(scllist->super->tail == node_10);
  assert(scllist->super->tail->next == scllist->super->head);
  free_node();
  scllist->super->destroy_sll(scllist);
  return TEST_PASSED;
}

TestResult test_delete_node() {
  init_node();
  SCLinkedlist *scllist = create_single_circular_linkedlist();
  single_circular_linkedlist_constructor(scllist, NULL, NULL, 0,
                                         scllist->super);
  scllist->super->insert_node_sll(scllist, node_10);
  scllist->super->insert_node_sll(scllist, node_23);
  scllist->super->insert_node_sll(scllist, node_1);
  assert(scllist->super->head == node_10);
  int head_v = *(int *)scllist->super->head->node_data;
  int v10 = *(int *)node_10->node_data;
  assert(head_v == v10);
  int tail_v = *(int *)scllist->super->tail->node_data;
  int v1 = *(int *)node_1->node_data;
  assert(scllist->super->tail == node_1);
  assert(tail_v == v1);
  int v23_next = *(int *)node_23->next->node_data;
  assert(node_23->next == node_1);
  assert(v23_next == v1);
  scllist->super->insert_node_sll(scllist, node_1024);
  int v1024 = *(int *)node_1024->node_data;
  assert(scllist->super->tail == node_1024);
  tail_v = *(int *)scllist->super->tail->node_data;
  assert(tail_v == v1024);
  int v1024_next = *(int *)node_1024->next->node_data;
  assert(node_1024->next == scllist->super->head);
  assert(v1024_next == head_v);
  scllist->super->delete_node_sll(scllist, node_1024);
  tail_v = *(int *)scllist->super->tail->node_data;
  v1 = *(int *)node_1->node_data;
  assert(scllist->super->tail == node_1);
  assert(tail_v == v1);
  int v1_next = *(int *)node_1->next->node_data;
  head_v = *(int *)scllist->super->head->node_data;
  assert(node_1->next == scllist->super->head);
  assert(v1_next == head_v);
  free_node();
  scllist->super->destroy_sll(scllist);
  return TEST_PASSED;
}

TestResult test_create_single_circular_linkedlist() {
  SCLinkedlist *scllist = create_single_circular_linkedlist();
  single_circular_linkedlist_constructor(scllist, NULL, NULL, 0,
                                         scllist->super);
  scllist = init_single_circular_linkedlist();
  NODE *test_head = scllist->super->head;
  NODE *test_tail = scllist->super->tail;
  assert(test_head == node_0);
  int test_headv = *(int *)test_head->node_data;
  int v0 = *(int *)node_0->node_data;
  assert(test_headv == v0);

  int v23_next = *(int *)node_23->next->node_data;
  int v33 = *(int *)node_33->node_data;
  assert(v23_next == v33);

  int v91_next = *(int *)node_91->next->node_data;
  int v321 = *(int *)node_321->node_data;
  assert(v91_next == v321);

  assert(test_tail == scllist->super->tail);
  int test_tailv = *(int *)test_tail->node_data;
  int v1201 = *(int *)node_1201->node_data;
  assert(test_tailv == v1201);

  assert(scllist->super->tail->next == scllist->super->head);
  int tailv_next = *(int *)scllist->super->tail->next->node_data;
  assert(tailv_next == test_headv);
  free_node();
  scllist->super->destroy_sll(scllist);
  return TEST_PASSED;
}
