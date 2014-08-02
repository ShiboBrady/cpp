#include "network.h"
#include <pthread.h>
#include <sys/epoll.h>

void preprocess(int *fd_server)
{
    int reuse = 1;
    if(-1 == (*fd_server = socket(PF_INET, SOCK_STREAM, 0)))
        ERR_EXIT("socket");
    if(-1 == setsockopt(*fd_server, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)))
        ERR_EXIT("setsockopt");

    SA server_addr;
    socklen_t addrlen = sizeof(server_addr);
    bzero(&server_addr, addrlen);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(-1 == bind(*fd_server, (struct sockaddr *)&server_addr, addrlen))
        ERR_EXIT("bind");

    if(-1 == listen(*fd_server, SOMAXCONN))
        ERR_EXIT("listen");
}

void do_epoll(int fd_server)
{
    int epollfd = epoll_create(2048);
    if(epollfd == -1)
        ERR_EXIT("epoll_create");
    struct epoll_event ev;
    ev.data.fd = fd_server;
    ev.events = EPOLLIN;
    if(-1 == epoll_ctl(epollfd, EPOLL_CTL_ADD, fd_server, &ev))
        ERR_EXIT("epoll_ctl");
    struct epoll_event events[2048];
    int nready;

    while(1){
        nready = epoll_wait(epollfd, events, 2048, -1);
        if(nready == -1){
            if(errno == EINTR)
                continue;
            ERR_EXIT("epoll_wait");
        }

        int i;
        for(i = 0; i < nready; ++i){
            if(events[i].data.fd == fd_server){
                SA client_addr;
                socklen_t addrlen = sizeof(client_addr);
                int fd_client = accept(fd_server, (struct sockaddr*)&client_addr, &addrlen);
                printf("client %s:%d is online.\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                struct epoll_event ev;
                ev.data.fd = fd_client;
                ev.events = EPOLLIN;
                if(-1 == epoll_ctl(epollfd, EPOLL_CTL_ADD, fd_client, &ev))
                    ERR_EXIT("epoll_ctl");
            }else{
                int fd_client = events[i].data.fd;
                char recvbuf[1024] = {0};
                int ret = readline(fd_client, recvbuf, 1024);
                if(ret == -1)
                    ERR_EXIT("readline");
                else if(ret == 0){
                    printf("one client close\n");
                    struct epoll_event ev;
                    ev.data.fd = fd_client;
                    if(-1 == epoll_ctl(epollfd, EPOLL_CTL_DEL, fd_client, &ev))
                        ERR_EXIT("epoll_ctl");
                    close(fd_client);
                    continue;                    
                }
                printf("recv msg: %s", recvbuf);
                writen(fd_client, recvbuf, strlen(recvbuf));
            }
        }
    }
}

int main(int argc, const char *argv[])
{
    if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        ERR_EXIT("signal");
    int fd_server;
    preprocess(&fd_server);
    do_epoll(fd_server); 
    close(fd_server);
    return 0;
}
