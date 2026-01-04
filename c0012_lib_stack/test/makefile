CC							=	cc
CFLAGS					=	-Wall -g -I$(INCLUDE_DIR)

SRCS						=	$(wildcard *.c)
#OBJS						=	$(patsubst %.c,$(BIN_DIR)/%.o,$(notdir $(wildcard $(SRCS))))
#OBJS						=	$(patsubst %.c,%.o,$(notdir $(wildcard $(SRCS))))
OBJS						=	$(SRCS:%.c=%.o)

#$(info $(SRCS))
#$(info $(OBJS))
all: $(OBJS)

%.o: %.c 
	$(CC) $(CFLAGS) -c $^ $@

#$(OBJS): $(SRCS)
	#$(CC) -c $(CFLAGS) $^ $@

# execute the following command in the directory test, the .o file will gernerated
# cc -c -I..include *.o *.c
