#include "test_player_name.h"

void init_player_name_queue(){
	head = (NODE*)malloc(sizeof(NODE));
	head->ptr_data = NULL;
	head->next = NULL;
	tail = head;
}

void print_player_name_queue(){
	NODE* print_node = head;
	char* player_name = NULL;
	if(is_empty()){
		printf("NONE: empty queue!\n");
		return;
	}
	while(print_node->ptr_data != NULL){
		player_name = (char*)(print_node->ptr_data);
		printf("Name  : %-20s\n", player_name);
		printf("****************************************************\n");
		print_node = print_node->next;
		if(print_node == NULL){
			return;
		}
	}
}

void test_player_name_queue(){
	init_player_name_queue();
	print_player_name_queue();

	/*
	char* michael = "Michael Jordan";
	char* kobe = "Kobe Bryant";
	char* tim = "Tim Dunkan";
	char* curry = "Stephen Curry";
	char* jams = "Lebron James";
	char* kevin = "Kevin Garnet";
	char* book = "Devin Book";
	char* paul = "Chris Paul";
	char* yao = "Yao Ming";
	char* yi = "Yi Jianlian";
	char* wang = "Wang Zhizhi";
	char* rose = "Derick Rose";
	char* ray = "Ray Allen";
	*/

	int print_count = 0;
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
    	print_player_name_queue();

	/* player name. */
	char* michael = "Michael Jordan";
	NODE* mj_node = (NODE*)malloc(sizeof(NODE));
	mj_node->ptr_data = michael, mj_node->next = NULL;

	char* kobe = "Kobe Bryant";
	NODE* kb_node = (NODE*)malloc(sizeof(NODE));
	kb_node->ptr_data = kobe, kb_node->next = NULL;

	char* tim = "Tim Dunkan";
	NODE* td_node = (NODE*)malloc(sizeof(NODE));
	td_node->ptr_data = tim, td_node->next = NULL;

	char* curry = "Stephen Curry";
	NODE* sc_node = (NODE*)malloc(sizeof(NODE));
	sc_node->ptr_data = curry, sc_node->next = NULL;

	char* james = "Lebron James";
	NODE* lj_node = (NODE*)malloc(sizeof(NODE));
	lj_node->ptr_data = james, lj_node->next = NULL;

	char* kevin = "Kevin Garnet";
	NODE* kg_node = (NODE*)malloc(sizeof(NODE));
	kg_node->ptr_data = kevin, kg_node->next = NULL;

	char* book = "Devin Book";
	NODE* db_node = (NODE*)malloc(sizeof(NODE));
	db_node->ptr_data = book, db_node->next = NULL;

	char* paul = "Chris Paul";
	NODE* cp_node = (NODE*)malloc(sizeof(NODE));
	cp_node->ptr_data = paul, cp_node->next = NULL;

	char* yao = "Yao Ming";
	NODE* ym_node = (NODE*)malloc(sizeof(NODE));
	ym_node->ptr_data = yao, ym_node->next = NULL;

	char* yi = "Yi Jianlian";
	NODE* yi_node = (NODE*)malloc(sizeof(NODE));
	yi_node->ptr_data = yi, yi_node->next = NULL;

	char* wang = "Wang Zhizhi";
	NODE* wzz_node = (NODE*)malloc(sizeof(NODE));
	wzz_node->ptr_data = wang, wzz_node->next = NULL;

	char* rose = "Derick Rose";
	NODE* dr_node = (NODE*)malloc(sizeof(NODE));
	dr_node->ptr_data = rose, dr_node->next = NULL;

	char* ray = "Ray Allen";
	NODE* ra_node = (NODE*)malloc(sizeof(NODE));
	ra_node->ptr_data = ray, ra_node->next = NULL;
	/* player name initial complete. */

	enqueue(mj_node);
	enqueue(ym_node);
	enqueue(yi_node);
	enqueue(td_node);

	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_name_queue();

	dequeue();
	enqueue(cp_node);

	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_name_queue();
	dequeue();
	dequeue();
	dequeue();
	enqueue(ra_node);
	enqueue(dr_node);
	dequeue();
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_name_queue();

	enqueue(lj_node);
	enqueue(mj_node);
	enqueue(sc_node);
	enqueue(ym_node);
	dequeue();
	dequeue();
	dequeue();
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_name_queue();

	dequeue();
	dequeue();
	dequeue();
	enqueue(db_node);
	enqueue(kg_node);
	enqueue(mj_node);
	enqueue(ym_node);
	enqueue(sc_node);
	enqueue(sc_node);
	dequeue();
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_name_queue();

	dequeue();
	dequeue();
	dequeue();
	enqueue(kg_node);
	enqueue(lj_node);
	enqueue(td_node);
	enqueue(db_node);
	printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n", print_count++);
	print_player_name_queue();

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
	print_player_name_queue();
}
