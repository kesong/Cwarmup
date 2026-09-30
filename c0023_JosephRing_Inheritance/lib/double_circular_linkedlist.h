#ifndef DC_LINKEDLIST_VAR
#define DC_LINKEDLIST_VAR

#include "double_linkedlist.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct double_circular_linkedlist DCLinkedList;

DCLinkedList *new_double_circular_linkedlist();
void double_circular_linkedlist_constructor(
    DCLinkedList *, char *, char *, NODE_DLL *, NODE_DLL *, int,
    insert_node_to_dll insert_func, delete_node_from_dll delete_func,
    destroy_double_linkedlist_func destroy_func);
bool is_empty_dcll(DCLinkedList *);
bool is_node_in_dcll(DCLinkedList *, NODE_DLL *);
int size_of_dcll(DCLinkedList *);
DCLinkedList *insert_node_as_head_dcll(DCLinkedList *, NODE_DLL *);
DCLinkedList *insert_node_after_head_dcll(DCLinkedList *, NODE_DLL *);
DCLinkedList *insert_node_in_middle_dcll(DCLinkedList *, NODE_DLL *, int);
DCLinkedList *insert_node_as_tail_dcll(DCLinkedList *, NODE_DLL *);
DCLinkedList *insert_node_dcll(DCLinkedList *, NODE_DLL *);
DCLinkedList *get_node_position_dcll(DCLinkedList *, NODE_DLL *);
DCLinkedList *delete_node_dcll(DCLinkedList *, NODE_DLL *);
void destroy_double_circular_linkedlist(DCLinkedList *);

// 为了体验第二种继承的方式，增加两个无用的属性，仅作演示和理论理解之用，无实际用途
struct double_circular_linkedlist {
  char *description;
  char *serial_no;
  DoubleLinkedList *super;
};

#endif // DC_LINKEDLIST_VAR
