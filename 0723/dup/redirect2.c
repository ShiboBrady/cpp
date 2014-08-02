#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc, const char *argv[])
{
    int fd = open("1.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
    if(fd == -1)
        ERR_EXIT("open");

    dup2(fd, 1);

    char buf[1024] = "dup2:Hello, World!";
    write(STDOUT_FILENO, buf, strlen(buf));
    close(fd);
    return 0;
}
