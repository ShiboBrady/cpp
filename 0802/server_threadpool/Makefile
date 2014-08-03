.PHONY:clean  
CC=g++  
CFLAGS=-Wall -g  
BIN=server  
OBJS=server.o threadpool.o network.o cond.o mutex.o  
$(BIN):$(OBJS)  
	$(CC) $(CFLAGS) $^ -o $@ -lpthread -std=c++0x 
%.o:%.cpp %.c
	$(CC) $(CFLAGS) -c $< -o $@ -lpthread -std=c++0x
clean:  
	rm -f *.o $(BIN)  

