CC=cc
CFLAGS=-Wall -g -I $(INCLUDE_DIR)

#SRC=$(wildcard $(TEST_DIR)/*.c)

$(BIN_DIR)/test_queue.o: test_queue.c $(BIN_DIR)/test_player.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(BIN_DIR)/test_player.o: test_player.c
	$(CC) $(CFLAGS) -c $^ -o $@
