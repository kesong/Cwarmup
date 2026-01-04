CC=cc
CFLAGS=-Wall -g -I $(INCLUDE_DIR)

#SRC=$(wildcard $(TEST_DIR)/*.c)
OBJ=$(BIN_DIR)/test_player.o

$(BIN_DIR)/test_queue.o: test_queue.c $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(BIN_DIR)/test_player.o: test_player.c
	$(CC) $(CFLAGS) -c $^ -o $@
	
#$(BIN_DIR)/test_player_name.o: test_player_name.c
	#$(CC) $(CFLAGS) -c $^ -o $@
