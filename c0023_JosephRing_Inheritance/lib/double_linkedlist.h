#ifndef D_LINKEDLIST_VAR
#define D_LINKEDLIST_VAR

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_dll NODE_DLL;
typedef struct double_linkedlist DoubleLinkedList;

typedef void *(*insert_node_to_dll)(void *, void *);
typedef void *(*delete_node_from_dll)(void *, void *);
typedef void (*destroy_double_linkedlist_func)(void *);

struct node_dll {
  void *node_data;
  NODE_DLL *prev, *next;
};

DoubleLinkedList *new_double_linkedlist();
void double_linkedlist_constructor(DoubleLinkedList *, NODE_DLL *, NODE_DLL *,
                                   int, insert_node_to_dll,
                                   delete_node_from_dll,
                                   destroy_double_linkedlist_func);
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

// C++和java等语言中有class类这种关键字创造不同的对象，C语言中没有这样的关键字。但是C语言实现面向对象可以使用结构体将对象的属性，行为函数（控制函数）等
// 封装起来，行为函数使用函数指针进行封装，实现面向对象的操作。
// 结构体可以视为class类的初级形式
struct double_linkedlist {
  NODE_DLL *head;
  NODE_DLL *tail;
  int dll_size;

  insert_node_to_dll insert_to_dll;
  delete_node_from_dll delete_from_dll;
  destroy_double_linkedlist_func destroy_dll;
};

#endif // DC_LINKEDLIST_VAR
