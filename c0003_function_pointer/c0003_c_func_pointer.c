#include <stdio.h>
#include <stdlib.h>

struct shape{
	char* name;
	float area;
	float volume;
};

typedef struct shape SHAPE;
typedef void (*shape_poly)(SHAPE, float, ...);

void print_shape(SHAPE spe){
	printf("Shape name is %s, ", spe.name);
	printf("Area is %0.2f, ", spe.area);
	printf("Volume is %0.2f.\n", spe.volume);
}

void circle_feature(SHAPE cir_st, float radius){
	float pi = 3.14;
	cir_st.area = pi * radius * radius;
	cir_st.volume = pi * radius * radius * radius;
	print_shape(cir_st);
}

/*
void square_feature(SHAPE sqa_st, float side){
	sqa_st.area = side * side;
	sqa_st.volume = side * side * side;
	print_shape(sqa_st);
}

void rec_feature(SHAPE rec_st, float length, float width, float height){
	rec_st.area = length * width;
	rec_st.volume = length * width * height;
	print_shape(rec_st);
}
*/
int main(){
	SHAPE circle = {.name = "Circle", .area = 0.0, .volume = 0.0};
	SHAPE square = {.name = "Square", .area = 0.0, .volume = 0.0};
	SHAPE rectangular = {.name = "Rectangular", .area = 0.0, .volume = 0.0};
	
	shape_poly cir_shape = circle_feature;
	cir_shape(circle, 2.5);
	
	/*
	shape_poly squa_shape = square_feature;
	(*squa_shape)(square, 8.0);

	shape_poly rec_shape = rec_feature;
	(*rec_shape)(rectangular, 3.0, 4.0, 5.0); */
}
