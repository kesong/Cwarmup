#include "stack.h"

// 初始化栈，用memset将成员全部初始化为0，指针类型的成员初始化为NULL；
// 使用malloc分配的内存空间，都要做初始化，要将结构体每个成员都置为0或者NULL，避免程序运行出现指针指向非法地址的问题
// 调用函数create_stack()创建一个栈，使用gdb打印栈中的内容如下，可以看到element数组的前两个元素地址不为NULL，系统分配了一个不知名地址
// (gdb) p *cr_stack
// $33 = {element = {0x7ffff7e03b20 <main_arena+96>, 0x7ffff7e03b20
// <main_arena+96>, 0x0 <repeats 28 times>}, top = 0}
// 使用memset()完成初始化之后，打印如下，element数组的30个元素全部置为NULL（指针变量）
// (gdb) p *cr_stack
// $34 = {element = {0x0 <repeats 30 times>}, top = 0}
Stack *create_stack() {
  Stack *cr_stack = (Stack *)malloc(sizeof(Stack));
  if (cr_stack == NULL) {
    log_e("error, create stack failed, malloc space for stack failed.");
  }
  memset(cr_stack, 0, sizeof(Stack));
  // 将top设置为-1，push函数中先执行自加操作，将需要push入栈的值放入栈中的第一个位置，如果是0的话后续push就需要做一些判断，避免将top位置已有的值覆盖了
  cr_stack->top = -1;
  log_i("The maximum size of Stack is %d, if it is not enough, you shold set "
        "greater.",
        MAX_SIZE);
  return cr_stack;
}

void free_stack(Stack *stack) { free(stack); }

int stack_size(Stack *stack) {
  if (stack->top == -1) {
    return 0;
  }
  return stack->top + 1;
}

bool is_stack_full(Stack *stack) {
  int count = 0;
  if (stack->top == MAX_SIZE - 1) {
    return true;
  } else {
    return false;
  }
}

bool is_stack_empty(Stack *stack) {
  if (stack->top < 0 || stack->element[0] == NULL) {
    return true;
  } else {
    return false;
  }
}

bool push(Stack *stack, void *value) {
  if (is_stack_full(stack)) {
    log_e("%s", "error, stack is full.");
    return false;
  }
  if (stack->top >= MAX_SIZE) {
    log_e("%s", "push fail, top pointer beyond the max address.");
    return false;
  }
  if (stack->top < 0) {
    stack->top = -1;
  }
  stack->element[++(stack->top)] = value;

  return true;
}

bool pop(Stack *stack, void **data_poped) {
  if (is_stack_empty(stack)) {
    log_e("%s", "error, stack is empty.");
    return false;
  }
  if (stack->top < 0 || stack->element[0] == NULL) {
    log_e("%s", "pop fail, top pointer smaller than the bottom address.");
    return false;
  }
  if (stack->element[stack->top] == NULL && stack->top > 0) {
    stack->top--;
  }
  *data_poped = stack->element[stack->top];
  stack->element[stack->top--] = NULL;
  return true;
}
