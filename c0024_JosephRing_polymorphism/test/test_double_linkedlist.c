#include "test_double_linkedlist.h"
#include "data_process.h"
#include "test_and_validation.h"
#include <assert.h>
#include <stdlib.h>

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

DoubleLinkedList *init_double_linkedlist() {
  DoubleLinkedList *dllist = create_double_linkedlist();
  double_linkedlist_constructor(dllist, NULL, NULL, 0, 'K', &insert_node_dll,
                                &delete_node_dll, &destroy_double_linkedlist,
                                "DoubleLinkedList", &set_name_dll,
                                &get_name_dll, &dll_toString);
  NODE_DLL *node_array = NULL;
  NODE_DLL *node_arr[ARRAY_SIZE] = {NULL};
  node_array = convert_node_dll_array(node_arr);
  for (int i = 0; i < ARRAY_SIZE; i++) {
    dllist->super->insert_node(dllist, (node_array + i));
  }

  return dllist;
}

TestResult test_insert_node_to_empty_dll() {
  DoubleLinkedList *dllist = create_double_linkedlist();
  double_linkedlist_constructor(dllist, NULL, NULL, 0, 'K', &insert_node_dll,
                                &delete_node_dll, &destroy_double_linkedlist,
                                "DoubleLinkedList", &set_name_dll,
                                &get_name_dll, &dll_toString);
  /*
  double_linkedlist_constructor(dllist, NULL, NULL, 0, 'K', &insert_node_dll,
                                &delete_node_dll, &destroy_double_linkedlist);
*/
  NODE_DLL *node_array = NULL;
  NODE_DLL *node_arr[ARRAY_SIZE] = {NULL};
  node_array = convert_node_dll_array(node_arr);
  dllist->super->insert_node(dllist, (node_array + 6));
  int headv = *(int *)((NODE_DLL *)dllist->super->head)->node_data;
  assert(headv == v14);
  free_node_dll_in_array(node_array);
  dllist->super->destroy_ll(dllist);
  return TEST_PASSED;
}

TestResult test_insert_node_to_dll() {
  DoubleLinkedList *dllist = create_double_linkedlist();
  double_linkedlist_constructor(dllist, NULL, NULL, 0, 'K', &insert_node_dll,
                                &delete_node_dll, &destroy_double_linkedlist,
                                "DoubleLinkedList", &set_name_dll,
                                &get_name_dll, &dll_toString);
  /*
  double_linkedlist_constructor(dllist, NULL, NULL, 0, 'K', &insert_node_dll,
                                &delete_node_dll, &destroy_double_linkedlist);
*/
  NODE_DLL *node_array = NULL;
  NODE_DLL *node_arr[ARRAY_SIZE] = {NULL};
  node_array = convert_node_dll_array(node_arr);

  dllist->super->insert_node(dllist, (node_array + 8));
  assert(dllist->super->head == (node_array + 8));
  int headv = *(int *)((NODE_DLL *)dllist->super->head)->node_data;
  assert(headv == v23);

  dllist->super->insert_node(dllist, node_array);
  assert(dllist->super->tail == node_array);
  int tailv = *(int *)((NODE_DLL *)dllist->super->tail)->node_data;
  assert(tailv == v0);

  dllist->super->insert_node(dllist, (node_array + 4));
  assert(dllist->super->tail == (node_array + 4));
  tailv = *(int *)((NODE_DLL *)dllist->super->tail)->node_data;
  assert(tailv == v10);

  dllist->super->insert_node(dllist, (node_array + 9));
  assert(dllist->super->tail == (node_array + 9));
  tailv = *(int *)((NODE_DLL *)dllist->super->tail)->node_data;
  assert(tailv == v33);

  free_node_dll_in_array(node_array);
  dllist->super->destroy_ll(dllist);
  return TEST_PASSED;
}

TestResult test_delete_node_dll() {
  DoubleLinkedList *dllist = create_double_linkedlist();
  double_linkedlist_constructor(dllist, NULL, NULL, 0, 'K', &insert_node_dll,
                                &delete_node_dll, &destroy_double_linkedlist,
                                "DoubleLinkedList", &set_name_dll,
                                &get_name_dll, &dll_toString);
  /*
  double_linkedlist_constructor(dllist, NULL, NULL, 0, 'K', &insert_node_dll,
                                &delete_node_dll, &destroy_double_linkedlist);
*/
  dllist = init_double_linkedlist();
  NODE_DLL *test_tail = dllist->super->tail;
  int headv = *(int *)((NODE_DLL *)dllist->super->head)->node_data;
  assert(headv == v0);

  dllist->super->delete_node(dllist,
                             ((NODE_DLL *)dllist->super->head)->next + 7);
  int dll_v21n =
      *(int *)((((NODE_DLL *)dllist->super->head)->next) + 6)->node_data;
  assert(dll_v21n == v33);

  dllist->super->delete_node(dllist, dllist->super->head);
  assert(*(int *)(((NODE_DLL *)dllist->super->head)->next)->node_data == v1);

  dllist->super->delete_node(dllist, dllist->super->tail);
  assert((((NODE_DLL *)dllist->super->head) + 13)->next == NULL);

  free_node_in_dll((Linkedlist *)dllist);
  dllist->super->destroy_ll(dllist);
  return TEST_PASSED;
}
