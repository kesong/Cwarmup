#include <stdio.h>
#include <stdlib.h>

struct player{
	char* pname;
	int pnumber;
	struct team* tm;
};

struct team{
	char* tname;
	char* city;
};

typedef struct player PLAYER; 
typedef struct team TEAM;

struct player init_player(char* name_str, int num, char* tna, char* city_str){
	PLAYER* p = (PLAYER *)malloc(sizeof(PLAYER));
	p->tm = (TEAM *)malloc(sizeof(TEAM));
	p->pname = name_str;
	p->pnumber = num;
	p->tm->tname = tna;
	p->tm->city = city_str;
	return *p;
}

int size_of_players(PLAYER **player_array){
	int player_count=0;
	while(*player_array != NULL){
		player_array++;
		player_count++;
	}
	return player_count;
}

void print_players(PLAYER *outplayer[]){
	printf("outplayer address: %p \n", outplayer);
	PLAYER *pointer_backup = *outplayer;
	PLAYER** p_p_array = outplayer;
	int player_sum = size_of_players(p_p_array);
	printf("There are %d players. \n", player_sum);
	printf("After caculate players, the outplayer address is: %p \n", outplayer);
	//outplayer = pointer_backup;
	//printf("restored address is: %p \n", outplayer);
	for(int i=0; i<player_sum; i++){
		printf("Player name is: %s \n", outplayer[i]->pname);
		printf("Number is: %d \n", outplayer[i]->pnumber);
		printf("Team is: %s, and located in %s \n", outplayer[i]->tm->tname, outplayer[i]->tm->city);
	}
	printf("##### Players print end. ##### \n");
}

int main(int argc, char *argv){

	//define a pointer, it should be initialized, if not there will be segment fault during compile.
	PLAYER* MJ = (PLAYER *)malloc(sizeof(PLAYER));
	MJ->tm = (TEAM *)malloc(sizeof(TEAM));
	MJ->pname = "Michael Jordan";
	MJ->pnumber = 23;
	MJ->tm->tname = "Bulls";
	MJ->tm->city = "Chicago";

	PLAYER KOBE = init_player("Kobe Bryant", 8, "Lakers", "Los Angeles");
	TEAM sixer = {.tname="76ers", .city="PHI"};
        PLAYER IVERSON = {.pname="Iverson", .pnumber=3, &sixer};
	TEAM piston = {.tname="Pistons", .city="DIO"};
	PLAYER HILL = {.pname="Hill", .pnumber=33, &piston};
	TEAM rapoto = {.tname="Rapoto", .city="VAN"};
	PLAYER CART = {.pname="Cart", .pnumber=15 , &rapoto};

	PLAYER* players[] = {MJ, &KOBE, &IVERSON, &HILL, &CART, NULL};
	print_players(players);
	free(MJ);
	free(MJ->tm);
}
