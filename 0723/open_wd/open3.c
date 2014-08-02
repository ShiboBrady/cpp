#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc, const char *argv[])
{
    int fd = open("2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(fd == -1){
        ERR_EXIT("open");
    }
    char buf[1024] = "you yi ge mei li de chuan shuo, jing mei de shi tou hui chang ge.";
    write(fd, buf, strlen(buf));
    close(fd);
    return 0;
}
