CC := gcc

ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

INC_DIR := $(ROOT_DIR)/inc
SRC_DIR := $(ROOT_DIR)/src
OBJ_DIR := $(ROOT_DIR)/obj

SRC_EXCLUDE :=

CFLAGS := -fpic -Wall -Werror -I$(INC_DIR)
LDFLAGS := -shared

SRCS := $(filter-out $(SRC_EXCLUDE), $(wildcard $(SRC_DIR)/*.c))
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS)) 
TARGET := libarg.so

all: build clean
build: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $^

objects: $(OBJS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJ_DIR):
	mkdir $@

clean:
	rm -rf $(OBJ_DIR)

remove: clean
	rm -f $(TARGET)

.PHONY: all

install: 
	mkdir -p /usr/include/arg_parse
	cp $(INC_DIR)/* /usr/include/arg_parse
	cp $(TARGET) /usr/lib/$(TARGET)
