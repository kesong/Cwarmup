#include "print_ADT.h"
#include "../test/test_player.h"

void print_player_node(NODE *p_node) {
  if (p_node == NULL) {
    log_i("null node.");
    return NULL;
  }
  PLAYER *player = NULL;
  player = (PLAYER *)(p_node->ptr_data);
  if (player == NULL) {
    log_i("null player.");
    return NULL;
  }
  log_i("%s", "this node is a PLAYER_NODE.");
  log_i("%6s:%20s", "Name", player->pname);
  log_i("%6s:%20d", "Number", player->pnumber);
  log_i("%6s:%20d", "Salary", player->salary);
  log_i("%6s:%20s", "Team", player->tm->tname);
  log_i("%6s:%20s", "City", player->tm->city);
  print_seperator(COLOR_YELLOW, "*");
}

// 从栈中获取元素的时候，top指针指向的是栈中元素的地址，所以要用二重指针获取栈中元素
void print_stack(Stack *stack) {
  NODE *player_node = NULL;
  if (stack->top > MAX_SIZE || stack->top < 0) {
    log_e("error, out of stack boundry.");
    return NULL;
  }
  if (is_empty(stack)) {
    log_i("stack empty.");
    return NULL;
  }
  // stack->top--;
  while (stack->top < MAX_SIZE && stack->top > 0) {
    player_node = (NODE *)stack->element[--stack->top];
    print_player_node(player_node);
  }
}
