#ifndef STACK_VAR
#define STACK_VAR

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define LENGTH 10

typedef struct player PLAYER;
typedef struct team TEAM;
typedef struct node NODE;

struct player{
	char* pname;
  	int pnumber;
	int salary;
	struct team* tm;
};
 
struct team{
	char* tname;
	char* city;
};

struct node{
	PLAYER* player_node;
	NODE* next;
};

extern NODE* top;
extern NODE* bottom;

void init_stack();
bool is_empty();
int size_of_linklist();
void push(NODE*);
void pop();
void stack_destroy();
void print_stack();

#endif //STACK_VAR
