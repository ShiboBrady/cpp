#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <unistd.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

void setNonblock(int fd);
void setBlock(int fd);

int main(int argc, const char *argv[])
{
    setNonblock(STDIN_FILENO);
    //setBlock(STDIN_FILENO);

    char buf[1024];
    bzero(buf, 1024);
    fgets(buf, 1024, stdin);
    fputs(buf, stdout);
    return 0;
}

void setNonblock(int fd)
{
    int val = fcntl(fd, F_GETFL, 0);
    if(val == -1){
        ERR_EXIT("fcntl");
    }

    val |= O_NONBLOCK;
    if(fcntl(fd, F_SETFL, val) < 0)
        ERR_EXIT("fcntl");
}

void setBlock(int fd)
{
    int val = fcntl(fd, F_GETFL, 0);
    if(val == -1)
        ERR_EXIT("fcntl");
    val &= ~O_NONBLOCK;
    if(fcntl(fd, F_SETFL, val) < 0)
        ERR_EXIT("fcntl");
}

