#include "test_double_circular_linkedlist.h"
#include "data_process.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

extern int v0;
extern int v1;
extern int v3;
extern int v8;
extern int v10;
extern int v11;
extern int v14;
extern int v21;
extern int v23;
extern int v33;
extern int v45;
extern int v91;
extern int v321;
extern int v1024;
extern int v1201;

DCLinkedList *init_double_circular_linkedlist() {
  DCLinkedList *dcllist = create_double_circular_linkedlist();
  double_circular_linkedlist_constructor(
      dcllist, "dcll polymorphism", "0123", NULL, NULL, 0, &insert_node_dcll,
      &delete_node_dcll, &destroy_double_circular_linkedlist, "DCLinkedList",
      &set_name_dcll, &get_name_dcll, &dcll_toString);
  /*
  double_circular_linkedlist_constructor(
      dcllist, "dcll polymorphism", "0123", NULL, NULL, 0, &insert_node_dcll,
      &delete_node_dcll, &destroy_double_circular_linkedlist); */
  NODE_DLL *node_array = NULL;
  NODE_DLL *node_arr[ARRAY_SIZE] = {NULL};
  node_array = convert_node_dll_array(node_arr);
  for (int i = 0; i < ARRAY_SIZE; i++) {
    dcllist->super->insert_node(dcllist, (node_array + i));
  }
  return dcllist;
}

TestResult test_size_of_dcll() {
  DCLinkedList *dcllist = init_double_circular_linkedlist();
  int dcll_size = size_of_dcll(dcllist);
  assert(dcll_size == 15);
  free_node_in_dcll(dcllist);
  dcllist->super->destroy_ll(dcllist);
  return TEST_PASSED;
}

TestResult test_insert_node_dcll() {
  DCLinkedList *dcllist = create_double_circular_linkedlist();
  double_circular_linkedlist_constructor(
      dcllist, "dcll polymorphism", "0123", NULL, NULL, 0, &insert_node_dcll,
      &delete_node_dcll, &destroy_double_circular_linkedlist, "DCLinkedList",
      &set_name_dcll, &get_name_dcll, &dcll_toString);
  /*
  double_circular_linkedlist_constructor(
      dcllist, "dcll polymorphism", "0123", NULL, NULL, 0, &insert_node_dcll,
      &delete_node_dcll, &destroy_double_circular_linkedlist); */
  NODE_DLL *node_array = NULL;
  NODE_DLL *node_arr[ARRAY_SIZE] = {NULL};
  node_array = convert_node_dll_array(node_arr);

  dcllist->super->insert_node(dcllist, (node_array + 4));
  int headv = *(int *)((NODE_DLL *)dcllist->super->head)->node_data;
  assert(headv == v10);
  free_node_dll_in_array(node_array);
  dcllist->super->destroy_ll(dcllist);
  return TEST_PASSED;
}

TestResult test_delete_middle_node_dcll() {
  DCLinkedList *dcllist = init_double_circular_linkedlist();
  NODE_DLL *test_head = dcllist->super->head;
  int thv = *(int *)((NODE_DLL *)dcllist->super->head)->node_data;
  assert(thv == v0);

  dcllist->super->delete_node(dcllist, ((NODE_DLL *)dcllist->super->head + 4));
  int dvn_10 =
      *(int *)(((NODE_DLL *)dcllist->super->head)->next + 5)->node_data;
  assert(dvn_10 == v14);

  dcllist->super->delete_node(dcllist,
                              ((NODE_DLL *)dcllist->super->head)->next + 12);
  int v321_next =
      *(int *)(((NODE_DLL *)dcllist->super->head)->next + 13)->node_data;
  assert(v321_next == v1201);

  // 链表中有节点被删除，链表的头指针就是node_array的首地址，一次性释放节点数组
  // 如果头节点被删除，在执行删除前要将头指针的地址保存，否则就会出现没有释放的空间，最终导致内存泄漏
  free_node_dll_in_array(dcllist->super->head);

  dcllist->super->destroy_ll(dcllist);
  return TEST_PASSED;
}
