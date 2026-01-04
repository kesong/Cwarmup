#include "test/test_player.h"

int main(int argc, char **argv) {
  Queue *queue = NULL;
  queue = create_queue();
  init_data();

  test_data_structure(queue);
}
