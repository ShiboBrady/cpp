.PHONY:clean  
CC=gcc  
CFLAGS=-Wall -g  
BIN=threadpool  
OBJS=threadpool.o queue.o main.o 
$(BIN):$(OBJS)  
	$(CC) $(CFLAGS) $^ -o $@ -lpthread 
%.o:%.c  
	$(CC) $(CFLAGS) -c $< -o $@  
clean:
	 rm -f *.o $(BIN)

