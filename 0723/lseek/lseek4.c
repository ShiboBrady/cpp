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
    write(fd, "Hello", 5);
    off_t len = lseek(fd, 1024 * 1024, SEEK_CUR);
    printf("offset = %d\n", (int)len);
    write(fd, "world", 5);
    return 0;
}
