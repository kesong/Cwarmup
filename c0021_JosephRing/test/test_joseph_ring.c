#include "test_joseph_ring.h"
#include "../include/log.h"
#include "../src/print_ADT.h"
#include "test_and_validation.h"
#include "test_single_circular_linkedlist.h"

#include <stdlib.h>
#include <string.h>

TestResult test_joseph_ring_implement_with_array() {
  int player_number[NUM] = {0,  1,  3,  8,  10,  11,   14,  21,
                            23, 33, 45, 91, 321, 1024, 1201};
  int k = 3, m = 5;
  int test_result[NUM];
  for (int i = 0; i < NUM; i++) {
    test_result[i] = -1;
  }
  joseph_ring_implement_with_array(player_number, NUM, k, m, test_result);
  print_joseph_ring_result(test_result);
  assert(*(test_result) == 21);
  assert(*(test_result + 5) == 11);
  assert(*(test_result + 14) == 8);
  return TEST_PASSED;
}

TestResult test_joseph_ring_implement_with_scll() {
  NODE *jr_head = create_single_circular_linkedlist();
  int k = 3, m = 5;
  NODE *test_result[NUM] = {NULL};
  int test_result_int[NUM];
  joseph_ring_implement_with_single_circular_linkedlist(jr_head, NUM, k, m,
                                                        test_result);
  for (int i = 0; i < NUM; i++) {
    test_result_int[i] = *(int *)test_result[i]->node_data;
  }
  print_joseph_ring_result(test_result_int);
  assert(*(test_result_int) == 21);
  assert(*(test_result_int + 5) == 11);
  assert(*(test_result_int + 14) == 8);
  free_node();
  return TEST_PASSED;
}

// 接收结果使用一个二重指针，用malloc开辟空间，与上面指针数组方式本质是一样的。
// 这里二重指针只需要保存地址，不保存NODE数据，所以malloc中用sizeof(NODE*)，如果要保存NODE数据就需要使用sizeof(NODE)；
TestResult test_joseph_ring_implement_with_scll_2() {
  NODE *jr_head = create_single_circular_linkedlist();
  int k = 3, m = 5;
  NODE **test_result = (NODE **)malloc(sizeof(NODE *) * NUM);
  memset(test_result, 0, NUM);
  int test_result_int[NUM];
  joseph_ring_implement_with_single_circular_linkedlist(jr_head, NUM, k, m,
                                                        test_result);
  for (int i = 0; i < NUM; i++) {
    test_result_int[i] = *(int *)test_result[i]->node_data;
  }
  print_joseph_ring_result(test_result_int);
  assert(*(test_result_int) == 21);
  assert(*(test_result_int + 5) == 11);
  assert(*(test_result_int + 14) == 8);
  free_node();
  free(test_result);
  test_result = NULL;
  return TEST_PASSED;
}
