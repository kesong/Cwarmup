#include "log.h"

typedef struct team {
  char *tname;
  char *city;
} Team;

typedef struct player {
  char *pname;
  int pnumber;
  int salary;
  Team *tm;
} Player;

void print_player(Player *);
