#include "network.h"
#include <pthread.h>
#include <poll.h>

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

void do_poll(int fd_server)
{
    struct pollfd clients[2048];
    int i;
    for(i = 1; i < 2048; ++i)
        clients[i].fd = -1;
    clients[0].fd = fd_server;
    clients[0].events = POLLIN;
    int max = 0;
    int nready;

    while(1){
        nready = poll(clients, max + 1, -1); //wait操作，等待可用的套接字描述符
        if(nready == -1){
            if(errno == EINTR)//处理中断信号
                continue;
            ERR_EXIT("poll");
        }else if(nready == 0)//超时退出本次等待，继续下次等待
            continue;

        if(clients[0].revents & POLLIN){//监听套接字非阻塞，即有客户端连接
            SA client_addr;
            socklen_t addrlen = sizeof(client_addr);
            int fd_client = accept(clients[0].fd, (struct sockaddr*)&client_addr, &addrlen);  //连接，并获取与客户端连接的套接字描述符
            if(fd_client == -1)
                ERR_EXIT("accept");
            int i;
            for(i = 1; i < 2048; ++i){  //查找可用的位置，将这个客户端加入监听队列
                if(clients[i].fd == -1){
                    clients[i].fd = fd_client;
                    clients[i].events = POLLIN;
                    if(i > max)  //更新监听队列下标
                        max = i;
                    break;  //此处很关键，不可缺少
                }
            }
            if(i == 2048){
                fprintf(stderr, "Too many clients.\n");
            }            
            if(--nready <= 0)
                continue;
        }
        //查询发信号的客户端
        for(i = 1; i <= max; ++i){
            int fd = clients[i].fd;
            if(fd == -1)
                continue;
            if(clients[i].revents & POLLIN){
                char recvbuf[1024] = {0};
                int nread = readline(fd, recvbuf, 1024);
                if(nread == -1)
                    ERR_EXIT("readline");
                else if(nread == 0){
                    printf("one client close.\n");
                    clients[i].fd = -1;
                    close(fd);
                    continue;
                }
                printf("recv msg: %s", recvbuf);
                writen(fd, recvbuf, strlen(recvbuf));
                if(--nready <= 0)
                    break;
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
    do_poll(fd_server); 
    close(fd_server);
    return 0;
}
