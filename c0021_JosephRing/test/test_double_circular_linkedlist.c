#include "test_double_circular_linkedlist.h"
#include <assert.h>
#include <stdlib.h>

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

void free_node_dcll() {
  dc_head = NULL;
  dc_tail = NULL;
}

void create_double_circular_linkedlist() {
  init_node_value_dll();
  insert_node_dcll(node_dll_0);
  insert_node_dcll(node_dll_1);
  insert_node_dcll(node_dll_3);
  insert_node_dcll(node_dll_8);
  insert_node_dcll(node_dll_10);
  insert_node_dcll(node_dll_11);
  insert_node_dcll(node_dll_14);
  insert_node_dcll(node_dll_21);
  insert_node_dcll(node_dll_23);
  insert_node_dcll(node_dll_33);
  insert_node_dcll(node_dll_45);
  insert_node_dcll(node_dll_91);
  insert_node_dcll(node_dll_321);
  insert_node_dcll(node_dll_1024);
  insert_node_dcll(node_dll_1201);
}

TestResult test_size_of_dcll() {
  create_double_circular_linkedlist();
  int dcll_size = size_of_dcll();
  assert(dcll_size == 15);
  free_node_dll();
  free_node_dcll();
  return TEST_PASSED;
}

TestResult test_insert_node_dcll() {
  init_node_value_dll();
  insert_node_dcll(node_dll_10);
  assert(dc_head == node_dll_10);
  int headv = *(int *)dc_head->node_data;
  assert(headv == dll_v10);
  free_node_dll();
  free_node_dcll();
  return TEST_PASSED;
}

TestResult test_delete_middle_node_dcll() {
  init_node_value_dll();
  create_double_circular_linkedlist();
  NODE_DLL *test_head = dc_head;
  assert(test_head == node_dll_0);

  delete_node_dcll(node_dll_11);
  assert(node_dll_10->next == node_dll_14);
  int dvn_10 = *(int *)node_dll_10->next->node_data;
  assert(dvn_10 == dll_v14);

  delete_node_dcll(node_dll_1024);
  assert(node_dll_321->next == node_dll_1201);

  delete_node_dcll(node_dll_1201);
  assert(node_dll_321->next == node_dll_0);

  delete_node_dcll(node_dll_0);
  assert(node_dll_321->next == node_dll_1);

  free_node_dll();
  free_node_dcll();
  return TEST_PASSED;
}
