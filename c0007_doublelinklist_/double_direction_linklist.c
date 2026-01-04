#include "double_direction_linklist.h"

NODE* head = NULL;
NODE* tail = NULL;
int size_count = 0;

void init_linklist(){
	head = (NODE*)malloc(sizeof(NODE));
	head->player_node = (PLAYER*)malloc(sizeof(PLAYER));
	head->player_node->tm = (TEAM*)malloc(sizeof(TEAM));
	head->player_node->pname = "";
	head->player_node->pnumber = 0;
	head->player_node->salary = 0;
	head->player_node->tm->tname = "";
	head->player_node->tm->city = "";
	tail = head;
	head->next = NULL;
	head->prev = NULL;
}

bool is_empty(){return false;};

bool is_node_in_list(NODE* t_node){
	NODE* targ_node = head;
	while(targ_node != NULL){
		if(!strcmp(targ_node->player_node->pname, t_node->player_node->pname)){
			return true;
		}
		if(targ_node->next != NULL){
			targ_node = targ_node->next;
		} else
			break;
	}
	return false;
}

int size_of_linklist(){
	NODE* size_node = head;
	if(head == NULL){
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

void insert_node_as_head(NODE* in_node){
	/*
	if(strlen(head->player_node->pname) == 0){
		;
	}   */
	if(!strcmp(head->player_node->pname, "")){
		head->player_node->pname = in_node->player_node->pname;
		head->player_node->pnumber = in_node->player_node->pnumber;
		head->player_node->salary = in_node->player_node->salary;
		head->player_node->tm->tname = in_node->player_node->tm->tname;
		head->player_node->tm->city = in_node->player_node->tm->city;
	} else {
		in_node->next = head;
		in_node->prev = NULL;
		head = in_node;
	}
	size_count++;
}

void insert_node_after_head(NODE* in_node){
	if(in_node == NULL){
		return;
	}
	in_node->next = head->next;
	in_node->prev = head;
	head->next = in_node;
	size_count++;
}

void insert_node_in_middle(NODE* in_node, int insert_pos){
	NODE* middle_node = head;
	NODE* found_node = NULL;
	if(in_node == NULL){
		return;
	}
	if(insert_pos > size_count){
		insert_node_after_head(in_node);
		return;
	} else if(insert_pos < 0){
		return;
	}
	while(insert_pos > 0){
		middle_node = middle_node->next;
		insert_pos--;
		if(insert_pos == 0){
			found_node = middle_node;
			break;
		}
	}
	in_node->next = found_node->next;
	in_node->prev = found_node;
	found_node->next = in_node;
	size_count++;
}

void insert_node_as_tail(NODE* in_node){
	tail = get_tail();
	if(in_node == NULL){
		return;
	}
	if(!strcmp(tail->player_node->pname, "")){
		tail->player_node->pname = in_node->player_node->pname;
		tail->player_node->pnumber = in_node->player_node->pnumber;
		tail->player_node->salary = in_node->player_node->salary;
		tail->player_node->tm->tname = in_node->player_node->tm->tname;
		tail->player_node->tm->city = in_node->player_node->tm->city;
	} else {
		tail->next = in_node;
		in_node->prev = tail;
		in_node->next = NULL;
		tail = in_node;
	}
	size_count++;
}

NODE* get_node_position(NODE* node_pos){
	static NODE* found_node = NULL;
	found_node = head;
	if(is_empty()){
		return NULL;
	}
	if(node_pos == NULL){
		return NULL;
	}
	while(node_pos != NULL){
		if(!strcmp(node_pos->player_node->pname, found_node->player_node->pname)){
			return found_node;
		}
		found_node = found_node->next;
	}
	return NULL;
}

NODE* get_previous_node(NODE* targ_node){
	static NODE* prev_node = NULL;
	prev_node = head;
	if(is_empty()){
		return NULL;
	}
	if(targ_node == NULL){
		return NULL;
	}
	while(prev_node->next != NULL){
		if(!strcmp(targ_node->player_node->pname, prev_node->next->player_node->pname)){
			return prev_node;
		}
		prev_node = prev_node->next;
	}
	return NULL;
}

NODE* get_tail(){
	static NODE* tail_node = NULL;
	tail_node = head;
	if(tail == NULL){
		printf("get error: empty list");
	}
	while(tail_node->next != NULL){
		tail_node = tail_node->next;
		if(tail_node->next == NULL){
			return tail_node;
		}
	}
	return tail_node;
}

void delete_node(NODE* out_node){
	static NODE* del_node = NULL;
	NODE* pre_node = NULL;
	del_node = out_node;
	if(out_node == NULL){
		return;
	}
	if(out_node == head){
		head = head->next;
		head->prev = NULL;
	} else if(out_node == tail){
		pre_node = get_previous_node(out_node);
		tail->prev = NULL;
		pre_node->next = NULL;
		tail = pre_node;
	} else if(is_node_in_list(del_node)){
		pre_node = get_previous_node(del_node);
		pre_node->next->next->prev = pre_node;
		pre_node->next = pre_node->next->next;
	} else {
		printf("delete error: the node plan to delete not exist in the list.\n");
		return;
	}
}

bool search_node(NODE* s_node){
	NODE* sear_node = head;
	if(s_node == NULL){
		return false;
	}
	while(s_node != NULL){
		if(!strcmp(s_node->player_node->pname, sear_node->player_node->pname)){
			return true;
		}
	}
	return false;
	printf("Node not found in the link list.\n");
}

void print_linklist(NODE* p_node){
	if(p_node == NULL){
		return;
	}
	if(!is_node_in_list(p_node)){
		printf("print error: node not in list.\n");
		return;
	}
	while(p_node != NULL){
		printf("Name  : %20s\n", p_node->player_node->pname);
		printf("Number: %20d\n", p_node->player_node->pnumber);
		printf("Salary: %20d\n", p_node->player_node->salary);
		printf("Team  : %20s\n", p_node->player_node->tm->tname);
		printf("City  : %20s\n", p_node->player_node->tm->city);
		printf("****************************************************\n");
		if(p_node->next == NULL){
			return;
		} else
			p_node = p_node->next;
	}
}
