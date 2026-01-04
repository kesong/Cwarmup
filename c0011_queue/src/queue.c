#include "queue.h"

NODE* head = NULL;
NODE* tail = NULL;
int size_count = 0;

void init_queue(){
	head = (NODE*)malloc(sizeof(NODE));
	tail = head;
	head->next = NULL;
}

bool is_empty(){
	if(head == NULL){
		return true;
	}
	if(head->ptr_data == NULL && tail->ptr_data == NULL){
		printf("queue is empty.\n");
		return true;
	}
	return false;
}

int size_of_queue(){
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

void enqueue(NODE* in_node){
	if(in_node == NULL){
		return;
	}
	if(is_empty()){
		head = in_node;
		head->next = NULL;
		tail = head;
		size_count++;
		return;
	}
	tail->next = in_node;
	tail = in_node;
	tail->next = NULL;
	size_count++;
}

void dequeue(){
	if(is_empty()){
		return;
	}
	if(head->next != NULL){
		head = head->next;
		//size_count--;
	} else {
		head = NULL;
		tail = NULL;
	}
}

void queue_destroy(){
	if(is_empty()){
		printf("queue is empty, nothing need dequeue.\n");
		return NULL;
	}
	if(head != NULL){
		while(head->ptr_data != NULL){
			dequeue();
			if(head == NULL){
				return;
			}
		}
		free(head);
	}
}

