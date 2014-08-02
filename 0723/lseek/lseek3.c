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
    int fd = open("1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(fd == -1){
        ERR_EXIT("open");
    }

    char buf[1024] = "xi chong";
    write(fd, buf, strlen(buf));
    off_t len = lseek(fd, 10, SEEK_CUR);
    printf("offset = %d\n", (int)len);
    bzero(buf, 1024);
    strcpy(buf, " hao wan de di fang");
    write(fd, buf, strlen(buf));
    close(fd);
    return 0;
}
