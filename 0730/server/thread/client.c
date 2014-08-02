#include "network.h"
#include <sys/epoll.h>

void do_service(int fd_client)
{
    char recvbuf[1024] = {0};
    char sendbuf[1024] = {0};

    //准备工作
    //1、创建epoll句柄，fd
    int epollfd = epoll_create(2);
    if(epollfd == -1)
        ERR_EXIT("epoll_create");
    //2、注册两个fd
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = fileno(stdin);
    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, fileno(stdin), &ev) == -1)
        ERR_EXIT("epoll_ctl");
    ev.events = EPOLLIN;
    ev.data.fd = fd_client;
    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, fd_client, &ev) == -1)
        ERR_EXIT("epoll_ctl");

    //3、准备一个数组
    struct epoll_event events[2];
    int nready;

    while(1){
        nready = epoll_wait(epollfd, events, 2, -1);
        if(nready == -1)
        {
            if(errno == EINTR)
                continue;
            ERR_EXIT("epoll_wait");
        }else if(nready == 0){
            continue;
        }

        int i;
        for(i = 0; i < nready; ++i){
            int fd = events[i].data.fd;
            if(fd == STDIN_FILENO)
            {
                if(fgets(sendbuf, 1024, stdin) == NULL)
                {
                    shutdown(fd_client, SHUT_WR);
                    struct epoll_event ev;
                    ev.data.fd = STDIN_FILENO;
                    if(epoll_ctl(epollfd, EPOLL_CTL_DEL, STDIN_FILENO, &ev) == -1)
                        ERR_EXIT("epoll_ctl");

                }else
                {
                    writen(fd_client, sendbuf, strlen(sendbuf));
                }
            }

            if(fd == fd_client)
            {
                int ret = readline(fd_client, recvbuf, 1024);
                if(ret == -1)
                    ERR_EXIT("readline");
                else if(ret == 0)
                {
                    close(fd_client);
                    printf("server close\n");
                    exit(EXIT_SUCCESS);
                }
                printf("recv data: %s", recvbuf);
            }
        }
    }
}


int main(int argc, const char *argv[])
{
    int fd_client;
    if(-1 == (fd_client = socket(PF_INET, SOCK_STREAM, 0)))
        ERR_EXIT("socket");

    SA client_addr;
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(9999);
    client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(-1 == connect(fd_client, (struct sockaddr*)&client_addr, sizeof(client_addr)))
        ERR_EXIT("connect");

    do_service(fd_client);
    close(fd_client);    
    return 0;
}
