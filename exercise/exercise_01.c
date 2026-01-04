#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void fun(char** p){
	*p = (char*)malloc(100);
}

int main(){
	char* p = NULL;
	fun(&p);
	free(p);
	if(p != NULL){
		strcpy(p, "hello world.");
		printf(p);
		printf("\n");
	}
}
