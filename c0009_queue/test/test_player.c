#include "test_player.h"

#define	print_size(x, y)	printf("%20s size is:  %3d Bytes.\n", x, sizeof(y))
#define print_offset(x, y) 	printf("%20s is: %3d Bytes.\n", x, y)

void init_player_queue(){
	PLAYER* player = NULL;
	TEAM* player_tm = NULL;
	NODE node_struct;
	PLAYER player_struct;
	TEAM team;
	print_size("struct node", NODE);
	print_size("*ptr_data", node_struct.ptr_data);
	print_size("struct player", PLAYER);
	print_size("player name", player_struct.pname);
	print_size("player number", player_struct.pnumber);
	print_size("player salary", player_struct.salary);
	print_size("struct team", TEAM);
	print_size("*tname", team.tname);
	print_size("*city", team.city);
	print_size("pointer NODE*", head);
	print_size("pointer PLAYER*", player);
	print_size("pointer TEAM*", player_tm);

	player = (PLAYER*)malloc(sizeof(PLAYER));
	player_tm = (TEAM*)malloc(sizeof(TEAM));
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	int pnumber_offset = sizeof(player_struct.pname);
	int salary_offset = pnumber_offset + sizeof(player_struct.pnumber);
	int tm_offset = pnumber_offset + salary_offset;
	int tname_offset = tm_offset + sizeof(player_struct.tm);
	int city_offset = tname_offset + sizeof(player_struct.tm->tname);
	print_offset("pnumber_offset", pnumber_offset);
	print_offset("salary_offset", salary_offset);
	print_offset("tm_offset",tm_offset);
	print_offset("tname_offset", tname_offset);
	print_offset("city_offset", city_offset);
	head->ptr_data = NULL;
	tail = head;
	head->next = NULL;
}

void print_player_queue(){
	NODE* print_node = head;
	PLAYER* player = NULL;
	if(is_empty()){
		printf("NONE: empty queue!\n");
		return;
	}
	while(print_node->ptr_data != NULL){
		player = (PLAYER*)(print_node->ptr_data);
		printf("Name  : %20s\n", player->pname);
		printf("Number: %20d\n", player->pnumber);
		printf("Salary: %20d\n", player->salary);
		printf("Team  : %20s\n", player->tm->tname);
		printf("City  : %20s\n", player->tm->city);
		printf("****************************************************\n");
		print_node = print_node->next;
		if(print_node == NULL){
			return;
		}
	}
}
