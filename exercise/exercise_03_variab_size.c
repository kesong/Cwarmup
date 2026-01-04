#include <stdio.h>
#include <stdlib.h> 

#define print(x, y) printf("%17s size is:  %2d Bytes.\n", x, sizeof(y))
#define compare(m, n) (m == n) ? "Yes" : "No"
#define print_compare(x, y) printf("%30s result is: %-s.\n", (x), (y))

typedef struct song SONG;

struct song{
	char c;
	short s;
	int i;
	char* ptr_c;
	long l;
	double d;
};

int main(){
	char c_type = 'k';
	int integer_type = 10;
	char* ptr_char = "kesong";
	int* ptr_int = NULL;
	short short_type = 10;
	short int s_integer = 10;          //same as short.
	unsigned short uns_s = 10;
	signed short s_short = 10;
	unsigned uns = 10;
	unsigned int uns_int = 10;
	signed sign = 10;
	signed int sign_int = 10;
	long signed long_sign = 10;
	long signed int long_sign_int = 10;
	long long_type = 10;
	long int long_int = 10;            //same as long.
	long long long_long = 10.0;
	float float_type = 10.0;
	//long float long_float = 10.0;      //it's invlid type, long and float not allowed to combind use like this.
	double double_type = 10.0;
	long double long_double = 10.0;
	//double double long_double = 10.0;   //invalid type, 2 double not allowed combination.

	SONG song_st;
	
	print("char", c_type);
	print("int", integer_type);
	print("char*", ptr_char);
	print("int*", ptr_int);
	print("short", short_type);
	print("short int", s_integer);
	print("unsigned short", uns_s);
	print("signed short", s_short);
	print("unsigned", uns);
	print("unsigned int", uns_int);            // same as unsigned.
	print("signed", sign);
	print("signed int", sign_int);
	print("long signed", long_sign);
	print("long signed int", long_sign_int);   // same as long signed.
	print("long", long_type);
	print("long int", long_int);
	print("long long", long_long);
	print("float", float_type);
	//print("long float", long_float);          // not allowed.
	print("double", double_type);
	print("long double", long_double);
	//print("double double", double_double);    // not allowed.

	print("struct SONG", SONG);
	print("struct char", song_st.c);
	print("struct short", song_st.s);
	print("struct int", song_st.i);
	print("struct char*", song_st.ptr_c);
	print("struct long", song_st.l);
	print("struct double", song_st.d);
	
	//print_compare("short = short int?", compare(short_type, s_integer));
	//print_compare("signed = unsigned?", compare(sign, uns));
	//print_compare("unsigned = unsigned int?", compare(uns, uns_int));
	//print_compare("long = long int?", compare(long_type, long_int));
	//print_compare("signed = signed int?", compare(sign, sign_int));
	//print_compare("long signed = long signed int?", compare(long_sign, long_sign_int));
}
