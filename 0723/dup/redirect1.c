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
    int fd = open("1.txt", O_RDONLY);
    if(fd == -1)
        ERR_EXIT("open");
    close(STDIN_FILENO);
    int fd2 = dup(fd);

    char buf[1024];
    int read_n = read(STDIN_FILENO, buf, 1024);
    if(read_n == -1)
        ERR_EXIT("read");
    write(STDOUT_FILENO, buf, strlen(buf));
    close(fd);
    return 0;
}
