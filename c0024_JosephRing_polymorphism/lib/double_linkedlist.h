#ifndef D_LINKEDLIST_VAR
#define D_LINKEDLIST_VAR

#include "linkedlist.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_dll NODE_DLL;
typedef struct double_linkedlist DoubleLinkedList;

/*
typedefpedef void *(*insert_node_to_dll)(void *, void *);
typedef void *(*delete_node_from_dll)(void *, void *);
typedef void (*destroy_double_linkedlist_func)(void *);
*/
struct node_dll {
  void *node_data;
  NODE_DLL *prev, *next;
};

DoubleLinkedList *create_double_linkedlist();
void double_linkedlist_constructor(DoubleLinkedList *, NODE_DLL *, NODE_DLL *,
                                   int, char, insert_node_to_ll,
                                   delete_node_from_ll, destroy_linkedlist_func,
                                   char *, set_name_poly, get_name_poly,
                                   polymorphism_toString);
bool is_empty_dll(DoubleLinkedList *);
bool is_node_in_list(DoubleLinkedList *, NODE_DLL *);
int size_of_dll(DoubleLinkedList *);
DoubleLinkedList *insert_node_as_head_dll(DoubleLinkedList *, NODE_DLL *);
DoubleLinkedList *insert_node_after_head_dll(DoubleLinkedList *, NODE_DLL *);
DoubleLinkedList *insert_node_in_middle_dll(DoubleLinkedList *, NODE_DLL *,
                                            int);
DoubleLinkedList *insert_node_as_tail_dll(DoubleLinkedList *, NODE_DLL *);
DoubleLinkedList *insert_node_dll(DoubleLinkedList *, NODE_DLL *);
DoubleLinkedList *get_node_position_dll(DoubleLinkedList *, NODE_DLL *);
DoubleLinkedList *delete_node_dll(DoubleLinkedList *, NODE_DLL *);
void destroy_double_linkedlist(DoubleLinkedList *);
void set_name_dll(DoubleLinkedList *, char *);

char *get_name_dll(DoubleLinkedList *);

void _toString_dll(void *);

void dll_toString(DoubleLinkedList *);

// 继承的第二种写法，父类不作为子类结构体的第一个成员，在应用中无法进行向上转型，将子类转换成父类
// 只能指向父类指针，通过父类指针调用父类成员，达到子类调用父类方法的目的
struct double_linkedlist {
  char charactor;
  Linkedlist *super;
};

#endif // DC_LINKEDLIST_VAR
