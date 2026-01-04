#include <stdio.h> 

typedef struct{ 
	char* job; 
	int age; 
} Person; 

void give_bob_a_job(Person*); 

int main(){ 
	Person bob; 
	give_bob_a_job(&bob); 
	printf("The job of bob is %s\n", bob.job); 
	return 0; 
} 

void give_bob_a_job(Person *bob){
	*bob.job = "Sysadmin"; (compile error)
	//bob->job="Sysadmin";  (correct)
	//(*bob).job = "Sysadmin"; (correc)
}