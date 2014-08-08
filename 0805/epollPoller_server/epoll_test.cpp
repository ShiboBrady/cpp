#include "EpollPoller.h"
#include "network.h"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h> 


void func(int fd, char *msg)
{
    std::cout << "Recv msg: " << msg;
    writen(fd, msg, strlen(msg));
}

void do_service(int listenfd)
{
    EpollPoller epoll_t(listenfd, func);
    while(1){
        epoll_t.wait();
        epoll_t.handle();
    }
}

void preprocess(int *listenfd)
{
    SA server_addr;
    socklen_t addrlen = sizeof(server_addr);
    int reuse = 1;
    
    if(-1 == (*listenfd = socket(PF_INET, SOCK_STREAM, 0)))
        throw std::runtime_error("socket");

    if(-1 == setsockopt(*listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)))
        throw std::runtime_error("setsockopt");

    bzero(&server_addr, addrlen);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(-1 == bind(*listenfd, (struct sockaddr *)&server_addr, addrlen))
        throw std::runtime_error("bind");

    if(-1 == listen(*listenfd, SOMAXCONN))
        throw std::runtime_error("listen");
}

int main(int argc, char *argv[])
{
    int listenfd;
    preprocess(&listenfd);
    do_service(listenfd);
    return 0;
}
