#ifndef LINKLIST_VAR
#define LINKLIST_VAR

#include "linkedlist.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 10

typedef struct node NODE;
typedef struct single_linkedlist SingleLinkedlist;

struct node {
  void *node_data;
  NODE *next;
};

SingleLinkedlist *create_single_linkedlist();
void single_linkedlist_constructor(SingleLinkedlist *, NODE *, NODE *, int,
                                   char *, insert_node_to_ll,
                                   delete_node_from_ll, destroy_linkedlist_func,
                                   char *, set_name_poly, get_name_poly,
                                   polymorphism_toString);
bool is_node_in_single_linkedlist(SingleLinkedlist *, NODE *);
bool is_empty(SingleLinkedlist *);
int size_of_linklist(SingleLinkedlist *);
SingleLinkedlist *insert_node_as_head(SingleLinkedlist *, NODE *);
SingleLinkedlist *insert_node_after_head(SingleLinkedlist *, NODE *);
SingleLinkedlist *insert_node_in_middle(SingleLinkedlist *, NODE *, int);
SingleLinkedlist *insert_node_as_tail(SingleLinkedlist *, NODE *);
SingleLinkedlist *insert_node_sll(SingleLinkedlist *, NODE *);
NODE *get_node_position(SingleLinkedlist *, NODE *);
NODE *get_previous_node(SingleLinkedlist *, NODE *);
NODE *get_tail_sll(SingleLinkedlist *);
SingleLinkedlist *delete_node_sll(SingleLinkedlist *, NODE *);
void destroy_single_linkedlist(SingleLinkedlist *);
void set_name_sll(SingleLinkedlist *, char *);
char *get_name_sll(SingleLinkedlist *);
void sll_toString(SingleLinkedlist *);

struct single_linkedlist {
  Linkedlist super;

  char *symbol;
};

#endif // LINKLIST_VAR
