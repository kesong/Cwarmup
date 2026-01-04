#ifndef STACK_LIB
#define STACK_LIB

#include "log.h"
#include <stdbool.h>
#include <stdio.h>

// 栈的大小就只有30，只能存放30个元素，如需更大，需要将这里修改成期望的大小
#define MAX_SIZE 30

typedef struct {
  void *element[MAX_SIZE];
  int top;
} Stack;

// 假如将一个NODE（在test/test_player.h中定义）类型的数据插入stack，成为栈中的第一个元素，在gdb调试的时候，查看栈中第一个元素是否正确的方法
// 栈结构体中第一个元素的地址表示法为stack->element_array[0]，使用gdb命令p查看地址信息，p
// stack->element_array[0]
// 由于元素类型为void不可以使用直接加指针符号*的方式解引用，*stack->element_array[0]非法。
// 要做强制转换来指明具体的类型，p
// (NODE*)stack->element_array[0],可以看到NODE结构体中的成员地址，NODE结构体中只有一个成员ptr_data，
// 这个也是void指针，不能直接解引用。继续强制转换，对(stack->element_array[0])->ptr_data强制转换,传递的实参NODE类型中的成员为PLAYER类型
// p
// *(PLAYER*)(((NODE*)stack->element_array)->ptr_data)，可以看到插入的节点具体信息。
// 这也是void*指针通用性强的一面，可以接收任意类型的指针，使用的时候要做具体类型的强制转换
// 对于stack->top来说，保存的是stack->element_array[0]的地址，是个二重指针，所以在解引用的时候需要使用二重指针来解析，那么获取stack->top指向的数据
// 就是(NODE**)stack->top，这个就等于(NODE*)stack->element_array[0]，进一步获取stack->top中成员指向的地址((NODE**)stack->top)->ptr_data，这也是void指针。
// *(PLAYER*)(((NODE**)stack->top)->ptr_data)，获取到ptr_data成员的具体内容，一个PLAYER信息。
// 如下这种定义栈的方式不号，计划让top指向数组的首地址，作为也是结构体的成员之一，他也有系统给它分配的地址，比较容易指向其他地方。

Stack *create_stack();
void free_stack(Stack *);
bool is_stack_full(Stack *);
bool is_stack_empty(Stack *);
bool push(Stack *, void *);
bool pop(Stack *, void **);
int size(Stack *);

#endif
