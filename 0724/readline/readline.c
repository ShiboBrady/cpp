#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

ssize_t readline(int fd, char *usrbuf, size_t n);
int main(int argc, const char *argv[])
{
    int fd = open("1.txt", O_RDONLY);
    char buf[1024] = {0};
    ssize_t rev;
    while((rev = readline(fd, buf, 1024)) > 0){
        write(STDOUT_FILENO, buf, strlen(buf));
        bzero(buf, 1024);
    }
    close(fd);
    return 0;
}

ssize_t readline(int fd, char *usrbuf, size_t maxLine)
{
    size_t nleft = maxLine - 1;
    ssize_t nread = 0;
    char *bufp = usrbuf;
    char c;

    while(nleft > 0){
        if((nread = read(fd, &c, 1)) == -1){
            if(errno == EINTR){
                continue;
            }else{
                return -1;
            }
        }else if(nread == 0){
            break;
        }
        *bufp++ = c;
        nleft--;
        if(c == '\n'){
            break;
        }
    }
    *bufp = '\0';
    return (maxLine - nleft -1);
}
