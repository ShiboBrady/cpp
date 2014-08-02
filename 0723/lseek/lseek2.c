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
    int fd = open("3.txt", O_RDONLY);
    if(fd == -1){
        ERR_EXIT("open");
    }

    char buf[1024];
    bzero(buf, 1024);
    read(fd, buf, 3);
    off_t len = lseek(fd, 0, SEEK_CUR);
    printf("move %d byte\n", (int)len);
    printf("buf = %s\n", buf);
    bzero(buf, 1024);
    read(fd, buf, 5);
    len = lseek(fd, 0, SEEK_CUR);
    printf("move %d byte\n", (int)len);
    printf("buf = %s\n", buf);
    len = lseek(fd, 1, SEEK_CUR);
    printf("%d\n", (int)len);
    len = lseek(fd, 0, SEEK_END);
    printf("Total len is %d\n", (int)len);
    len = lseek(fd, -2, SEEK_END);
    printf("%d\n", (int)len);
    return 0;
}
