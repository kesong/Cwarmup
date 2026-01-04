#include "double_direction_linklist.h"

int main(int argc, char** argv){
    	init_linklist();
	int print_count = 0;
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
    	print_linklist(head);

	/* fill out the linklist with some data.*/
	TEAM tm_LA = {.tname="Lakers", .city="LA"};
	PLAYER kobe = {.pname="Kobe", .pnumber=8, .salary=3500, .tm=&tm_LA};

	TEAM tm_CH = {"Bulls", "Chicago"};
	PLAYER jordan = {"Michael", 23, 3000, .tm=&tm_CH};

	PLAYER* yao = (PLAYER*)malloc(sizeof(PLAYER));
	yao->tm = (TEAM*)malloc(sizeof(TEAM));
	yao->pname="Yao", yao->pnumber=11, yao->salary=2500, yao->tm->tname="Rockets", yao->tm->city="Hous";

	PLAYER* yi = (PLAYER*)malloc(sizeof(PLAYER));
	yi->tm = (TEAM*)malloc(sizeof(TEAM));
	yi->pname="Yi", yi->pnumber=6, yi->salary=500, yi->tm->tname="Bucks", yi->tm->city="Milv";

	PLAYER* camelo = (PLAYER*)malloc(sizeof(PLAYER));
	camelo->tm = (TEAM*)malloc(sizeof(TEAM));
	camelo->pname="Camelo", camelo->pnumber=15, camelo->salary=2700, camelo->tm->tname="Nick", camelo->tm->city="NY";

	PLAYER* dunken = (PLAYER*)malloc(sizeof(PLAYER));
	dunken->tm = (TEAM*)malloc(sizeof(TEAM));
	dunken->pname="Tim", dunken->pnumber=21, dunken->salary=3200, dunken->tm->tname="Spurs", dunken->tm->city="Santo";

	PLAYER* curry = (PLAYER*)malloc(sizeof(PLAYER));
	curry->tm = (TEAM*)malloc(sizeof(TEAM));
	curry->pname="Curry", curry->pnumber=30, curry->salary=5000, curry->tm->tname="War", curry->tm->city="San";

	PLAYER* jimmy = (PLAYER*)malloc(sizeof(PLAYER));
	jimmy->tm = (TEAM*)malloc(sizeof(TEAM));
	jimmy->pname="Jimmy", jimmy->pnumber=10, jimmy->salary=5500, jimmy->tm->tname="War", jimmy->tm->city="San";

	PLAYER* book = (PLAYER*)malloc(sizeof(PLAYER));
	book->tm = (TEAM*)malloc(sizeof(TEAM));
	book->pname="Book", book->pnumber=0, book->salary=3800, book->tm->tname="Suns", book->tm->city="Phix";

	PLAYER* paul = (PLAYER*)malloc(sizeof(PLAYER));
	paul->tm = (TEAM*)malloc(sizeof(TEAM));
	paul->pname="Paul", paul->pnumber=3, paul->salary=4000, paul->tm->tname="Suns", paul->tm->city="Phix";

	PLAYER* rodman = (PLAYER*)malloc(sizeof(PLAYER));
	rodman->tm = (TEAM*)malloc(sizeof(TEAM));
	rodman->pname="Rodman", rodman->pnumber=91, rodman->salary=1000, rodman->tm->tname="Piston", rodman->tm->city="Dix";

	PLAYER* jokic = (PLAYER*)malloc(sizeof(PLAYER));
	jokic->tm = (TEAM*)malloc(sizeof(TEAM));
	jokic->pname="Jokic", jokic->pnumber=15, jokic->salary=6000, jokic->tm->tname="Nug", jokic->tm->city="Den";

	static NODE* kobe_node = NULL;
	kobe_node = (NODE*)malloc(sizeof(NODE));
	kobe_node->player_node = &kobe, kobe_node->next=NULL;

	static NODE* jordan_node = NULL;
	jordan_node = (NODE*)malloc(sizeof(NODE));
	jordan_node->player_node = &jordan, jordan_node->next=NULL;

	static NODE* yao_node = NULL;
	yao_node = (NODE*)malloc(sizeof(NODE));
	yao_node->player_node = yao, yao_node->next=NULL;

	static NODE* yi_node = NULL;
	yi_node = (NODE*)malloc(sizeof(NODE));
	yi_node->player_node = yi, yi_node->next=NULL;

	static NODE* camelo_node = NULL;
	camelo_node = (NODE*)malloc(sizeof(NODE));
	camelo_node->player_node = camelo, camelo_node->next=NULL;

	static NODE* dunken_node = NULL;
	dunken_node = (NODE*)malloc(sizeof(NODE));
	dunken_node->player_node = dunken, dunken_node->next=NULL;

	static NODE* curry_node = NULL;
	curry_node = (NODE*)malloc(sizeof(NODE));
	curry_node->player_node = curry, curry_node->next=NULL;

	static NODE* jimmy_node = NULL;
	jimmy_node = (NODE*)malloc(sizeof(NODE));
	jimmy_node->player_node = jimmy, jimmy_node->next=NULL;

	static NODE* book_node = NULL;
	book_node = (NODE*)malloc(sizeof(NODE));
	book_node->player_node = book, book_node->next=NULL;

	static NODE* paul_node = NULL;
	paul_node = (NODE*)malloc(sizeof(NODE));
	paul_node->player_node = paul, paul_node->next=NULL;

	static NODE* rodman_node = NULL;
	rodman_node = (NODE*)malloc(sizeof(NODE));
	rodman_node->player_node = rodman, rodman_node->next=NULL;

	static NODE* jokic_node = NULL;
	jokic_node = (NODE*)malloc(sizeof(NODE));
	jokic_node->player_node = jokic, jokic_node->next=NULL;
	/* data fill out complete.*/

	insert_node_as_head(jordan_node);

	insert_node_in_middle(yao_node, 3);

	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_linklist(head);

	delete_node(paul_node);
	
	insert_node_as_tail(jokic_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_linklist(head);

	insert_node_in_middle(rodman_node, 2);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_linklist(head);

	insert_node_in_middle(jimmy_node, 2);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_linklist(head);

	insert_node_as_head(book_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_linklist(head);

	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_linklist(jimmy_node);

	delete_node(kobe_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_linklist(kobe_node);
	
	delete_node(yao_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_linklist(head);

	insert_node_in_middle(kobe_node, 4);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_linklist(head);

	insert_node_as_tail(yi_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_linklist(head);

	delete_node(book_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_linklist(head);

	insert_node_as_head(dunken_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_linklist(head);

	insert_node_in_middle(camelo_node, 3);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_linklist(head);

	insert_node_as_tail(curry_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_linklist(head);

	delete_node(jordan_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_linklist(head);

	delete_node(kobe_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_linklist(head);

	insert_node_as_head(jordan_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_linklist(head);

	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
    	print_linklist(tail);
}
