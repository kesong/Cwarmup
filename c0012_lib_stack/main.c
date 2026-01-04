#include "test/test_player.h"

int main(int argc, char **argv) {
  Stack *stack = NULL;
  stack = create_stack();
  init_data();

  test_data_structure(stack);
}
