#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define LENGTH 10

typedef int bool_t;

int stack_size(int*);
int s_arr[LENGTH] = {};
int* ptr_start = NULL;
int* ptr_end = NULL;
int* ptr_current = NULL;

int* push(int ptrdata){
    if(ptr_current < ptr_start){
        ptr_current = ptr_start;
    }
    if(ptr_current > ptr_end){
        ptr_current = ptr_end;
    }
    if(ptr_current == ptr_end){
        if(*ptr_current){
            printf("stack fulled, %d push to stack not allowed.\n", ptrdata);
            return ptr_current;
        }
        *ptr_current = ptrdata;
        printf("push the last item %d to the stack.\n", *ptr_current);
        ptr_current += 1; 
        return ptr_current;
    }
    if(*ptr_current){
        ptr_current++;
    }
    *ptr_current = ptrdata;
    printf("%d pushed to stack successful.\n", *ptr_current);
    ptr_current += 1; 
    return ptr_current;
}

int* pop(){
    if(ptr_current > ptr_end){
        ptr_current = ptr_end;
    }
    if(ptr_current < ptr_start){
        ptr_current = ptr_start;
    }
    if(ptr_current == ptr_start){
        if(!(*ptr_current)){
            printf("pop: failed, point the start, nothing pop.\n");
            return ptr_current;
        }
        printf("pop the last item in the stack: %d\n", *ptr_current);
		*ptr_current = 0;
		ptr_current -= 1;
        return ptr_current;
    }
    if(!(*ptr_current)){
        ptr_current--;
    }
    printf("%d poped from the stack.\n", *ptr_current);
	*ptr_current = 0;
    ptr_current -= 1;
    
    return ptr_current;
}

bool_t is_stack_full(){
	int* ptr_full = NULL;
	ptr_full = ptr_start;
	if(ptr_current > ptr_end){
		ptr_current = ptr_end;
		if(*ptr_current){
			printf("is_stack_full: true, stack is full.\n");
			return 1;
		} else
			return 0;
	}
	if(ptr_current < ptr_start){
		ptr_current = ptr_start;
		if(!(*ptr_current)){
			printf("is_stack_full: false, stack is empty.\n");
			return 0;
		}
	}
	//下面的判断是否可以不需要了，上面对指针当前指向的内容已经做了判断了；
	while(ptr_full <= ptr_end && ptr_full >= ptr_start){
		if(*ptr_full && ptr_full == ptr_end){
			printf("is_stack_full: true, stack is full.\n");
			return 1;
		}
		ptr_full++;
	}
	return 0;
}

bool_t is_stack_empty(){
	int* ptr_empty = NULL;
	ptr_empty = ptr_start;
	if(ptr_current > ptr_end){
		ptr_current = ptr_end;
		if(*ptr_current){
			printf("is_stack_empty: false, stack is full.\n");
			return 0;
		}
	}
	if(ptr_current < ptr_start){
		ptr_current = ptr_start;
		if(!(*ptr_current)){
			printf("is_stack_empty: true, stack is empty.\n");
			return 1;
		}
	}
	while(ptr_empty <= ptr_end && ptr_empty >= ptr_start){
		if(!(*ptr_empty) && ptr_empty == ptr_start){
			printf("is_stack_empty: true, stack is empty.\n");
			return 1;
		}
		ptr_empty++;
	}
	return 0;
}

int* top(){
	int* ptr_top = NULL;
	if(is_stack_full()){
		ptr_current = ptr_end;
	}
	if(is_stack_empty()){
		ptr_current = ptr_start;
	}
    while(ptr_top <= ptr_end && ptr_top >= ptr_start){
        if(!(*ptr_top)){
			ptr_current = ptr_top;
			return ptr_current;
		}
        ptr_top++;
    }
    return ptr_current;
}

int* init_stack(){
    for(int i = 0; i < LENGTH; i++){
        s_arr[i] = 0;
    }
    ptr_start = &s_arr[0];
    ptr_end = &s_arr[LENGTH - 1];
    ptr_current = ptr_start;
    return ptr_current;
}

void print_stack(){
    int* ptr_current_backup = ptr_current;
    printf("before print stack, ptr_current address is %p.\n", ptr_current);
    int pop_count = 0;
    int* ptr_pop = NULL;
    while(ptr_current <= ptr_end && ptr_current >= ptr_start){
        if(ptr_current == ptr_start && !(*ptr_current)){
            printf("empty stack, nothing pop.\n");
            break;
        }
        ptr_pop = pop();
        if(ptr_pop == NULL){
            break;
        }
        printf("item %d poped.\n", pop_count);
        if(++pop_count >= LENGTH){
            ptr_current = ptr_end;
            printf("stack poped %d items, pop end.\n", pop_count);
            break;
        }
    }
    printf("after print stack, ptr_current address is %p.\n", ptr_current);
    ptr_current = ptr_current_backup;
}

void full_push_stack(){
	int iInput_num = 0;
    int* ptr_push = NULL;
	for(int i = 0; i < LENGTH; i++){
        printf("Please input integer number: ");
        scanf("%d", &iInput_num); 
        ptr_push = push(iInput_num);
        if(ptr_push == NULL){
            printf("push stack end.\n");
            ptr_current = ptr_end;
            break;
        }
        if(ptr_current > ptr_end){
            ptr_current = ptr_end;
            printf("stack fulled.\n");
            break;
        }
    }
}

int main(int argc, char** argv){
    init_stack();
    print_stack();
	
	full_push_stack();
	push(250);
	push (500);
	
	int* get_top = top();
	assert(get_top == ptr_end);
	printf("stack start address is %p, stack point address is %p, stack end address is %p.\n", ptr_start, ptr_current, ptr_end);
	
	int fulled = is_stack_full();
	int emptyed = is_stack_empty();
	assert(fulled == 1);
	assert(emptyed == 0);
	
	pop();
	fulled = is_stack_full();
	assert(fulled == 0);
	
	get_top = top();
	printf("stack start address is %p, stack point address is %p, stack end address is %p.\n", ptr_start, ptr_current, ptr_end);
	assert(get_top < ptr_end);
	assert(get_top > ptr_start);
	
	push(300);
	fulled = is_stack_full();
	assert(fulled == 1);
	pop();
	push(400);
	pop();
    print_stack();
}