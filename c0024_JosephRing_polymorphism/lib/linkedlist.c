#include "linkedlist.h"
#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Linkedlist *create_linkedlist() {
  Linkedlist *llist = (Linkedlist *)malloc(sizeof(Linkedlist));
  memset(llist, 0, sizeof(Linkedlist));
  return llist;
}

void linkedlist_constructor(Linkedlist *llist, void *head, void *tail,
                            int size_ll, insert_node_to_ll insert_func,
                            delete_node_from_ll delete_func,
                            destroy_linkedlist_func destroy_func, char *name,
                            set_name_poly set_name_func,
                            get_name_poly get_name_func,
                            polymorphism_toString toString) {
  llist->head = head;
  llist->tail = tail;
  llist->size_ll = size_ll;
  llist->insert_node = insert_func;
  llist->delete_node = delete_func;
  llist->destroy_ll = destroy_func;
  llist->name = name;
  llist->set_name = set_name_func;
  llist->get_name = get_name_func;
  llist->toString = toString;
}

int size_of_linklist(Linkedlist *llist) { return llist->size_ll; }
bool is_empty(Linkedlist *llist) { return llist->head == NULL ? true : false; }

void destroy_linkedlist(Linkedlist *llist) {
  free(llist);
  llist = NULL;
}

void set_name_ll(Linkedlist *llist, char *name) { llist->name = name; }

char *get_name_ll(Linkedlist *llist) { return llist->name; }

void _toString_ll(void *receive_llist) {
  Linkedlist *llist = (Linkedlist *)receive_llist;
  printf("This is %s. \n", llist->name);
}

void ll_toString(Linkedlist *llist) { _toString_ll(llist); }
