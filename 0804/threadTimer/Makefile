.PHONY:clean
CC=g++
CFLAGS=-Wall -g
BIN=test
OBJS=test.o Thread.o Timer.o
LINK=-lpthread
STAR=-std=c++0x
$(BIN):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LINK)
%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(STAR)
clean:
	rm -f *.o $(BIN)

