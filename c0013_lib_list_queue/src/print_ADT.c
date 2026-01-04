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

void print_adt(Queue *queue) {
  NODE *player_node = NULL;
  if (queue->front == NULL) {
    log_e("error, empty queue, nothing to do.");
    return NULL;
  }
  QueueNode *backup_node = queue->front;
  while (queue->front != NULL) {
    player_node = (NODE *)queue->front->qn_data;
    print_player_node(player_node);
    queue->front = queue->front->next;
  }
  queue->front = backup_node;
}
