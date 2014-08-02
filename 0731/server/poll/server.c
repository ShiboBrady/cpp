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
    //初始化各参数
    struct pollfd clients[2048];
    int i;
    for(i = 1; i < 2048; ++i)
        clients[i].fd = -1;
    clients[0].fd = fd_server;
    clients[0].events = POLLIN;
    int maxi = 0;
    int nready;

    //while循环    
    while(1){
        nready = poll(clients, maxi + 1, -1);
        if(nready == -1){
            if(errno == EINTR)
                continue;
            ERR_EXIT("poll");
        }else if(nready == 0)
            continue;

        //判断fd_server。
        if(clients[0].revents & POLLIN){
            SA client_addr;
            socklen_t addrlen = sizeof(client_addr);
            int fd_client = accept(fd_server, (struct sockaddr*)&client_addr, &addrlen);
            if(fd_client == -1)
                ERR_EXIT("accept");
            printf("Client %s:%d is online.\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            int i;
            for(i = 1; i < 2048; ++i){
                if(clients[i].fd == -1){
                    clients[i].fd = fd_client;
                    clients[i].events = POLLIN;
                    if(i > maxi)
                        maxi = i;
                    break;
                }
            }

            if(i == 2048){
                fprintf(stderr, "Too many client.\n");
                exit(EXIT_FAILURE);
            }

            if(--nready == 0)
                continue;
        }

        //判断客户端
        int i;
        for(i = 1; i <= maxi; ++i){
            //if(nready == 0)
            //    break;
            //if(clients[i].fd != -1 && (clients[i].revents & POLLIN)){
            if(clients[i].revents & POLLIN){
                char recvbuf[1024] = {0};
                int fd = clients[i].fd;
                int nread = readline(fd, recvbuf, 1024);
                if(nread == -1)
                    ERR_EXIT("readline");
                else if(nread == 0){
                    clients[i].fd = -1;
                    close(fd);
                    printf("One client is offline.\n");
                    --nready;
                    continue;
                }
                printf("recv msg: %s", recvbuf);
                writen(fd, recvbuf, strlen(recvbuf));
                --nready;
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
