#ifndef DATA_PROCESS
#define DATA_PROCESS

#include "../src/left_leaning_red_black_tree.h"
#include "test_player.h"
#include <stdio.h>
#include <unistd.h>

#define ARRAY_SIZE 27

PLAYER **read_file_and_return_int_array(char *, int *, PLAYER **);
TreeNode **generate_node(PLAYER **, TreeNode **);
void init_array(PLAYER **);
void free_array(PLAYER **);
void init_secondary_ptr(PLAYER **);
void init_node_llrbtree(TreeNode **);
void free_node_llrbtree(TreeNode **);
char *get_current_path();
char *get_test_path(char *);
PLAYER **get_player_array(char *, char *, char *, char *, PLAYER **);
TreeNode **get_node_array(TreeNode **, PLAYER **);
TreeNode *convert_node_array(TreeNode **);
void free_node_in_array(void *);
void free_llrb(LLRBTree);

#endif
