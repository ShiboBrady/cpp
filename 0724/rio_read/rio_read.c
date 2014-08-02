#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define RIO_BUFFERSIZE 8192
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

typedef struct rio_t{
    ssize_t left_;
    char buffer_[RIO_BUFFERSIZE];
    char *bufPtr_;
    int fd_;
}rio_t;

void rio_init(rio_t *r, int fd)
{
    r->fd_ = fd;
    r->left_ = 0;
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
        }else if(nread == 0){
            return 0;        
        }
        r->left_ = nread;
        r->bufPtr_ = r->buffer_;
    }
    
    int rev = n;
    if(n > r->left_){
        rev = r->left_;
    }
    memcpy(usrbuf, r->bufPtr_, rev);
    r->left_ -= rev;
    r->bufPtr_ += rev;
    return rev;
}

ssize_t rio_readn(rio_t *r, char *usrbuf, size_t n)
{
    ssize_t nread;
    size_t nleft = n;
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
ssize_t rio_readline(rio_t *r, char *usrbuf, size_t maxlen)
{
    size_t nleft = maxlen -1;
    ssize_t nread = 0;
    char c;
    while(nleft > 0){
        nread = rio_read(r, &c, 1);
        if(nread == -1){
            return -1;
        }else if(nread == 0){
            break;
        }else{
            *usrbuf++ = c;
            nleft--;
            if(c == '\n'){
                break;
            }
        }
    }
    *usrbuf = '\0';
    return (maxlen - nleft);
}

int main(int argc, const char *argv[])
{
    rio_t r;
    char buf[1024] = {0};
    int fd = open("1.txt", O_RDONLY);
    rio_init(&r, fd);
    //ssize_t rev = rio_read(&r, buf, 1024);
    ssize_t rev = rio_readn(&r, buf, 1024);
    printf("buf = %s\n", buf);
    close(fd);
    return 0;
}
