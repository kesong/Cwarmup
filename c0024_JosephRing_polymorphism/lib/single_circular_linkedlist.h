#ifndef CIRCULAR_LINKLIST_VAR
#define CIRCULAR_LINKLIST_VAR

#include "linkedlist.h"
#include "single_linkedlist.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 10

typedef struct single_circular_linkedlist SCLinkedlist;

SCLinkedlist *create_single_circular_linkedlist();
void single_circular_linkedlist_constructor(SCLinkedlist *, NODE *, NODE *, int,
                                            insert_node_to_ll,
                                            delete_node_from_ll,
                                            destroy_linkedlist_func, char *,
                                            set_name_poly, get_name_poly,
                                            polymorphism_toString);
bool is_node_in_scll(SCLinkedlist *, NODE *);
int size_of_scll(SCLinkedlist *);
SCLinkedlist *insert_node_as_head_in_scll(SCLinkedlist *, NODE *);
SCLinkedlist *insert_node_after_head_in_scll(SCLinkedlist *, NODE *);
SCLinkedlist *insert_node_in_middle_scll(SCLinkedlist *, NODE *, int);
SCLinkedlist *insert_node_as_tail_in_scll(SCLinkedlist *, NODE *);
SCLinkedlist *insert_node_scll(SCLinkedlist *, NODE *);
NODE *get_node_position_scll(SCLinkedlist *, NODE *);
NODE *get_previous_node_scll(SCLinkedlist *, NODE *, NODE *);
SCLinkedlist *delete_node_scll(SCLinkedlist *, NODE *);
void destroy_single_circular_linkedlist(SCLinkedlist *);
void set_name_scll(SCLinkedlist *, char *);
char *get_name_scll(SCLinkedlist *);
void scll_toString(SCLinkedlist *);

// 父类作为子类第一个成员，可以进行子类到父类的向上转型
struct single_circular_linkedlist {
  Linkedlist super;
};

#endif // LINKLIST_VAR
