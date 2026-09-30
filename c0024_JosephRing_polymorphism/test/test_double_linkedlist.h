#ifndef TEST_DOUBLE_LINKEDLIST
#define TEST_DOUBLE_LINKEDLIST

#include "../lib/double_linkedlist.h"
#include "test_and_validation.h"

NODE_DLL *convert_node_dll_array(NODE_DLL **);
DoubleLinkedList *init_double_linkedlist();
TestResult test_insert_node_to_empty_dll();
TestResult test_insert_node_to_dll();
TestResult test_delete_node_dll();

#endif
