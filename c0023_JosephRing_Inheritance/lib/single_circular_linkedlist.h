#ifndef CIRCULAR_LINKLIST_VAR
#define CIRCULAR_LINKLIST_VAR

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
                                            SingleLinkedlist *);
bool is_node_in_scll(SCLinkedlist *, NODE *);
int size_of_scll(SCLinkedlist *);
SCLinkedlist *insert_node_as_head_in_scll(SCLinkedlist *, NODE *);
SCLinkedlist *insert_node_after_head_in_scll(SCLinkedlist *, NODE *);
SCLinkedlist *insert_node_in_middle_scll(SCLinkedlist *, NODE *, int);
SCLinkedlist *insert_node_as_tail_in_scll(SCLinkedlist *, NODE *);
SCLinkedlist *insert_node_in_scll(SCLinkedlist *, NODE *);
NODE *get_node_position_in_scll(SCLinkedlist *, NODE *);
NODE *get_previous_node_in_scll(SCLinkedlist *, NODE *, NODE *);
SCLinkedlist *delete_node_in_scll(SCLinkedlist *, NODE *);
void destroy_single_circular_linkedlist(SCLinkedlist *);

// 将这里的结构体称之为类
// 实现继承的第一种方法，必须将父类放在子类的第一个元素
// 第二种方法可以将父类放在子类的任意位置，在双向链表中采用第二种方式
struct single_circular_linkedlist {
  SingleLinkedlist *super;
};

#endif // LINKLIST_VAR
