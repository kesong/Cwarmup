#include <stdio.h>

int main(int argc, char* argv){

	int lichee = 22;
	int pineapple = 23;
	int cherry = 24;

	const int* con_value_ptr = &lichee;
	int* const con_addr_ptr = &pineapple;
	int const *con_ptr = &cherry;

	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	printf("con_value_ptr value is: %d, address is %p.\n", *con_value_ptr, con_value_ptr);
	printf("con_addr_ptr value is: %d, address is %p.\n", *con_addr_ptr, con_addr_ptr);
	printf("con_ptr value is: %d, address is %p.\n", *con_ptr, con_ptr);

	//error: assignment of read-only location ‘*con_value_ptr’
	*con_value_ptr = 220;              //指针指向的值不可以改变，指针的地址可以改变

	*con_addr_ptr = 230;              //指针指向的值可以改变，指针的地址不可以改变
	
	//error: assignment of read-only location ‘*con_ptr’
	*con_ptr = 240;                   //同第一个表达式

	printf("**********************************************************\n");
	printf("con_value_ptr value is: %d, address is %p.\n", *con_value_ptr, con_value_ptr);
	printf("con_addr_ptr value is: %d, address is %p.\n", *con_addr_ptr, con_addr_ptr);
	printf("con_ptr value is: %d, address is %p.\n", *con_ptr, con_ptr);

	int plum = 2200;
	int cherimoya = 2300;
	int longan = 2400;

	con_value_ptr = &plum;
	
	//error: assignment of read-only variable ‘con_addr_ptr’
	con_addr_ptr = &cherimoya;                //地址不可以改变
	
	con_ptr = &longan;

	printf("##########################################################\n");
	printf("con_value_ptr value is: %d, address is %p.\n", *con_value_ptr, con_value_ptr);
	printf("con_addr_ptr value is: %d, address is %p.\n", *con_addr_ptr, con_addr_ptr);
	printf("con_ptr value is: %d, address is %p.\n", *con_ptr, con_ptr);
}
