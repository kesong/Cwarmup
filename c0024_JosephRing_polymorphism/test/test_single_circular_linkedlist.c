#include "test_single_circular_linkedlist.h"
#include "../lib/single_circular_linkedlist.h"
#include "data_process.h"
#include "test_and_validation.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// 测试数据
//  0, 1, 3, 8, 10, 11, 14, 21, 23, 33, 45, 91, 321, 1024, 1201
int v0 = 0;
int v1 = 1;
int v3 = 3;
int v8 = 8;
int v10 = 10;
int v11 = 11;
int v14 = 14;
int v21 = 21;
int v23 = 23;
int v33 = 33;
int v45 = 45;
int v321 = 321;
int v1024 = 1024;
int v1201 = 1201;

SCLinkedlist *init_single_circular_linkedlist() {
  SCLinkedlist *scllist = create_single_circular_linkedlist();
  single_circular_linkedlist_constructor(
      scllist, NULL, NULL, 0, &insert_node_scll, &delete_node_scll,
      &destroy_single_circular_linkedlist, "SCLinkedlist", &set_name_scll,
      &get_name_scll, &scll_toString);
  Linkedlist *llist = (Linkedlist *)scllist;

  NODE *node_array = NULL;
  NODE *node_arr[ARRAY_SIZE] = {NULL};
  node_array = convert_node_array(node_arr);
  for (int i = 0; i < ARRAY_SIZE; i++) {
    llist->insert_node(scllist, (node_array + i));
  }
  return scllist;
}

TestResult test_is_empty() {
  SCLinkedlist *scllist = create_single_circular_linkedlist();
  single_circular_linkedlist_constructor(
      scllist, NULL, NULL, 0, &insert_node_scll, &delete_node_scll,
      &destroy_single_circular_linkedlist, "SCLinkedlist", &set_name_scll,
      &get_name_scll, &scll_toString);
  /*
  single_circular_linkedlist_constructor(scllist, NULL, NULL, 0,
                                         &insert_node_scll, &delete_node_scll,
                                         &destroy_single_circular_linkedlist);
*/
  Linkedlist *llist = (Linkedlist *)scllist;
  assert(llist->head == NULL);
  assert(llist->tail == NULL);
  llist->destroy_ll(scllist);
  return TEST_PASSED;
}

TestResult test_insert_node() {
  SCLinkedlist *scllist = create_single_circular_linkedlist();
  single_circular_linkedlist_constructor(
      scllist, NULL, NULL, 0, &insert_node_scll, &delete_node_scll,
      &destroy_single_circular_linkedlist, "SCLinkedlist", &set_name_scll,
      &get_name_scll, &scll_toString);
  /*
  single_circular_linkedlist_constructor(scllist, NULL, NULL, 0,
                                         &insert_node_scll, &delete_node_scll,
                                         &destroy_single_circular_linkedlist);
*/
  NODE *node_array = NULL;
  NODE *node_arr[ARRAY_SIZE] = {NULL};
  node_array = convert_node_array(node_arr);
  scllist->super.insert_node(scllist, (node_array + 8));
  assert(scllist->super.head == node_array + 8);
  assert(scllist->super.tail == scllist->super.head);
  insert_node_as_tail_in_scll(scllist, (node_array + 4));
  assert(scllist->super.tail == (node_array + 4));
  assert(((NODE *)scllist->super.tail)->next == scllist->super.head);
  free_node_in_array(node_array);
  scllist->super.destroy_ll(scllist);
  return TEST_PASSED;
}

TestResult test_delete_node() {
  SCLinkedlist *scllist = create_single_circular_linkedlist();
  single_circular_linkedlist_constructor(
      scllist, NULL, NULL, 0, &insert_node_scll, &delete_node_scll,
      &destroy_single_circular_linkedlist, "SCLinkedlist", &set_name_scll,
      &get_name_scll, &scll_toString);
  /*
  single_circular_linkedlist_constructor(scllist, NULL, NULL, 0,
                                         &insert_node_scll, &delete_node_scll,
                                         &destroy_single_circular_linkedlist);
*/
  NODE *node_array = NULL;
  NODE *node_arr[ARRAY_SIZE] = {NULL};
  node_array = convert_node_array(node_arr);
  scllist->super.insert_node(scllist, (node_array + 4));
  scllist->super.insert_node(scllist, (node_array + 8));
  scllist->super.insert_node(scllist, (node_array + 1));
  assert(scllist->super.head == (node_array + 4));

  int head_v = *(int *)((NODE *)scllist->super.head)->node_data;
  assert(head_v == v10);

  int tail_v = *(int *)((NODE *)scllist->super.tail)->node_data;
  assert(scllist->super.tail == (node_array + 1));
  assert(tail_v == v1);

  int v23_next = *(int *)(node_array + 8)->next->node_data;
  assert((node_array + 8)->next == (node_array + 1));
  assert(v23_next == v1);

  scllist->super.insert_node(scllist, node_array + 13);
  assert(scllist->super.tail == (node_array + 13));

  tail_v = *(int *)((NODE *)scllist->super.tail)->node_data;
  assert(tail_v == v1024);

  int v1024_next = *(int *)(node_array + 13)->next->node_data;
  assert((node_array + 13)->next == scllist->super.head);
  assert(v1024_next == head_v);

  scllist->super.delete_node(scllist, node_array + 13);
  tail_v = *(int *)((NODE *)scllist->super.tail)->node_data;
  assert(scllist->super.tail == (node_array + 1));
  assert(tail_v == v1);

  int v1_next = *(int *)(node_array + 1)->next->node_data;
  head_v = *(int *)((NODE *)scllist->super.head)->node_data;
  assert((node_array + 1)->next == scllist->super.head);
  assert(v1_next == head_v);

  free_node_in_array(node_array);

  scllist->super.destroy_ll(scllist);
  return TEST_PASSED;
}

TestResult test_create_single_circular_linkedlist() {
  SCLinkedlist *scllist = init_single_circular_linkedlist();
  NODE *test_head = scllist->super.head;
  NODE *test_tail = scllist->super.tail;
  int test_headv = *(int *)test_head->node_data;
  assert(test_headv == v0);

  int v23_next = *(int *)((NODE *)scllist->super.head + 8)->next->node_data;
  assert(v23_next == v33);

  int v91_next = *(int *)((NODE *)scllist->super.head + 11)->next->node_data;
  assert(v91_next == v321);

  int test_tailv = *(int *)test_tail->node_data;
  assert(test_tailv == v1201);

  assert(((NODE *)scllist->super.tail)->next == scllist->super.head);
  int tailv_next = *(int *)((NODE *)scllist->super.tail)->next->node_data;
  assert(tailv_next == test_headv);
  free_node_in_scll((Linkedlist *)scllist);
  scllist->super.destroy_ll(scllist);
  return TEST_PASSED;
}
