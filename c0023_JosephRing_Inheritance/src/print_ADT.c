#include "print_ADT.h"
#include "../lib/single_circular_linkedlist.h"
#include "joseph_ring.h"

NODE *phead = NULL;

void print_joseph_ring_result(int *result_array) {
  for (int i = 0; i < NUM - 1; i++) {
    printf("%d, ", *(result_array + i));
  }
  printf("%d.", *(result_array + NUM - 1));
  printf("\n");
  print_seperator(COLOR_YELLOW, "*");
}

void print_integer_linkedlist(SCLinkedlist *scllist, NODE *p_node) {
  phead = scllist->super->head;
  if (p_node == NULL) {
    return;
  }
  if (!is_node_in_scll(scllist, p_node)) {
    printf("print error: node not in list.\n");
    return;
  }
  while (p_node != NULL) {
    printf("%d", *((int *)p_node->node_data));
    print_seperator(COLOR_YELLOW, "*");
    if (p_node->next == phead) {
      return;
    } else
      p_node = p_node->next;
  }
}

void print_joseph_ring_result_by_scll(NODE *result_array) {
  for (int i = 0; i < NUM; i++) {
    printf("%d.", *(int *)(result_array + i)->node_data);
  }
  printf("\n");
  print_seperator(COLOR_YELLOW, "*");
}
