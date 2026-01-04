#ifndef QUEUE_VAR
#define QUEUE_VAR

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define LENGTH 10

typedef struct node NODE;
typedef enum{PLAYER_NODE, PLAYER_NAME, PLAYER_YEAR} NODE_TYPE;

struct node{
	NODE_TYPE node_t;
	void* ptr_data;
	NODE* next;
};

extern NODE* head;
extern NODE* tail;

void init_queue();
bool is_empty();
int size_of_queue();
void enqueue(NODE*);
void dequeue();
void queue_destroy();

#endif //QUEUE_VAR
