#include "queue.h"
#include "test_player.h"
#include "test_player_name.h"

int main(int argc, char** argv){
	init_queue();
	init_player_queue();
	
	test_player_queue();

	test_player_name_queue();

}
