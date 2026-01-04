CC=cc
CFLAGS=-Wall -g
#LDFLAGS=

linklist.o: linklist.c
	$(CC) $(CFLAGS) -c $< -o $@

test_linklist.o: test_linklist.c
	$(CC) $(CFLAGS) -c $< -o $@
	
#linklist: linklist.o
	#$(CC) -o $@ $^

test_linklist: linklist.o test_linklist.o
	$(CC) $^ -o $@

#linklist: linklist.o
	#$(CC) -o linklist linklist.o

.PHONY: clean
clean:
	rm -f *.o *.gch


#使用如下两个命令编译也可以做到生成可执行的test_linklist程序的效果
#cc -wall -g -c linklist.c -o linklist.o 
#cc -wall test_linklist.c linklist.o -o test_linklist