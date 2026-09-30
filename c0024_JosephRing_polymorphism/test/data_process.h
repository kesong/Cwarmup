#ifndef DATA_PROCESS
#define DATA_PROCESS

#include "test_double_circular_linkedlist.h"
#include "test_double_linkedlist.h"
#include "test_single_linkedlist.h"
#include <stdio.h>
#include <unistd.h>

#define ARRAY_SIZE 15

int **read_file_and_return_int_array(char *, int *, int **);
NODE **generate_node(int **, NODE **);
NODE_DLL **generate_node_dll(int **, NODE_DLL **);
void init_array(int **);
void free_array(int **);
void init_node_sll(NODE **);
void free_node_sll(NODE **);
void init_node_dll_new(NODE_DLL **);
void free_node_dll_new(NODE_DLL **);
char *get_current_path();
char *get_test_path(char *);
int **get_int_array(char *, char *, char *, char *, int **);
NODE **get_node_array(NODE **, int **);
NODE_DLL **get_node_dll_array(NODE_DLL **, int **);
NODE *convert_node_array(NODE **);
NODE_DLL *convert_node_dll_array(NODE_DLL **);
void free_node_in_array(void *);
void free_node_dll_in_array(NODE_DLL *);
void free_node_in_sll(Linkedlist *);
void free_node_in_scll(Linkedlist *);
void free_node_in_dll(Linkedlist *);
void free_node_in_dcll(DCLinkedList *);

#endif
