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

void test_player_queue(){
	int print_count = 0;
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();

	/* fill out the queue with some data.*/
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
	kobe_node->ptr_data = &kobe, kobe_node->next=NULL;

	static NODE* jordan_node = NULL;
	jordan_node = (NODE*)malloc(sizeof(NODE));
	jordan_node->ptr_data = &jordan, jordan_node->next=NULL;

	static NODE* yao_node = NULL;
	yao_node = (NODE*)malloc(sizeof(NODE));
	yao_node->ptr_data = yao, yao_node->next=NULL;

	static NODE* yi_node = NULL;
	yi_node = (NODE*)malloc(sizeof(NODE));
	yi_node->ptr_data = yi, yi_node->next=NULL;

	static NODE* camelo_node = NULL;
	camelo_node = (NODE*)malloc(sizeof(NODE));
	camelo_node->ptr_data = camelo, camelo_node->next=NULL;

	static NODE* dunken_node = NULL;
	dunken_node = (NODE*)malloc(sizeof(NODE));
	dunken_node->ptr_data = dunken, dunken_node->next=NULL;

	static NODE* curry_node = NULL;
	curry_node = (NODE*)malloc(sizeof(NODE));
	curry_node->ptr_data = curry, curry_node->next=NULL;

	static NODE* jimmy_node = NULL;
	jimmy_node = (NODE*)malloc(sizeof(NODE));
	jimmy_node->ptr_data = jimmy, jimmy_node->next=NULL;

	static NODE* book_node = NULL;
	book_node = (NODE*)malloc(sizeof(NODE));
	book_node->ptr_data = book, book_node->next=NULL;
	
	static NODE* paul_node = NULL;
	paul_node = (NODE*)malloc(sizeof(NODE));
	paul_node->ptr_data = paul, paul_node->next=NULL;

	static NODE* rodman_node = NULL;
	rodman_node = (NODE*)malloc(sizeof(NODE));
	rodman_node->ptr_data = rodman, rodman_node->next=NULL;

	static NODE* jokic_node = NULL;
	jokic_node = (NODE*)malloc(sizeof(NODE));
	jokic_node->ptr_data = jokic, jokic_node->next=NULL;
	/* data fill out complete.*/

	enqueue(jordan_node);

	enqueue(yao_node);

	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();

	dequeue();
	
	enqueue(jokic_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();

	enqueue(rodman_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();

	enqueue(jimmy_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();

	enqueue(book_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();

	dequeue();

	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();

	dequeue();
	dequeue();
	dequeue();

	enqueue(kobe_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();
	
	enqueue(yao_node);
	dequeue();
	dequeue();
	dequeue();
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();

	dequeue();

	enqueue(kobe_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();

	enqueue(yi_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();

	enqueue(book_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();

	enqueue(dunken_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();

	enqueue(camelo_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();

	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	enqueue(curry_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();

	dequeue();
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();

	dequeue();
	dequeue();
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();

	enqueue(jordan_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();

	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();
	
	free(jokic), free(rodman), free(paul), free(book), free(jimmy), free(curry), free(dunken), free(camelo), free(yi), free(yao);
	
	free(kobe_node), free(jordan_node), free(yao_node), free(yi_node), free(camelo_node), free(dunken_node);
	free(curry_node), free(jimmy_node), free(book_node), free(paul_node), free(rodman_node), free(jokic_node);
	
	queue_destroy();
}
