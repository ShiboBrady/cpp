#include "network.h"
#include <sys/epoll.h>

void do_service(int fd_client)
{
    char recvbuf[1024] = {0};
    char sendbuf[1024] = {0};

    int epollfd = epoll_create(2);
    if(epollfd == -1)
        ERR_EXIT("epoll_create");

    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = STDIN_FILENO;
    if(-1 == epoll_ctl(epollfd, EPOLL_CTL_ADD, STDIN_FILENO, &ev))
        ERR_EXIT("epoll_ctl");
    ev.events = EPOLLIN;
    ev.data.fd = fd_client;
    if(-1 == epoll_ctl(epollfd, EPOLL_CTL_ADD, fd_client, &ev))
        ERR_EXIT("epoll_ctl");

    struct epoll_event events[2];
    int nready;

    while(1){
        nready = epoll_wait(epollfd, events, 2, -1);
        if(nready == -1){
            if(errno == EINTR)
                continue;
            ERR_EXIT("epoll_wait");
        }else if(nready == 0)
            continue;

        int i;
        for(i = 0; i < nready; ++i){
            int fd = events[i].data.fd;
            if(fd == STDIN_FILENO){
                if(fgets(sendbuf, 1024, stdin) == NULL){
                    shutdown(fd_client, SHUT_WR);
                    struct epoll_event ev;
                    ev.data.fd = STDIN_FILENO;
                    if(-1 == epoll_ctl(epollfd, EPOLL_CTL_DEL, STDIN_FILENO, &ev))
                        ERR_EXIT("epoll_ctl");
                }else{
                    writen(fd_client, sendbuf, strlen(sendbuf));
                }
            }

            if(fd == fd_client){
                int ret = readline(fd_client, recvbuf, 1024);
                if(ret == -1){
                    ERR_EXIT("readline");
                }else if(ret == 0){
                    close(fd_client);
                    printf("server close\n");
                    exit(EXIT_SUCCESS);
                }
                printf("recv data: %s", recvbuf);
            }
        }

       
    }
}

