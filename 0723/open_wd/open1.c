#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc, const char *argv[])
{
    int fd = open("1.txt", O_RDONLY);
    if(fd == -1){
        ERR_EXIT("open");
    }

    char buf[1024];
    bzero(buf, sizeof(buf));

    int read_n = read(fd, buf, 1024);
    if(read_n == -1){
        ERR_EXIT("read");
    }

    printf("%s\n", buf);

    close(fd);
    return 0;
}
