#include "test_player.h"

#define	print_size(x, y)	printf("%20s size is:  %3d Bytes.\n", x, sizeof(y))
#define print_offset(x, y) 	printf("%20s is: %3d Bytes.\n", x, y)

#define COLOR_RESET	"\033[0m"
#define COLOR_RED 	"\033[31m"
#define COLOR_GREEN	"\033[32m"
#define COLOR_YELLOW	"\033[33m"
#define COLOR_BLUE	"\033[34m"
#define COLOR_MAGENTA	"\033[35m"
#define COLOR_CYAN	"\033[36m"
#define COLOR_WHITE	"\033[37m"

#define CHARAC 55


#define PRINT_SEPERATOR(color, x)				\
{								\
	for(int i=CHARAC; i>0; i--){				\
		printf("%s%s", color, x);			\
	}							\
	printf(COLOR_RESET"\n");				\
}								

void init_player_queue(){
	PLAYER* player = NULL;
	TEAM* player_tm = NULL;
	NODE node_struct;
	PLAYER player_struct;
	TEAM team;
	void* ptr_void = NULL;
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
	print_size("void*:", ptr_void);

	player = (PLAYER*)malloc(sizeof(PLAYER));
	player_tm = (TEAM*)malloc(sizeof(TEAM));
	//printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	PRINT_SEPERATOR(COLOR_MAGENTA, "+");
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
}

void print_player_node(NODE* p_node){
	PLAYER* player = NULL;
	player = (PLAYER*)(p_node->ptr_data);
	printf("this node is a PLAYER_NODE.\n");
	printf("Name  : %20s\n", player->pname);
	printf("Number: %20d\n", player->pnumber);
	printf("Salary: %20d\n", player->salary);
	printf("Team  : %20s\n", player->tm->tname);
	printf("City  : %20s\n", player->tm->city);
	//printf("\033[31m****************************************************\033[0m\n");
	PRINT_SEPERATOR(COLOR_RED, "*");
}

void print_player_name(NODE* p_node){
	printf("this node is a PLAYER_NAME.\n");
	char* player_name = NULL;
	player_name = (char*)p_node->ptr_data;
	printf("Player name: %-20s\n", player_name);
	//printf("\033[33m****************************************************\033[0m\n");
	PRINT_SEPERATOR(COLOR_YELLOW, "*");
}

void print_player_year(NODE* p_node){
	printf("this node is a PLAYER_YEAR.\n");
	//int player_year = (int)p_node->ptr_data;		//int占用4位，ptr_data是void*类型，占用8位，将一个8位的数据转化为一个4位的数据，这里强制转换以后会有数值的错误；
	int* player_year_addr = (int*)p_node->ptr_data; 	//使用int*接收void*可以解决这个问题，但是能否彻底解决这个问题有待验证和思考	
	printf("Player career start year: %d\n", *player_year_addr); 
	//printf("\033[34m****************************************************\033[0m\n");
	PRINT_SEPERATOR(COLOR_BLUE, "*");
}

void print_player_queue(){
	NODE* print_node = head;
	if(is_empty()){
		printf("NONE: empty queue!\n");
		return;
	}
	while(print_node->ptr_data != NULL){
		switch(print_node->node_t){
			case PLAYER_NODE:
				print_player_node(print_node);
				break;
			case PLAYER_NAME:
				print_player_name(print_node);
				break;
			case PLAYER_YEAR:
				print_player_year(print_node);
				break;
			default:
				printf("error: no info found!\n");
				break;
		}
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


	/* player name. */
	char* michael = "Michael Jordan";
	NODE* mj_name_node = (NODE*)malloc(sizeof(NODE));
	mj_name_node->ptr_data = michael, mj_name_node->next = NULL;
	mj_name_node->node_t=PLAYER_NAME;

	char* kb_name = "Kobe Bryant";
	NODE* kb_name_node = (NODE*)malloc(sizeof(NODE));
	kb_name_node->ptr_data = kb_name, kb_name_node->next = NULL;
	kb_name_node->node_t=PLAYER_NAME;

	char* td_name = "Tim Dunkan";
	NODE* td_name_node = (NODE*)malloc(sizeof(NODE));
	td_name_node->ptr_data = td_name, td_name_node->next = NULL;
	td_name_node->node_t=PLAYER_NAME;

	char* curry_name = "Stephen Curry";
	NODE* sc_name_node = (NODE*)malloc(sizeof(NODE));
	sc_name_node->ptr_data = curry_name, sc_name_node->next = NULL;
	sc_name_node->node_t=PLAYER_NAME;

	char* lj_name = "Lebron James";
	NODE* lj_name_node = (NODE*)malloc(sizeof(NODE));
	lj_name_node->ptr_data = lj_name, lj_name_node->next = NULL;
	lj_name_node->node_t=PLAYER_NAME;

	char* kg_name = "Kevin Garnet";
	NODE* kg_name_node = (NODE*)malloc(sizeof(NODE));
	kg_name_node->ptr_data = kg_name, kg_name_node->next = NULL;
	kg_name_node->node_t=PLAYER_NAME;

	char* db_name = "Devin Book";
	NODE* db_name_node = (NODE*)malloc(sizeof(NODE));
	db_name_node->ptr_data = db_name, db_name_node->next = NULL;
	db_name_node->node_t=PLAYER_NAME;

	char* cp_name = "Chris Paul";
	NODE* cp_name_node = (NODE*)malloc(sizeof(NODE));
	cp_name_node->ptr_data = cp_name, cp_name_node->next = NULL;
	cp_name_node->node_t=PLAYER_NAME;

	char* yao_name = "Yao Ming";
	NODE* ym_name_node = (NODE*)malloc(sizeof(NODE));
	ym_name_node->ptr_data = yao_name, ym_name_node->next = NULL;
	ym_name_node->node_t=PLAYER_NAME;

	char* yi_name = "Yi Jianlian";
	NODE* yi_name_node = (NODE*)malloc(sizeof(NODE));
	yi_name_node->ptr_data = yi_name, yi_name_node->next = NULL;
	yi_name_node->node_t=PLAYER_NAME;

	char* wzz_name = "Wang Zhizhi";
	NODE* wzz_name_node = (NODE*)malloc(sizeof(NODE));
	wzz_name_node->ptr_data = wzz_name, wzz_name_node->next = NULL;
	wzz_name_node->node_t=PLAYER_NAME;

	char* dr_name = "Derick Rose";
	NODE* dr_name_node = (NODE*)malloc(sizeof(NODE));
	dr_name_node->ptr_data = dr_name, dr_name_node->next = NULL;
	dr_name_node->node_t=PLAYER_NAME;

	char* ra_name = "Ray Allen";
	NODE* ra_name_node = (NODE*)malloc(sizeof(NODE));
	ra_name_node->ptr_data = ra_name, ra_name_node->next = NULL;
	ra_name_node->node_t=PLAYER_NAME;
	/* player name initial complete. */

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
	kobe_node->node_t=PLAYER_NODE;

	static NODE* jordan_node = NULL;
	jordan_node = (NODE*)malloc(sizeof(NODE));
	jordan_node->ptr_data = &jordan, jordan_node->next=NULL;
	jordan_node->node_t=PLAYER_NODE;

	static NODE* yao_node = NULL;
	yao_node = (NODE*)malloc(sizeof(NODE));
	yao_node->ptr_data = yao, yao_node->next=NULL;
	yao_node->node_t=PLAYER_NODE;

	static NODE* yi_node = NULL;
	yi_node = (NODE*)malloc(sizeof(NODE));
	yi_node->ptr_data = yi, yi_node->next=NULL;
	yi_node->node_t=PLAYER_NODE;

	static NODE* camelo_node = NULL;
	camelo_node = (NODE*)malloc(sizeof(NODE));
	camelo_node->ptr_data = camelo, camelo_node->next=NULL;
	camelo_node->node_t=PLAYER_NODE;

	static NODE* dunken_node = NULL;
	dunken_node = (NODE*)malloc(sizeof(NODE));
	dunken_node->ptr_data = dunken, dunken_node->next=NULL;
	dunken_node->node_t=PLAYER_NODE;

	static NODE* curry_node = NULL;
	curry_node = (NODE*)malloc(sizeof(NODE));
	curry_node->ptr_data = curry, curry_node->next=NULL;
	curry_node->node_t=PLAYER_NODE;

	static NODE* jimmy_node = NULL;
	jimmy_node = (NODE*)malloc(sizeof(NODE));
	jimmy_node->ptr_data = jimmy, jimmy_node->next=NULL;
	jimmy_node->node_t=PLAYER_NODE;

	static NODE* book_node = NULL;
	book_node = (NODE*)malloc(sizeof(NODE));
	book_node->ptr_data = book, book_node->next=NULL;
	book_node->node_t=PLAYER_NODE;
	
	static NODE* paul_node = NULL;
	paul_node = (NODE*)malloc(sizeof(NODE));
	paul_node->ptr_data = paul, paul_node->next=NULL;
	paul_node->node_t=PLAYER_NODE;

	static NODE* rodman_node = NULL;
	rodman_node = (NODE*)malloc(sizeof(NODE));
	rodman_node->ptr_data = rodman, rodman_node->next=NULL;
	rodman_node->node_t=PLAYER_NODE;

	static NODE* jokic_node = NULL;
	jokic_node = (NODE*)malloc(sizeof(NODE));
	jokic_node->ptr_data = jokic, jokic_node->next=NULL;
	jokic_node->node_t=PLAYER_NODE;
	/* data fill out complete.*/


	/* player year. */
	int mj_y = 1985;
	NODE* mj_year_node = (NODE*)malloc(sizeof(NODE));
	mj_year_node->ptr_data = &mj_y, mj_year_node->next = NULL;
	mj_year_node->node_t=PLAYER_YEAR;

	int kb_y = 1996;
	NODE* kb_year_node = (NODE*)malloc(sizeof(NODE));
	kb_year_node->ptr_data = &kb_y, kb_year_node->next = NULL;
	kb_year_node->node_t=PLAYER_YEAR;

	int td_y = 1997;
	NODE* td_year_node = (NODE*)malloc(sizeof(NODE));
	td_year_node->ptr_data = &td_y, td_year_node->next = NULL;
	td_year_node->node_t=PLAYER_YEAR;

	int sc_y = 2005;
	NODE* sc_year_node = (NODE*)malloc(sizeof(NODE));
	sc_year_node->ptr_data = &sc_y, sc_year_node->next = NULL;
	sc_year_node->node_t=PLAYER_YEAR;

	int lj_y = 2003;
	NODE* lj_year_node = (NODE*)malloc(sizeof(NODE));
	lj_year_node->ptr_data = &lj_y, lj_year_node->next = NULL;
	lj_year_node->node_t=PLAYER_YEAR;

	int kg_y = 1995;
	NODE* kg_year_node = (NODE*)malloc(sizeof(NODE));
	kg_year_node->ptr_data = &kg_y, kg_year_node->next = NULL;
	kg_year_node->node_t=PLAYER_YEAR;

	int db_y = 2015;
	NODE* db_year_node = (NODE*)malloc(sizeof(NODE));
	db_year_node->ptr_data = &db_y, db_year_node->next = NULL;
	db_year_node->node_t=PLAYER_YEAR;

	int cp_y = 2005;
	NODE* cp_year_node = (NODE*)malloc(sizeof(NODE));
	cp_year_node->ptr_data = &cp_y, cp_year_node->next = NULL;
	cp_year_node->node_t=PLAYER_YEAR;

	int ym_y = 2002;
	NODE* ym_year_node = (NODE*)malloc(sizeof(NODE));
	ym_year_node->ptr_data = &ym_y, ym_year_node->next = NULL;
	ym_year_node->node_t=PLAYER_YEAR;

	int yi_y = 2006;
	NODE* yi_year_node = (NODE*)malloc(sizeof(NODE));
	yi_year_node->ptr_data = &yi_y, yi_year_node->next = NULL;
	yi_year_node->node_t=PLAYER_YEAR;

	int wzz_y = 1999;
	NODE* wzz_year_node = (NODE*)malloc(sizeof(NODE));
	wzz_year_node->ptr_data = &wzz_y, wzz_year_node->next = NULL;
	wzz_year_node->node_t=PLAYER_YEAR;

	int dr_y = 2008;
	NODE* dr_year_node = (NODE*)malloc(sizeof(NODE));
	dr_year_node->ptr_data = &dr_y, dr_year_node->next = NULL;
	dr_year_node->node_t=PLAYER_YEAR;

	int ra_y = 1996;
	NODE* ra_year_node = (NODE*)malloc(sizeof(NODE));
	ra_year_node->ptr_data = &ra_y, ra_year_node->next = NULL;
	ra_year_node->node_t=PLAYER_YEAR;
	/* player year initial complete. */


	enqueue(jordan_node);

	enqueue(mj_year_node);

	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();

	dequeue();
	
	enqueue(ym_name_node);
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

	enqueue(kb_name_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();
	
	enqueue(yao_node);
	dequeue();
	dequeue();
	dequeue();
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();

	dequeue();

	enqueue(mj_year_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();

	enqueue(yi_year_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();

	enqueue(book_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();

	enqueue(db_name_node);
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
	enqueue(sc_name_node);
	enqueue(sc_year_node);
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
	enqueue(yao_node);
	enqueue(ym_year_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();

	dequeue();
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();

	dequeue();
	dequeue();
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();

	enqueue(mj_year_node);
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
	enqueue(kg_name_node);
	enqueue(kg_year_node);
	enqueue(wzz_year_node);
	enqueue(yi_year_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();
	dequeue();
	dequeue();
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_queue();
	
	free(jokic), free(rodman), free(paul), free(book), free(jimmy), free(curry), free(dunken), free(camelo), free(yi), free(yao);
	
	free(kobe_node), free(jordan_node), free(yao_node), free(yi_node), free(camelo_node), free(dunken_node);
	free(curry_node), free(jimmy_node), free(book_node), free(paul_node), free(rodman_node), free(jokic_node);
	
	queue_destroy();
}
