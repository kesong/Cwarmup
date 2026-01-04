#include "queue.h"

// 初始化队列，用memset将成员全部初始化为0，指针类型的成员初始化为NULL；
Queue *create_queue() {
  Queue *cr_queue = (Queue *)malloc(sizeof(Queue));
  if (cr_queue == NULL) {
    log_e("error, create queue fail, malloc ram space for queue failed.");
    exit(EXIT_FAILUE);
  }
  memset(cr_queue, 0, sizeof(Queue));
  return cr_queue;
}

/*
void destory_queue(Queue *queue) {
  if (is_empty(queue)) {
    log_i("empty queue, nothing to do.");
  }
  QueueNode remove_node = queue->front;
  while (remove_node != queue->rear) {
    remove_node = queue->front;
    queue->front = remove_node->next;
    free(remove_node);
  }
  if (queue->rear != NULL) {
    free(queue->rear);
  }
} */

bool is_empty(Queue *queue) { return queue->front == NULL; }

QueueNode *enqueue(Queue *queue, void *value) {
  QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
  if (newNode == NULL) {
    log_e("error, malloc for new Node failed.");
    exit(EXIT_FAILURE);
  }
  newNode->qn_data = value;
  if (queue->rear == NULL) {
    queue->front = queue->rear = newNode;
  } else {
    queue->rear->next = newNode;
    queue->rear = queue->rear->next;
    queue->rear->next = NULL;
  }
  return queue->rear;
}

QueueNode *dequeue(Queue *queue) {
  if (is_empty(queue)) {
    log_e("error, queue is empty.");
    return NULL;
  }
  QueueNode *outNode = queue->front;
  queue->front = queue->front->next;
  if (queue->front == NULL) {
    queue->rear = NULL;
  }
  free(outNode);
  return outNode;
}
