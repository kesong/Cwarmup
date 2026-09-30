#ifndef LINKLIST_VAR
#define LINKLIST_VAR

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 10

typedef struct node NODE;

struct node {
  void *node_data;
  NODE *next;
};

extern NODE *sc_head;
extern NODE *sc_tail;

NODE *init_single_circular_linkedlist();
bool is_empty_scll();
bool is_node_in_single_circular_linkedlist(NODE *);
int size_of_single_circular_linkedlist();
NODE *insert_node_as_head_in_single_circular_linkedlist(NODE *);
NODE *insert_node_after_head_in_single_circular_linkedlist(NODE *);
NODE *insert_node_in_middle_single_circular_linkedlist(NODE *, int);
NODE *insert_node_as_tail_in_single_circular_linkedlist(NODE *);
NODE *insert_node_in_single_circular_linkedlist(NODE *);
NODE *get_node_position_in_single_circular_linkedlist(NODE *);
NODE *get_previous_node_in_single_circular_linkedlist(NODE *, NODE *);
NODE *delete_node_in_single_circular_linkedlist(NODE *);
int clear_single_circular_linkedlist();

#endif // LINKLIST_VAR
