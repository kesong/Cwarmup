#ifndef D_LINKEDLIST_VAR
#define D_LINKEDLIST_VAR

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_dll NODE_DLL;

struct node_dll {
  void *node_data;
  NODE_DLL *prev, *next;
};

NODE_DLL *init_double_linkedlist();
bool is_empty_dll();
bool is_node_in_list(NODE_DLL *);
int size_of_dll();
NODE_DLL *insert_node_as_head_dll(NODE_DLL *);
NODE_DLL *insert_node_after_head_dll(NODE_DLL *);
NODE_DLL *insert_node_in_middle_dll(NODE_DLL *, int);
NODE_DLL *insert_node_as_tail_dll(NODE_DLL *);
NODE_DLL *insert_node_dll(NODE_DLL *);
NODE_DLL *get_node_position_dll(NODE_DLL *);
NODE_DLL *delete_node_dll(NODE_DLL *);

#endif // DC_LINKEDLIST_VAR
