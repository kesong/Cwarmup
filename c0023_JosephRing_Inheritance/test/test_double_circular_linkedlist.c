#include "test_double_circular_linkedlist.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

extern NODE_DLL *node_dll_0;
extern NODE_DLL *node_dll_1;
extern NODE_DLL *node_dll_3;
extern NODE_DLL *node_dll_8;
extern NODE_DLL *node_dll_10;
extern NODE_DLL *node_dll_11;
extern NODE_DLL *node_dll_14;
extern NODE_DLL *node_dll_21;
extern NODE_DLL *node_dll_23;
extern NODE_DLL *node_dll_33;
extern NODE_DLL *node_dll_45;
extern NODE_DLL *node_dll_91;
extern NODE_DLL *node_dll_321;
extern NODE_DLL *node_dll_1024;
extern NODE_DLL *node_dll_1201;
extern NODE_DLL *dc_head;
extern NODE_DLL *dc_tail;
extern int dll_v0;
extern int dll_v1;
extern int dll_v3;
extern int dll_v8;
extern int dll_v10;
extern int dll_v11;
extern int dll_v14;
extern int dll_v21;
extern int dll_v23;
extern int dll_v33;
extern int dll_v45;

DCLinkedList *init_double_circular_linkedlist() {
  init_node_value_dll();
  DCLinkedList *dcllist = new_double_circular_linkedlist();
  double_circular_linkedlist_constructor(
      dcllist, "dcll polymorphism", "0123", NULL, NULL, 0, &insert_node_dcll,
      &delete_node_dcll, &destroy_double_circular_linkedlist);
  dcllist->super->insert_to_dll(dcllist, node_dll_0);
  dcllist->super->insert_to_dll(dcllist, node_dll_1);
  dcllist->super->insert_to_dll(dcllist, node_dll_3);
  dcllist->super->insert_to_dll(dcllist, node_dll_8);
  dcllist->super->insert_to_dll(dcllist, node_dll_10);
  dcllist->super->insert_to_dll(dcllist, node_dll_11);
  dcllist->super->insert_to_dll(dcllist, node_dll_14);
  dcllist->super->insert_to_dll(dcllist, node_dll_21);
  dcllist->super->insert_to_dll(dcllist, node_dll_23);
  dcllist->super->insert_to_dll(dcllist, node_dll_33);
  dcllist->super->insert_to_dll(dcllist, node_dll_45);
  dcllist->super->insert_to_dll(dcllist, node_dll_91);
  dcllist->super->insert_to_dll(dcllist, node_dll_321);
  dcllist->super->insert_to_dll(dcllist, node_dll_1024);
  dcllist->super->insert_to_dll(dcllist, node_dll_1201);
  return dcllist;
}

TestResult test_size_of_dcll() {
  DCLinkedList *dcllist = init_double_circular_linkedlist();
  int dcll_size = size_of_dcll(dcllist);
  assert(dcll_size == 15);
  free_node_dll();
  dcllist->super->destroy_dll(dcllist);
  return TEST_PASSED;
}

TestResult test_insert_node_dcll() {
  init_node_value_dll();
  DCLinkedList *dcllist = new_double_circular_linkedlist();
  double_circular_linkedlist_constructor(
      dcllist, "dcll polymorphism", "0123", NULL, NULL, 0, &insert_node_dcll,
      &delete_node_dcll, &destroy_double_circular_linkedlist);

  dcllist->super->insert_to_dll(dcllist, node_dll_10);
  assert(dcllist->super->head == node_dll_10);
  int headv = *(int *)dcllist->super->head->node_data;
  assert(headv == dll_v10);
  free_node_dll();
  dcllist->super->destroy_dll(dcllist);
  return TEST_PASSED;
}

TestResult test_delete_middle_node_dcll() {
  init_node_value_dll();
  DCLinkedList *dcllist = init_double_circular_linkedlist();
  NODE_DLL *test_head = dcllist->super->head;
  assert(test_head == node_dll_0);

  dcllist->super->delete_from_dll(dcllist, node_dll_11);
  assert(node_dll_10->next == node_dll_14);
  int dvn_10 = *(int *)node_dll_10->next->node_data;
  assert(dvn_10 == dll_v14);

  dcllist->super->delete_from_dll(dcllist, node_dll_1024);
  assert(node_dll_321->next == node_dll_1201);

  dcllist->super->delete_from_dll(dcllist, node_dll_1201);
  assert(node_dll_321->next == node_dll_0);

  dcllist->super->delete_from_dll(dcllist, node_dll_0);
  assert(node_dll_321->next == node_dll_1);

  free_node_dll();
  dcllist->super->destroy_dll(dcllist);
  return TEST_PASSED;
}
