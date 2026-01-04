CC=cc
CFLAGS=-Wall -g
#LDFLAGS=

double_direction_linklist.o: double_direction_linklist.c
	$(CC) $(CFLAGS) -c $< -o $@

test_dd_linklist.o: test_dd_linklist.c
	$(CC) $(CFLAGS) -c $< -o $@

test_dd_linklist: double_direction_linklist.o test_dd_linklist.o
	$(CC) $^ -o $@

.PHONY: clean
clean:
	rm -f *.o *.gch
