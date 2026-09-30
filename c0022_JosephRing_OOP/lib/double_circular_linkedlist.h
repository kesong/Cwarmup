#ifndef DC_LINKEDLIST_VAR
#define DC_LINKEDLIST_VAR

#include "double_linkedlist.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct double_circular_linkedlist DCLinkedList;

DCLinkedList *init_double_circular_linkedlist(DCLinkedList *);
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

struct double_circular_linkedlist {
  NODE_DLL *head_node;
  NODE_DLL *tail_node;
  int dc_size;

  DCLinkedList *(*init_double_circular_linkedlist)(DCLinkedList *);
  bool (*is_empty_dcll)(DCLinkedList *);
  bool (*is_node_in_dcll)(DCLinkedList *, NODE_DLL *);
  int (*size_of_dcll)(DCLinkedList *);
  DCLinkedList *(*insert_node_as_head_dcll)(DCLinkedList *, NODE_DLL *);
  DCLinkedList *(*insert_node_after_head_dcll)(DCLinkedList *, NODE_DLL *);
  DCLinkedList *(*insert_node_in_middle_dcll)(DCLinkedList *, NODE_DLL *, int);
  DCLinkedList *(*insert_node_as_tail_dcll)(DCLinkedList *, NODE_DLL *);
  DCLinkedList *(*insert_node_dcll)(DCLinkedList *, NODE_DLL *);
  DCLinkedList *(*get_node_position_dcll)(DCLinkedList *, NODE_DLL *);
  DCLinkedList *(*delete_node_dcll)(DCLinkedList *, NODE_DLL *);
};

#endif // DC_LINKEDLIST_VAR
