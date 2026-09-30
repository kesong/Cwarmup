#include "test_single_linkedlist.h"
#include "data_process.h"
#include "test_single_circular_linkedlist.h"
#include <assert.h>
#include <stdbool.h>
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

SingleLinkedlist *init_single_linkedlist() {
  SingleLinkedlist *sllist = create_single_linkedlist();
  single_linkedlist_constructor(sllist, NULL, NULL, 0, "Narcissus",
                                &insert_node_sll, &delete_node_sll,
                                &destroy_single_linkedlist, "SingleLinkedlist",
                                &set_name_sll, &get_name_sll, sll_toString);
  NODE *node_array = NULL;
  NODE *node_arr[ARRAY_SIZE] = {NULL};
  node_array = convert_node_array(node_arr);
  for (int i = 0; i < ARRAY_SIZE; i++) {
    ((Linkedlist *)sllist)->insert_node(sllist, (node_array + i));
  }
  return sllist;
}

TestResult test_insert_node_to_empty_sll() {
  SingleLinkedlist *sllist = create_single_linkedlist();
  single_linkedlist_constructor(sllist, NULL, NULL, 0, "Narcissus",
                                &insert_node_sll, &delete_node_sll,
                                &destroy_single_linkedlist, "SingleLinkedlist",
                                &set_name_sll, &get_name_sll, sll_toString);
  Linkedlist *llist = (Linkedlist *)sllist;
  NODE *node_array = NULL;
  NODE *node_arr[ARRAY_SIZE] = {NULL};
  node_array = convert_node_array(node_arr);
  llist->insert_node(sllist, (node_array + 6));
  int headv = *(int *)((NODE *)llist->head)->node_data;
  assert(headv == v14);
  int tailv = *(int *)((NODE *)llist->tail)->node_data;
  assert(tailv == v14);
  free_node_in_array(node_array);
  llist->destroy_ll(sllist);
  return TEST_PASSED;
}

TestResult test_insert_node_in_sll() {
  SingleLinkedlist *sllist = init_single_linkedlist();
  Linkedlist *llist = (Linkedlist *)sllist;
  NODE *test_head = llist->head;
  int thv = *(int *)test_head->node_data;
  assert(v0 == thv);
  free_node_in_sll(llist);
  llist->destroy_ll(sllist);
  return TEST_PASSED;
}

// 有从链表中删除节点，被删除节点的空间也要释放，所以这里要释放的是此前保存节点的数组，不能遍历链表的方式释放，因为被删除的节点是无法遍历到的。
TestResult test_get_tail() {
  SingleLinkedlist *sllist = init_single_linkedlist();
  Linkedlist *llist = (Linkedlist *)sllist;
  NODE *test_head = llist->head;
  NODE *test_tail = NULL;
  NODE *head_next = ((NODE *)(llist->head))->next;
  // 下面这个注释了的head_next值与上面相同.
  //  NODE *head_next = ((NODE*)(sllist->super->head))->next;
  llist->delete_node(sllist, (((NODE *)llist->head)->next + 13));
  test_tail = get_tail_sll(sllist);
  int tailv = *(int *)((NODE *)llist->tail)->node_data;
  assert(tailv == v1024);

  // 链表中有节点被删除，链表的头指针就是node_array的首地址，一次性释放节点数组
  // 如果头节点被删除，在执行删除前要将头指针的地址保存，否则就会出现没有释放的空间，最终导致内存泄漏
  free_node_in_array(sllist->super.head);

  llist->destroy_ll(sllist);
  return TEST_PASSED;
}

TestResult test_delete_node_in_scll() {
  SingleLinkedlist *sllist = init_single_linkedlist();
  Linkedlist *llist = (Linkedlist *)sllist;
  NODE *test_head = (NODE *)llist->head;
  llist->delete_node(sllist, (((NODE *)llist->head)->next + 4));
  int v10n = *(int *)(((NODE *)(llist->head))->next + 5)->node_data;
  assert(v10n == v14);
  free_node_in_array(sllist->super.head);
  // free_node_in_sll(llist);
  llist->destroy_ll(sllist);
  return TEST_PASSED;
}
