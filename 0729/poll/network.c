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
    ssize_t nwrite;
    char *bufp = usrbuf;

    while(nleft > 0){
        nwrite = write(fd, bufp, nleft);
        if(nwrite <= 0){
            if(errno = EINTR)
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
    size_t rtn;
    while(1){
        rtn = recv(sockfd, usrbuf, len, MSG_PEEK);
        if(rtn < 0){
            if(errno == EINTR)
                continue;
            return -1;
        }
        break;
    }
    return rtn;
}

ssize_t readline(int sockfd, char *usrbuf, size_t len)
{
    size_t nread;
    size_t rtn;
    ssize_t nleft = len - 1;
    char tempbuf[1024];
    int total = 0;
    char *bufp = usrbuf;
    int i;
    while(nleft > 0){
        nread = recv_peek(sockfd, tempbuf, nleft);
        if(nread <= 0)
            return nread;

        for(i = 0; i < nread; ++i){
            if(tempbuf[i] == '\n'){
                rtn = readn(sockfd, bufp, i + 1); 
                if(rtn < (i + 1))
                    return -1;
                total += (i + 1);
                bufp[i + 1] = 0;
                return total;
            }
        }

        rtn = readn(sockfd, bufp, nread);
        if(rtn < nread)
            return -1;
        bufp += nread;
        nleft -= nread;
        total += nread;
    }
    *bufp = 0;
    return (len - 1);
}
