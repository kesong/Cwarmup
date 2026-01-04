#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define LENGTH 10

typedef int bool_t;

int queue_size(int*);
int* enq_position();
bool_t is_queue_full();
bool_t is_queue_empty();
void move_element_after_enqueue();
void move_element_after_dequeue(int);
void remove_zero_from_queue();

int que_arr[LENGTH] = {};
//int* ptr_start = NULL;
//int* ptr_end = NULL;
int* ptr_enq = NULL;
int* ptr_deq = NULL;
int* ptr_current = NULL;

int* enqueue(int ptrdata){
	int* ptr_in = ptr_enq;
	if(is_queue_full()){
		printf("queue full, %d enqueue failed.\n", ptrdata);
		return NULL;
	}
	if(!(*ptr_in) && !(*(ptr_in+1))){
            *ptr_in = ptrdata;
	    ptr_current = ptr_in;
	    printf("%d enqueue successful.\n", *ptr_in);
	    move_element_after_enqueue();
	    *ptr_in = 0;
            return ptr_current;
        }
	*ptr_in = ptrdata;
	ptr_current = ptr_in;
	printf("the last element %d enqueued. \n", *ptr_in);
	return ptr_current;
	
}

int* dequeue(int remove_count){
	int* ptr_out = ptr_deq;
	int* ptr_move = NULL;
	int* ptr_front = NULL;
	int remove_count_bak = remove_count;
	if(is_queue_empty()){
        	printf("dequeue failed, queue empty.\n");
		return NULL;
    	}
	if(remove_count <= 0){
		printf("the parameter to the funciton should greater than 0.\n");
		return NULL;
	}
	if(remove_count >= LENGTH){
		printf("the parameter must not greater than the queue length.\n");
		return NULL;
	}
	if(*ptr_out){
		while(remove_count > 0){
			if(ptr_out >= ptr_enq){
				printf("%d dequeued.\n", *ptr_out);
				*ptr_out = 0;
				ptr_out--;
				remove_count--;
			}
			if(ptr_out < ptr_enq){
				ptr_out = ptr_enq;
			}
			if(ptr_out == ptr_enq){
				*ptr_out = 0;;
				break;
			}
			if(*ptr_out == 0){
				break;
			}
		}
	}
	move_element_after_dequeue(remove_count_bak);
	ptr_current = ptr_out;
	//remove_zero_from_queue();
	return ptr_current;
}

bool_t is_queue_full(){
	int* ptr_full = ptr_enq;
	while(*ptr_full){
		if(ptr_full == ptr_deq){
	  		printf("is_queue_full: true, queue is full.\n");
	        	return 1;
		}
		ptr_full++;
	}
	return 0;
}

bool_t is_queue_empty(){
	int* ptr_empty = ptr_deq;
	while(!(*ptr_empty)){
		if(ptr_empty == ptr_enq){
			printf("is_queue_empty: true, queue is empty.\n");
			return 1;
		}
		ptr_empty--;
	}
	return 0;
}

int* enq_position(){
	int* ptr_cur = ptr_enq;
	if(is_queue_empty()){
		return NULL;
	}
	if(is_queue_full()){
		return NULL;
	}
    	while(!(*ptr_cur)){
		ptr_cur++;
		if(*ptr_cur){
			break;
		}
    	}
	ptr_current = ptr_cur;
	return ptr_current;
}

int* deq_position(){
	int* ptr_cur = ptr_deq;
	if(is_queue_full()){
		return NULL;
	}
	if(is_queue_empty()){
		return NULL;
	}
	while(*ptr_cur){
		ptr_cur--;
		if(!(*ptr_cur)){
			ptr_current = ptr_cur;
			break;
		}
	}
	return ptr_current;
}

int* deq_target_addr(){
	int* ptr_target = ptr_deq;
	if(is_queue_full()){
		return NULL;
	}
	if(!(*ptr_target)){
		return NULL;
	}
	while(*ptr_target){
		if(!(*ptr_target)){
			break;
		}
		ptr_target--;
	}
	ptr_current = ptr_target;
	return ptr_current;
}

void move_element_after_enqueue(){
	int* move_start = enq_position();
	int* move_end = deq_position();
	int move_count = 0;
	int move_sum = 0;
	if(move_start != NULL && move_end != NULL){
		if(move_start > ptr_deq || move_start < ptr_enq){
			printf("move error: get a wrong start address.\n");
			return;
		}
		if(move_end > ptr_deq || move_end < ptr_enq){
			printf("move error: get a wrong end address.\n");
			return;
		}
	}
	if(move_end == ptr_enq){
		*ptr_deq = *move_start;
	} else
		*move_end = *move_start;
}

void move_element_after_dequeue(int move_count){
	int* ptr_move = ptr_deq;
	while(ptr_move >= ptr_enq + move_count){
		*ptr_move = *(ptr_move - move_count);
		ptr_move--;
	}
	while(ptr_move > ptr_enq){
		*ptr_move = 0;
		ptr_move--;
		if(ptr_move == ptr_enq){
			*ptr_move = 0;
			return;
		}
	}
}

void move_one_element_once(){
	int* ptr_move_one = ptr_deq;
	while(ptr_move_one > ptr_enq){
		*ptr_move_one = *(ptr_move_one--);
		if(ptr_move_one == ptr_enq){
			*ptr_move_one = 0;
			return;
		}
	}
}

int* init_queue(){
    for(int i = 0; i < LENGTH; i++){
        que_arr[i] = 0;
    }
    ptr_enq = &que_arr[0];
    ptr_deq = &que_arr[LENGTH - 1];
    return ptr_enq;
}

void print_queue(){
	int deq_count = 0;
	int* ptr_outofq = ptr_deq;
	printf("queue print as: ");
    	while(ptr_outofq >= ptr_enq){
		if(ptr_outofq == ptr_enq){
			printf("%d.\n", *ptr_outofq);
			ptr_current = ptr_enq;
			break;
		}
		printf("%d, ", *ptr_outofq);
		ptr_outofq--;
    	}
}

void full_fill_queue(){
	int iInput_num = 0;
    	int* ptr_fill = NULL;
	while(!(*ptr_enq)){
        	printf("Please input integer number: ");
        	scanf("%d", &iInput_num); 
        	ptr_fill = enqueue(iInput_num);
		if(ptr_fill == NULL){
			printf("queue filled complete.\n");
			break;
		}
    }
}

int main(int argc, char** argv){
    	init_queue();
	assert(is_queue_empty() == 1);
    	print_queue();
	
	full_fill_queue();
	assert(is_queue_full() == 1);
	enqueue(250);
	enqueue(500);
	
	//int* get_pos = enq_position();
	//assert(get_pos == ptr_end);
	//printf("queue start address is %p, deq point address is %p, queue end adress is %p.\n", ptr_start, ptr_deq, ptr_end);
	
	//int fulled = is_queue_full();
	//int emptyed = is_queue_empty();
	//assert(fulled == 1);
	//assert(emptyed == 0);
	
	dequeue(2);
	print_queue();
	//fulled = is_queue_full();
	//assert(fulled == 0);
	
	//get_pos = enq_position();
	//printf("queue start address is %p, deq point address is %p, queue end adress is %p.\n", ptr_start, ptr_deq, ptr_end);
	//assert(get_pos < ptr_end);
	//assert(get_pos > ptr_start);
	
	enqueue(300);
	print_queue();
	//fulled = is_queue_full();
	//assert(fulled == 1);
	dequeue(4);
	print_queue();
	enqueue(400);
	dequeue(5);
    	print_queue();
}
