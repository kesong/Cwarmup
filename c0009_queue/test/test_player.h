#ifndef TEST_PLAYER
#define TEST_PLAYER
#include "queue.h"


typedef struct player PLAYER;
typedef struct team TEAM;

struct player{
	char* pname;
  	int pnumber;
	int salary;
	struct team* tm;
};
 
struct team{
	char* tname;
	char* city;
};

void init_player_queue();

void print_player_queue();

#endif //TEST_PLAYER
