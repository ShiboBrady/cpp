.PHONY:clean  
CC=gcc 
CFLAGS=-Wall -g  
BIN=server
OBJS=server.o network.o poll_t.c
$(BIN):$(OBJS)  
	$(CC) $(CFLAGS) $^ -o $@ -lpthread
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@  
clean:  
	rm -f *.o $(BIN) 

