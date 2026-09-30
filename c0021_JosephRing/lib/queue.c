#include "queue.h"

// 初始化队列，用memset将成员全部初始化为0，指针类型的成员初始化为NULL；
Queue *create_queue() {
  Queue *cr_queue = (Queue *)malloc(sizeof(Queue));
  if (cr_queue == NULL) {
    log_e("error, create queue fail, malloc space for queue failed.");
    exit(EXIT_FAILUE);
  }
  memset(cr_queue, 0, sizeof(Queue));
  log_i("The maximum size of Queue is %d, if it is not enough, you shoud set "
        "the size greater.",
        MAX_SIZE);
  return cr_queue;
}

void free_queue(Queue *queue) { free(queue); }

bool is_queue_empty(Queue *queue) { return queue->front == NULL; }

int size_of_queue(Queue *queue, int *que_size) {
  if (!*que_size) {
    log_e("Please pass 0 to the second parameter.");
    return -1;
  }
  while (queue->front != NULL) {
    (*que_size)++;
  }
  return 0;
}

QueueNode *enqueue(Queue *queue, void *value) {
  QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
  if (newNode == NULL) {
    log_e("error, malloc for new Node failed.");
    exit(EXIT_FAILURE);
  }
  newNode->qn_data = value;
  newNode->next = NULL;
  if (queue->rear == NULL) {
    queue->front = queue->rear = newNode;
  } else {
    queue->rear->next = newNode;
    queue->rear = newNode;
  }
  return queue->rear;
}

bool dequeue(Queue *queue, QueueNode **deq_node) {
  if (is_queue_empty(queue)) {
    log_e("error, queue is empty.");
    return false;
  }
  *deq_node = queue->front;
  queue->front = queue->front->next;
  if (queue->front == NULL) {
    queue->rear = NULL;
  }
  return true;
}
