#include "test_single_linkedlist.h"
#include "../lib/single_linkedlist.h"
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

void destroy_node() {
  head = NULL;
  tail = NULL;
}

NODE *create_single_linkedlist() {
  init_node();
  insert_node(node_0);
  insert_node(node_1);
  insert_node(node_3);
  insert_node(node_8);
  insert_node(node_10);
  insert_node(node_11);
  insert_node(node_14);
  insert_node(node_21);
  insert_node(node_23);
  insert_node(node_33);
  insert_node(node_45);
  return head;
}

TestResult test_insert_node_to_empty_sll() {
  init_node_value();
  insert_node(node_14);
  assert(head == node_14);
  int headv = *(int *)head->node_data;
  assert(headv == v14);
  assert(tail == node_14);
  int tailv = *(int *)tail->node_data;
  assert(tailv == v14);
  free_node();
  destroy_node();
  return TEST_PASSED;
}

TestResult test_insert_node_in_sll() {
  init_node_value();
  NODE *test_head = create_single_linkedlist();
  assert(test_head == node_0);
  int thv = *(int *)test_head->node_data;
  assert(v0 == thv);
  free_node();
  destroy_node();
  return TEST_PASSED;
}

TestResult test_get_tail() {
  init_node_value();
  NODE *test_head = create_single_linkedlist();
  NODE *test_tail = NULL;
  delete_node(node_45);
  test_tail = get_tail();
  assert(tail == node_33);
  int tailv = *(int *)tail->node_data;
  assert(tailv == v33);
  free_node();
  destroy_node();
  return TEST_PASSED;
}

TestResult test_delete_node_in_scll() {
  init_node_value();
  NODE *test_head = create_single_linkedlist();
  delete_node(node_11);
  assert(node_10->next == node_14);
  int v10n = *(int *)node_10->next->node_data;
  assert(v10n == v14);
  free_node();
  destroy_node();
  return TEST_PASSED;
}
