#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

#define RIO_BUFFERSIZE 8192
#define MAXLINE 1024

typedef struct rio_t{
    int fd_;
    char buffer_[RIO_BUFFERSIZE];
    char *bufPtr_;
    ssize_t left_;
}rio_t;

void rio_init(rio_t *r, int fd)
{
    r->left_ = 0;
    r->fd_ = fd;
    bzero(r->buffer_, RIO_BUFFERSIZE);
    r->bufPtr_ = r->buffer_;
}

ssize_t rio_read(rio_t *r, char *usrbuf, size_t n)
{
    ssize_t nread; 
    while(r->left_ <= 0){
        bzero(r->buffer_, RIO_BUFFERSIZE);
        nread = read(r->fd_, r->buffer_, RIO_BUFFERSIZE);
        if(nread == -1){
            if(errno == EINTR)
                continue;
            return -1;
        }else if(nread == 0)
            return 0;
        r->left_ = nread;
        r->bufPtr_ = r->buffer_;
    }
    int rev = n;
    if(rev > r->left_){
        rev = r->left_;
    }
    memcpy(usrbuf, r->bufPtr_, rev);
    r->left_ -= rev;
    r->bufPtr_ += rev;
    return rev;
}

ssize_t rio_readn(rio_t *r, char *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;
    while(nleft > 0){
        nread = rio_read(r, bufp, nleft);
        if(nread == -1)
            return -1;
        else if(nread == 0)
            break;
        nleft -= nread;
        bufp += nread;
    }
    return (n - nleft);
}

ssize_t rio_writen(int fd, char *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nwrite;
    char *bufp = usrbuf;
    while(nleft > 0){
        nwrite = write(fd, bufp, nleft);
        if(nwrite <= 0){
            if(errno == EINTR)
                continue;
            else
                return -1;
        }
        nleft -= nwrite;
        bufp += nwrite;
    }
    return (n - nleft);
}

ssize_t rio_readline(rio_t *r, char *usrbuf, size_t n)
{
    char c;
    ssize_t nread;
    int i;
    for(i = 0; i < n - 1; ++i){
        nread = rio_read(r, &c, 1);
        if(nread == -1)
            return -1;
        else if(nread == 0){
            if(i == 0){
                return 0;
            }else{
                break;
            }
        }
        *usrbuf++ = c;
        if(c == '\n')
            break;
    }
    *usrbuf = '\0';
    return (i + 1);
}

int main(int argc, const char *argv[])
{
    rio_t r;
    ssize_t nread;
    int fd = open("1.txt", O_RDONLY);
    rio_init(&r, fd);
    char buf[MAXLINE] = {0};
    while((nread = (rio_readn(&r, buf, MAXLINE))) > 0){
        rio_writen(STDOUT_FILENO, buf, nread);
    }
    return 0;
}
