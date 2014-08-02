.PHONY:clean all
CC= gcc
DFLAGS=-Wall -g
BIN=signal signal2 sleep alarm sigchld
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)
