#ifndef QUEUE_LIB
#define QUEUE_LIB

#include "../include/log.h"
#include <stdbool.h>
#include <stdio.h>

#define MAX_SIZE 30
#define EXIT_FAILUE -1

typedef struct QueueNode {
  void *qn_data;
  struct QueueNode *next;
} QueueNode;

typedef struct Queue {
  QueueNode *front;
  QueueNode *rear;
} Queue;

Queue *create_queue();
void free_queue(Queue *);
bool is_queue_empty(Queue *);
int size_of_queue(Queue *, int *);
QueueNode *enqueue(Queue *, void *);
bool dequeue(Queue *, QueueNode **);

#endif
