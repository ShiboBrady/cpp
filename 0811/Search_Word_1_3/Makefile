.PHONY:clean  
CC=g++  
CFLAGS=-Wall -g  
LINKS=-lecho -lpthread
STATE=-std=c++0x
BIN=server  
OBJS=Search.o Server.o test.o  
$(BIN):$(OBJS)  
	$(CC) $(CFLAGS) $^ -o $@ $(LINKS)
%.o:%.cpp  
	$(CC) $(CFLAGS) -c $< -o $@ $(STATE) 
clean:  
	rm -f *.o $(BIN)  
