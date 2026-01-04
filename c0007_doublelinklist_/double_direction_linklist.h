#ifndef DD_LINKLIST_VAR
#define DD_LINKLIST_VAR

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

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
	NODE *prev, *next;
};

extern NODE* head;
extern NODE* tail;

void init_linklist();
bool is_node_in_list(NODE*);
int size_of_linklis();
void insert_node_as_head(NODE*);
void insert_node_after_head(NODE*);
void insert_node_in_middle(NODE*, int);
void insert_node_as_tail(NODE*);
NODE* get_node_position(NODE*);
NODE* get_previous_node(NODE*);
NODE* get_tail();
void delete_node(NODE*);
bool search_node(NODE*);
void print_linklist(NODE*);

#endif //DD_LINKLIST_VAR
