.PHONY:clean  
CC=g++  
CFLAGS=-Wall -g  
BIN=server
STARD=-std=c++0x -rdynamic
LINK=-lpthread -lecho
OBJS=Server.o TextQuery.o test.o 
$(BIN):$(OBJS)  
	$(CC) $(CFLAGS) $^ -o $@ $(LINK) 
%.o:%.cpp  
	$(CC) $(CFLAGS) -c $< -o $@ $(STARD)
clean:  
	rm -f *.o $(BIN)  
