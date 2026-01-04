#ifndef TEST_PLAYER
#define TEST_PLAYER

#include "../lib/stack.h"
#include "log.h"
#include "print_ADT.h"

typedef struct node NODE;
typedef struct player PLAYER;
typedef struct team TEAM;

struct node {
  void *ptr_data;
};

struct player {
  char *pname;
  int pnumber;
  int salary;
  struct team *tm;
};

struct team {
  char *tname;
  char *city;
};

void init_data();

void test_data_structure(Stack *);

#endif // TEST_PLAYER
