#ifndef DC_LINKEDLIST_VAR
#define DC_LINKEDLIST_VAR

#include "double_linkedlist.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
typedef struct node_dll NODE_DLL;

struct node_dll {
  void *node_data;
  NODE_DLL *prev, *next;
};
*/

NODE_DLL *init_double_circular_linkedlist();
bool is_empty_dcll();
bool is_node_in_dcll(NODE_DLL *);
int size_of_dcll();
NODE_DLL *insert_node_as_head_dcll(NODE_DLL *);
NODE_DLL *insert_node_after_head_dcll(NODE_DLL *);
NODE_DLL *insert_node_in_middle_dcll(NODE_DLL *, int);
NODE_DLL *insert_node_as_tail_dcll(NODE_DLL *);
NODE_DLL *insert_node_dcll(NODE_DLL *);
NODE_DLL *get_node_position_dcll(NODE_DLL *);
NODE_DLL *delete_node_dcll(NODE_DLL *);

#endif // DC_LINKEDLIST_VAR
