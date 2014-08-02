.PHONY:clean  
CC=g++  
CFLAGS=-Wall -g  
BIN=server
OBJS=server.o threadpool.o mutex.o cond.o network.o  
$(BIN):$(OBJS)  
	$(CC) $(CFLAGS) $^ -o $@ -lpthread -std=c++0x 
%.o:%.cpp %.c
	$(CC) $(CFLAGS) -c $< -o $@  
clean:
	rm -f *.o $(BIN)  
