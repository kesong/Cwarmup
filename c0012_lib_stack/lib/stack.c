#include "stack.h"

// 初始化栈，用memset将成员全部初始化为0，指针类型的成员初始化为NULL；
Stack *create_stack() {
  Stack *cr_stack = (Stack *)malloc(sizeof(Stack));
  memset(cr_stack, 0, sizeof(Stack));
  return cr_stack;
}

void destory_stack(Stack *stack) {
  if (stack->element[stack->top] != NULL) {
    pop(stack);
  }
}

bool is_full(Stack *stack) {
  int count = 0;
  if (stack->top == MAX_SIZE - 1) {
    return true;
  } else {
    return false;
  }
}

bool is_empty(Stack *stack) {
  if (stack->top < 0 || stack->element[0] == NULL) {
    return true;
  } else {
    return false;
  }
}

bool push(Stack *stack, void *value) {
  if (is_full(stack)) {
    log_e("%s", "error, stack is full.");
    return false;
  }
  if (stack->top >= MAX_SIZE) {
    log_e("%s", "push fail, top pointer beyond the max address.");
    return false;
  }
  stack->element[stack->top++] = value;
  return true;
}

bool pop(Stack *stack) {
  if (is_empty(stack)) {
    log_e("%s", "error, stack is empty.");
    return false;
  }
  if (stack->top < 0 || stack->element[0] == NULL) {
    log_e("%s", "pop fail, top pointer smaller than the bottom address.");
    return false;
  }
  stack->element[stack->top--] = NULL;
  return true;
}
