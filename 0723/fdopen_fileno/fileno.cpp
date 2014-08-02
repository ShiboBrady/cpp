#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc, const char *argv[])
{
    FILE *fp = fopen("1.txt", "r");
    if(fp == NULL)
        ERR_EXIT("fopen");
    int fd = fileno(fp);
    char buf[1024];
    bzero(buf, 1024);
    int read_n = read(fd, buf, 1024);
    if(read_n == -1){
        ERR_EXIT("read");
    }
    printf("buf = %s\n", buf);
    return 0;
}
