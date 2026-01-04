#ifndef QUEUE_LIB
#define QUEUE_LIB

#include "log.h"
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
// void destroy_queue(Queue *);
bool is_empty(Queue *);
QueueNode *enqueue(Queue *, void *);
QueueNode *dequeue(Queue *);

#endif
