#ifndef QUEUE_VAR
#define QUEUE_VAR

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define LENGTH 10

typedef struct node NODE;

struct node{
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
