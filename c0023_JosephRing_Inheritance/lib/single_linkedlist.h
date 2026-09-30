#ifndef LINKLIST_VAR
#define LINKLIST_VAR

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 10

typedef struct node NODE;
typedef struct single_linkedlist SingleLinkedlist;

// C语言多态就是靠函数指针指向不同的行为函数，实现多态
// 定义链表操作的行为函数原型，将这些原型放入链表结构体，创建链表的时候为这些函数赋值，继承自父类的子链表会赋予不同的行为函数
// 运行的时候不同的链表运行各自的行为函数，实现多态的效果。
typedef void *(*insert_node_to_sll)(void *, void *);
typedef void *(*delete_node_from_sll)(void *, void *);
typedef void (*destroy_linkedlist)(void *);
typedef void *(*insert_node_at_the_end)(void *, void *);

struct node {
  void *node_data;
  NODE *next;
};

SingleLinkedlist *create_single_linkedlist();
void single_linkedlist_constructor(SingleLinkedlist *, NODE *, NODE *, int);
bool is_node_in_single_linkedlist(SingleLinkedlist *, NODE *);
bool is_empty(SingleLinkedlist *);
int size_of_linklist(SingleLinkedlist *);
SingleLinkedlist *insert_node_as_head(SingleLinkedlist *, NODE *);
SingleLinkedlist *insert_node_after_head(SingleLinkedlist *, NODE *);
SingleLinkedlist *insert_node_in_middle(SingleLinkedlist *, NODE *, int);
SingleLinkedlist *insert_node_as_tail(SingleLinkedlist *, NODE *);
SingleLinkedlist *insert_node(SingleLinkedlist *, NODE *);
NODE *get_node_position(SingleLinkedlist *, NODE *);
NODE *get_previous_node(SingleLinkedlist *, NODE *);
NODE *get_tail(SingleLinkedlist *);
SingleLinkedlist *delete_node(SingleLinkedlist *, NODE *);
void destroy_single_linkedlist(SingleLinkedlist *);

struct single_linkedlist {
  NODE *head;
  NODE *tail;
  int sll_size;

  insert_node_to_sll insert_node_sll;
  insert_node_at_the_end insert_at_the_end;
  delete_node_from_sll delete_node_sll;
  destroy_linkedlist destroy_sll;
};

#endif // LINKLIST_VAR
