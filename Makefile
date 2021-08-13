CC := gcc

ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

INC_DIR := $(ROOT_DIR)/inc
SRC_DIR := $(ROOT_DIR)/src
OBJ_DIR := $(ROOT_DIR)/obj

SRC_EXCLUDE :=

CFLAGS := -Wall -Werror -I$(INC_DIR)
LDFLAGS := 

SRCS := $(filter-out $(SRC_EXCLUDE), $(wildcard $(SRC_DIR)/*.c))
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS)) 
TARGET :=  

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