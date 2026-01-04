CC=cc
CFLAGS=-Wall -g -I $(INCLUDE_DIR)
#LDFLAGS=
VPATH=src include test

TOPDIR		:= $(PWD)
SRC_DIR		:= $(TOPDIR)/src
BIN_DIR		:= $(TOPDIR)/bin
INCLUDE_DIR	:= $(TOPDIR)/include
TEST_DIR	:= $(TOPDIR)/test
SUBDIR		:= src test

export TOPDIR SRC_DIR BIN_DIR INCLUDE_DIR TEST_DIR

SRCS=$(wildcard $(SRC_DIR)/*.c) $(wildcard $(TEST_DIR)/*.c)
OBJS=$(patsubst %.c, $(BIN_DIR)/%.o, $(notdir $(wildcard $(SRCS))))
TARGETS=$(BIN_DIR)/$(basename $(notdir $(wildcard $(TEST_DIR)/*.c)))

all: $(SUBDIR) $(TARGETS)
$(SUBDIR): RUN
	make -C $@
RUN:

$(TARGETS): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@


.PHONY: clean
clean:
	rm -rf *.o *.gch
	$(shell if [ -e $(BIN_DIR) ]; then rm -rf $(BIN_DIR); fi)
	
