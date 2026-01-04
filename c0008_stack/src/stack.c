#include "../include/stack.h"

NODE* top = NULL;
NODE* bottom = NULL;
int size_count = 0;

void init_stack(){
	top = (NODE*)malloc(sizeof(NODE));
	top->player_node = (PLAYER*)malloc(sizeof(PLAYER));
	top->player_node->tm = (TEAM*)malloc(sizeof(TEAM));
	top->player_node->pname = "";
	top->player_node->pnumber = 0;
	top->player_node->salary = 0;
	top->player_node->tm->tname = "";
	top->player_node->tm->city = "";
	bottom = top;
	top->next = NULL;
}

bool is_empty(){
	if(top == NULL || (int)strcmp(top->player_node->pname, "") == 0){
		printf("stack is empty.\n");
		return true;
	}
	return false;
}

int size_of_linklist(){
	NODE* size_node = top;
	if(top == NULL){
		return 0;
	}
	while(size_node != NULL){
		size_count++;
		if(size_node->next == NULL){
			return size_count;
		}
		size_node = size_node->next;
	}
	return 0;
}

void push(NODE* in_node){
	NODE* top_temp = top;
	if(in_node == NULL){
		return;
	}
	if(top == NULL || (int)strcmp(top->player_node->pname, "") == 0){
		top = in_node;
		top->next = NULL;
		return;
	}
	in_node->next = top;
	top = in_node;
}

void pop(){
	if(is_empty()){
		return;
	}
	top = top->next;
}

void stack_destroy(){
	if(is_empty()){
		printf("stack is empty, nothing need pop.\n");
		return NULL;
	}
	while(top != NULL){
		pop();
	}
}

void print_stack(){
	NODE* print_node = top;
	if(is_empty()){
		printf("NONE: empty stack!\n");
		return;
	}
	while(print_node != NULL){
		printf("Name  : %20s\n", print_node->player_node->pname);
		printf("Number: %20d\n", print_node->player_node->pnumber);
		printf("Salary: %20d\n", print_node->player_node->salary);
		printf("Team  : %20s\n", print_node->player_node->tm->tname);
		printf("City  : %20s\n", print_node->player_node->tm->city);
		printf("****************************************************\n");
		print_node = print_node->next;
		if(print_node == NULL){
			return;
		}
	}
}
