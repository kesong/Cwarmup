#include <stdio.h>

#define eprintf_1(...) fprintf(stderr, __VA_ARGS__)

#define eprintf_2(format, ...) fprintf(stderr, format,  __VA_ARGS__)

#define eprintf_3(format, ...) fprintf(stderr, format, ##__VA_ARGS__)

int main(){
	eprintf_1("song, you shoud work harder than past.");

	char *str = "Dragon Boat Festival";
	int year = 2025;
	eprintf_2("Happy %s, %d!\n", str, year);

	eprintf_3("Happy %s, %d!\n", str, year);

	//compile error, it will expanded like: fprintf(stderr, "variadic parameter is empty.\n", ), there is a comma at the end,
	eprintf_2("variadic parameter is empty.\n");

	//expanded as: fprintf(stderr, "variadic parameter is empty.\n"), no comma at the end. it's the ## make sense.
	eprintf_3("variadic parameter is empty.\n");
}

