#ifndef LINKEDLIST_VAR
#define LINKEDLIST_VAR

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linkedlist Linkedlist;

typedef void *(*insert_node_to_ll)(void *, void *);
typedef void *(*delete_node_from_ll)(void *, void *);
typedef void (*destroy_linkedlist_func)(void *);
typedef void (*polymorphism_toString)(Linkedlist *);
typedef void (*set_name_poly)(Linkedlist *, char *);
typedef char *(*get_name_poly)();

Linkedlist *create_linkedlist();
void linkedlist_constructor(Linkedlist *, void *, void *, int,
                            insert_node_to_ll, delete_node_from_ll,
                            destroy_linkedlist_func, char *, set_name_poly,
                            get_name_poly, polymorphism_toString);

void destroy_linkedlist(Linkedlist *llist);
void set_name_ll(Linkedlist *, char *);

char *get_name_ll(Linkedlist *);

void _toString_ll(void *);

void ll_toString(Linkedlist *);

struct linkedlist {
  char *name;
  void *head;
  void *tail;
  int size_ll;

  insert_node_to_ll insert_node;
  delete_node_from_ll delete_node;
  destroy_linkedlist_func destroy_ll;
  polymorphism_toString toString;
  set_name_poly set_name;
  get_name_poly get_name;
};

#endif
