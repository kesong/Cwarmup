#include <stdlib.h>
#include <stdio.h>
#include <time.h>

char* time_format_string(){
	time_t timep;
	time(&timep);
	struct tm* local_time = localtime(&timep);
	int year = 1900 + local_time->tm_year;
	int month = 1 + local_time->tm_mon;
	int day = local_time->tm_mday;
	char *format_str="";
	if(asprintf(&format_str, "%d-%02d-%02d %02d:%02d:%02d", year, month, day, local_time->tm_hour, local_time->tm_min, local_time->tm_sec) < 1){
		return NULL;
	}
	return format_str;
}

int main(){
	printf("%ld seconds from 1970/1/1. \n", time((time_t*)NULL));
	time_t timep;
	time(&timep);
	//struct tm* current_time = gmtime(&timep);
	struct tm* local_time = localtime(&timep);
	//printf("current time: %d-%d-%d--%d:%d:%d \n", current_time->tm_year, current_time->tm_mon, current_time->tm_mday, current_time->tm_hour, current_time->tm_min, current_time->tm_sec);
	int year = 1900 + local_time->tm_year;
	int month = 1 + local_time->tm_mon;
	int day = local_time->tm_mday;
	printf("local time: %d-%d-%d %02d:%02d:%02d \n", year, month, day, local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
	printf("%s ########## \n", time_format_string());
	printf("%s call time format funciton. \n", time_format_string());
}
