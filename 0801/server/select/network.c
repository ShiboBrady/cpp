#include "network.h"

ssize_t readn(int fd, char *usrbuf, size_t len)
{
    ssize_t nleft = len;
    size_t nread;
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
    ssize_t nleft = len;
    size_t nwrite;
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
    size_t nread;
    char *bufp = usrbuf;
    while(1){
        nread = recv(sockfd, bufp, len, MSG_PEEK);
        if(nread == -1){
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
    size_t rtn;
    size_t nread;
    size_t total = 0;
    char *bufp = usrbuf;
    char tempbuf[1024] = {0};
    int i;
    while(nleft > 0){
        bzero(tempbuf, 1024);
        rtn = recv_peek(sockfd, tempbuf, nleft);
        if(rtn <= 0)
            return rtn;
        for(i = 0; i < rtn; ++i){
            if(tempbuf[i] == '\n'){
                nread = readn(sockfd, bufp, i + 1);
                if(nread != (i + 1))
                    return -1;
                total += nread;
                bufp[i + 1] = '\0';
                return total;
            }
        }

        nread = readn(sockfd, bufp, rtn);
        if(nread != rtn)
            return -1;
        bufp += nread;
        nleft -= nread;
        total += nread;
    } 
    return (len -1);
}
