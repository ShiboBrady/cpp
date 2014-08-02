#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stddef.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

ssize_t readn(int fd, char *usrbuf, size_t n);
ssize_t writen(int fd, char *usrbuf, size_t n);
int main(int argc, const char *argv[])
{
    int fd = open("1.txt", O_RDONLY);
    if(fd == -1)
        ERR_EXIT("open");
    int rev = 0;
    char buf[100] = {0};
    while((rev = readn(fd, buf, 5)) > 0){
        writen(STDOUT_FILENO, buf, rev);
    }
    close(fd);
    return 0;
}

ssize_t readn(int fd, char *usrbuf, size_t n)
{
    size_t nleft = n;
    size_t nread;
    char *bufp = usrbuf;

    while(nleft > 0){
        if((nread = read(fd, bufp, nleft)) == -1){
            if(errno == EINTR)
                continue;
            else
                return -1;
        }else if(nread == 0)
            break;

        nleft -= nread;
        bufp += nread;
    }
    return (n - nleft);
}

ssize_t writen(int fd, char *usrbuf, size_t n)
{
    size_t nleft = n;
    size_t nwrite;
    char *bufp = usrbuf;

    while(nleft > 0){
        if((nwrite = write(fd, bufp, nleft)) <= 0){
            if(errno == EINTR)
                nwrite = 0;
            else
                return -1;
        }
        nleft -= nwrite;
        bufp += nwrite;
    }
    return n;
}
