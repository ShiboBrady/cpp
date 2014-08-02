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
    int fd = open("3.txt", O_WRONLY | O_CREAT | O_EXCL, 0666);
    if(fd == -1)
        ERR_EXIT("open");
    char buf[1024] = "wang si ke shi yi ge hao gu niang.";
    write(fd, buf, sizeof(buf));
    close(fd);
    return 0;
}
