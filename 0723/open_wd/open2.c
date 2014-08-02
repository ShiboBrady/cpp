#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc, const char *argv[])
{
    int fd = open("2.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
    if(fd == -1){
        ERR_EXIT ("open");
    }

    char buf[1024] = "wo ai ni zhong guo.";
    write(fd, buf, sizeof(buf));
    close(fd);
    return 0;
}
