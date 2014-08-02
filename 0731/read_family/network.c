#include "network.h"

ssize_t readn(int fd, char *usrbuf, size_t len)
{
    size_t nleft = len;
    ssize_t nread;
    char *bufp = usrbuf;

    while(nleft > 0){
        nread = read(fd, bufp, nleft);
        if(nread == -1){
            if(errno == EINTR)
                continue;
            return -1;
        }else if(nread == 0)
            break;
        nleft -= nread;
        bufp += nread;
    }
    return (len - nleft);
}

ssize_t writen(int fd, char *usrbuf, size_t len)
{
    size_t nleft = len;
    ssize_t nwrite;
    char *bufp = usrbuf;

    while(nleft > 0){
        nwrite = write(fd, bufp, nleft);
        if(nwrite <= 0){
            if(errno == EINTR)
                continue;
            return -1;
        }
        nleft -= nwrite;
        bufp += nwrite;
    }
    return len;
}

ssize_t recv_peek(int sockfd, char *usrbuf, size_t len)
{
    ssize_t nread;
    while(1){
        nread = recv(sockfd, usrbuf, len, MSG_PEEK);
        if(nread < 0){
            if(errno == EINTR)
                continue;
            return -1;
        }
        break;
    }
    return nread;
}

ssize_t readline(int sockfd, char *usrbuf, size_t len)
{
    size_t nleft = len - 1;
    ssize_t nread;
    ssize_t rtn;
    size_t total = 0;
    char *bufp = usrbuf;
    char tempbuf[1024] = {0};

    while(nleft > 0){
        bzero(tempbuf, 1024);
        nread = recv_peek(sockfd, tempbuf, nleft);
        if(nread <= 0)
            return nread;

        int i;
        for(i = 0; i < nread; ++i){
            if(bufp[i] == '\n'){
                rtn = readn(sockfd, bufp, i + 1);
                if(rtn < (i + 1))
                    return -1;
                total += rtn;
                bufp += rtn;
                nleft -= rtn;
                *bufp = 0;
                return total;
            }
        }

        rtn = readn(sockfd, bufp, nread);
        if(rtn < nread)
            return -1;
        total += rtn;
        bufp += rtn;
        nleft -= rtn;
    }
    return (len - 1);
}
