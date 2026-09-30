#include "test_and_validation.h"
#include "test_double_circular_linkedlist.h"
#include "test_double_linkedlist.h"
#include "test_joseph_ring.h"
#include "test_single_circular_linkedlist.h"
#include "test_single_linkedlist.h"
#include <assert.h>

#define CASE_SUM 20

void run_test_suites(TestCase *test_cases, size_t test_count) {
  for (int i = 0; i < test_count; i++) {
    if (test_cases[i].case_name == NULL) {
      return;
    }
    if (test_cases[i].test_function() == TEST_PASSED) {
      log_d("%s passed.", test_cases[i].case_name);
    } else {
      log_d("%s failed.", test_cases[i].case_name);
    }
  }
}

int main(int argc, char **argv) {

  TestCase test_case[CASE_SUM] = {
      {"test joseph ring with array", test_joseph_ring_implement_with_array},
      {"test scll is empty", test_is_empty},
      {"test insert in scll", test_insert_node},
      {"test delete in scll", test_delete_node},
      {"test create scll", test_create_single_circular_linkedlist},
      {"test joseph ring with scll", test_joseph_ring_implement_with_scll},
      {"test joseph ring with scll 2", test_joseph_ring_implement_with_scll_2},
      {"test insert to empty sll", test_insert_node_to_empty_sll},
      {"test insert in sll", test_insert_node_in_sll},
      {"test get tail", test_get_tail},
      {"test delete node in sll", test_delete_node_in_scll},
      {"test insert node to empty dll", test_insert_node_to_empty_dll},
      {"test insert node to dll", test_insert_node_to_dll},
      {"test delete node in dll", test_delete_node},
      {"test size of dcll", test_size_of_dcll},
      {"test insert node dcll", test_insert_node_dcll},
      {"test delete node dcll", test_delete_middle_node_dcll}

  };

  run_test_suites(test_case, CASE_SUM);
}
