.PHONY:clean  all 
CC=gcc
CFLAGS=-w -g

DIR=./
PATH_OUT = $(DIR)/debug
PATH_INCLUDE = $(DIR)/include
PATH_SRC = $(DIR)/src

BIN=client socketwatchser lookoutServerPS 
DEPEND=client.c socketWatchServer.c lookoutServerPS.c
all:$(BIN) 

client:$(PATH_SRC)/client.c 
	$(CC) $(CFLAGS) -o $(PATH_OUT)/client $(PATH_SRC)/client.c -I $(PATH_INCLUDE)
socketwatchser:$(PATH_SRC)/socketWatchServer.c 	
	$(CC) $(CFLAGS) -o $(PATH_OUT)/socketwatchser $(PATH_SRC)/socketWatchServer.c -I $(PATH_INCLUDE)
lookoutServerPS:$(PATH_SRC)/lookoutServerPS.c 
	$(CC) $(CFLAGS) -o $(PATH_OUT)/lookoutServerPS $(PATH_SRC)/lookoutServerPS.c -I $(PATH_INCLUDE)

clean:
	$(foreach BIN, $(BIN), rm -f $(PATH_OUT)/$(BIN))
