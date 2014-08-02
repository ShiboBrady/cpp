.PHONY:clean  
CC=gcc  
CFLAGS=-Wall -g  
BIN=server
OBJS=server.o network.o  
$(BIN):$(OBJS)  
	$(CC) $(CFLAGS) $^ -o $@ -lpthread
%.o:%.cpp  
	$(CC) $(CFLAGS) -c $< -o $@  
clean:  
	rm -f *.o $(BIN) 

