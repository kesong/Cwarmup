#include "test_single_linkedlist.h"
#include "test_single_circular_linkedlist.h"
#include <assert.h>
#include <stdbool.h>

extern NODE *node_0;
extern NODE *node_1;
extern NODE *node_3;
extern NODE *node_8;
extern NODE *node_10;
extern NODE *node_11;
extern NODE *node_14;
extern NODE *node_21;
extern NODE *node_23;
extern NODE *node_33;
extern NODE *node_45;

int v0;
int v1;
int v3;
int v8;
int v10;
int v11;
int v14;
int v21;
int v23;
int v33;
int v45;

void init_node_value() {
  init_node();
  v0 = *(int *)node_0->node_data;
  v1 = *(int *)node_1->node_data;
  v3 = *(int *)node_3->node_data;
  v8 = *(int *)node_8->node_data;
  v10 = *(int *)node_10->node_data;
  v11 = *(int *)node_11->node_data;
  v14 = *(int *)node_14->node_data;
  v21 = *(int *)node_21->node_data;
  v23 = *(int *)node_23->node_data;
  v33 = *(int *)node_33->node_data;
  v45 = *(int *)node_45->node_data;
}

SingleLinkedlist *init_single_linkedlist() {
  init_node();
  SingleLinkedlist *sllist = create_single_linkedlist();
  single_linkedlist_constructor(sllist, NULL, NULL, 0);
  sllist->insert_node_sll(sllist, node_0);
  sllist->insert_node_sll(sllist, node_1);
  sllist->insert_node_sll(sllist, node_3);
  sllist->insert_node_sll(sllist, node_8);
  sllist->insert_node_sll(sllist, node_10);
  sllist->insert_node_sll(sllist, node_11);
  sllist->insert_node_sll(sllist, node_14);
  sllist->insert_node_sll(sllist, node_21);
  sllist->insert_node_sll(sllist, node_23);
  sllist->insert_node_sll(sllist, node_33);
  sllist->insert_node_sll(sllist, node_45);
  return sllist;
}

TestResult test_insert_node_to_empty_sll() {
  init_node_value();
  SingleLinkedlist *sllist = create_single_linkedlist();
  single_linkedlist_constructor(sllist, NULL, NULL, 0);
  sllist->insert_node_sll(sllist, node_14);
  assert(sllist->head == node_14);
  int headv = *(int *)sllist->head->node_data;
  assert(headv == v14);
  assert(sllist->tail == node_14);
  int tailv = *(int *)sllist->tail->node_data;
  assert(tailv == v14);
  free_node();
  sllist->destroy_sll(sllist);
  return TEST_PASSED;
}

TestResult test_insert_node_in_sll() {
  // node_xx这些节点分配内存空间
  init_node_value();
  SingleLinkedlist *sllist = create_single_linkedlist();
  single_linkedlist_constructor(sllist, NULL, NULL, 0);
  // 再次调用了init_node第二次为这些node分配了空间，并且会覆盖第一次分配的地址，导致第一次的地址丢失，无法回收，造成内存泄漏
  // 将init_node_value()合并到init_node()中去，同一个变量只做一次内存分配，避免造成第一次分配的地址被覆盖，且第一次分配的空间未回收，带来内存泄漏的风险
  sllist = init_single_linkedlist();
  NODE *test_head = sllist->head;
  assert(test_head == node_0);
  int thv = *(int *)test_head->node_data;
  assert(v0 == thv);
  free_node();
  sllist->destroy_sll(sllist);
  return TEST_PASSED;
}

TestResult test_get_tail() {
  init_node_value();
  SingleLinkedlist *sllist = create_single_linkedlist();
  single_linkedlist_constructor(sllist, NULL, NULL, 0);
  sllist = init_single_linkedlist();
  NODE *test_head = sllist->head;
  NODE *test_tail = NULL;
  sllist->delete_node_sll(sllist, node_45);
  test_tail = get_tail(sllist);
  assert(sllist->tail == node_33);
  int tailv = *(int *)sllist->tail->node_data;
  assert(tailv == v33);
  free_node();
  destroy_single_linkedlist(sllist);
  return TEST_PASSED;
}

TestResult test_delete_node_in_scll() {
  init_node_value();
  SingleLinkedlist *sllist = create_single_linkedlist();
  single_linkedlist_constructor(sllist, NULL, NULL, 0);
  sllist = init_single_linkedlist();
  NODE *test_head = sllist->head;
  sllist->delete_node_sll(sllist, node_11);
  assert(node_10->next == node_14);
  int v10n = *(int *)node_10->next->node_data;
  assert(v10n == v14);
  free_node();
  destroy_single_linkedlist(sllist);
  return TEST_PASSED;
}
