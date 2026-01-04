#ifndef PRINT_ADT
#define PRINT_ADT

#include "../lib/stack.h"
#include "log.h"

// 这里指用到了NODE指针，不需要包含test/test_player.h整个头文件，只做一个声明就行了，避免循环引用（互相引用）导致的编译错误。
typedef struct node NODE;
typedef struct player PLAYER;
typedef struct team TEAM;

void print_player_node(NODE *);

void print_stack(Stack *);

#endif
