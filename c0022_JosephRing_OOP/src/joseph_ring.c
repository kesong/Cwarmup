#include "joseph_ring.h"
#include <assert.h>
#include <time.h>

extern NODE *sc_head;
extern NODE *sc_tail;

// 约瑟夫环问题
// 0, 1, 2, 3, ..., n-1,
// n一共n个数字排成一个圆圈，从编号为k的数字开始报数，将数到m的数字移除，如此循环，直到没有数字为止，请按移除顺序输出每一轮被移除的数字

// 除了常见的循环链表实现约瑟夫环，用数组也可以实现约瑟夫环，约瑟夫环的本质就是不断从中取出第m个元素，直到最后一个取出，环中没有元素结束
// 数组中存放所有元素，用一个指针指向要取元素的起始位置k，移动指针，每移动一个元素进行计数，一共移动m个位置，取出元素，继续移动m个，
// 如果指针移动到了数组最后一个元素，但是还不够m个位置，指针移动数组第一个元素位置继续计数，移除的元素可以用一个并不是数组中的数字替代，后续移动指针计数时，
// 如果指向的元素是替代数字，为无效数字，则不计数，直至数组中全部为无效数字为止

int *joseph_ring_implement_with_array(int *jr_array, int n, int k, int m,
                                      int *result_array) {
  int count = 0;
  int removed = -65536;
  int *joseph_ring = jr_array + k - 1;
  int *first_element = jr_array;
  int circle_count = 0;
  for (;;) {
    if (count == m && *joseph_ring != removed) {
      *result_array = *joseph_ring;
      result_array++;
      *joseph_ring = removed;
      count = 0;
    }
    joseph_ring++;
    if (*joseph_ring != removed) {
      count++;
    }
    // 最后一个数字如果不是要移除的，就将指针移到第一个元素继续查找，实现类似循环链表的功能
    if (joseph_ring == jr_array + n - 1) {
      if (count == m) {
        *result_array = *joseph_ring;
        result_array++;
        *joseph_ring = removed;
        count = 0;
      }
      joseph_ring = jr_array;
      if (*joseph_ring != removed) {
        count++;
      }
    }
    while (first_element != jr_array + n - 1) {
      if (*first_element == removed) {
        first_element++;
      } else {
        break;
      }
    }
    if (first_element == jr_array + n - 1 && *first_element == removed) {
      break;
    } else {
      first_element = jr_array;
    }
  }
  return result_array;
}

NODE **joseph_ring_implement_with_single_circular_linkedlist(
    NODE *linkedlist, int n, int k, int m, NODE **result_array) {
  int count = 0;
  int index = 1;
  NODE *joseph_ring = NULL;
  NODE *start_node = linkedlist;
  NODE **start_array = result_array;
  while (index++ < k) {
    start_node = start_node->next;
  }

  if (start_node != NULL) {
    joseph_ring = start_node;
  }
  NODE *first_element = linkedlist;
  for (;;) {
    if (count == m && joseph_ring != NULL) {
      *result_array = joseph_ring;
      result_array += 1;
      delete_node_in_single_circular_linkedlist(joseph_ring);
      count = 0;
    }
    joseph_ring = joseph_ring->next;
    count++;
    if (sc_head == sc_tail) {
      *result_array = joseph_ring;
      break;
    }
  }
  delete_node_in_single_circular_linkedlist(joseph_ring);
  return result_array;
}
