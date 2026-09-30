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

extern NODE *head;
extern NODE *tail;

NODE *init_single_linkedlist();
bool is_node_in_list(NODE *);
int size_of_linklis();
NODE *insert_node_as_head(NODE *);
NODE *insert_node_after_head(NODE *);
NODE *insert_node_in_middle(NODE *, int);
NODE *insert_node_as_tail(NODE *);
NODE *insert_node(NODE *);
NODE *get_node_position(NODE *);
NODE *get_previous_node(NODE *);
NODE *get_tail();
NODE *delete_node(NODE *);

#endif // LINKLIST_VAR
