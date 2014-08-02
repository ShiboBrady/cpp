#include "network.h"
#include <pthread.h>
#include <sys/select.h>

void preprocess(int *fd_server)
{
    int reuse = 1;
    if(-1 == (*fd_server = socket(PF_INET, SOCK_STREAM, 0)))
        ERR_EXIT("socket");
    if(-1 == setsockopt(*fd_server, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)))
        ERR_EXIT("setsockopt");

    SA server_addr;
    int addrlen = sizeof(server_addr);
    bzero(&server_addr, addrlen);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(-1 == bind(*fd_server, (struct sockaddr *)&server_addr, addrlen))
        ERR_EXIT("bind");

    if(-1 == listen(*fd_server, SOMAXCONN))
        ERR_EXIT("listen");
}

void do_select(int fd_server)
{
    //初始化
    fd_set fset, bset;
    int clients[FD_SETSIZE];
    int maxi = 0;
    int maxfd = fd_server;
    int nready;
    int i; 
    for(i = 0; i < FD_SETSIZE; ++i)
        clients[i] = -1;

    FD_ZERO(&fset);
    FD_ZERO(&bset);
    FD_SET(fd_server, &bset);

    while(1){
        //select()
        fset = bset;
        nready = select(maxfd + 1, &fset, NULL, NULL, NULL);
        if(nready == -1){
            if(errno == EINTR)
                continue;
            ERR_EXIT("select");
        }else if(nready == 0)
            continue;

        //判断fd_server
        if(FD_ISSET(fd_server, &fset)){
            SA client_addr;
            socklen_t addrlen = sizeof(client_addr);
            int fd_client = accept(fd_server, (struct sockaddr*)&client_addr, &addrlen);
            for(i = 0; i < FD_SETSIZE; ++i){
                if(clients[i] == -1){
                    clients[i] = fd_client;
                    if(i > maxi)
                        maxi = i;
                    break;
                }
            }

            if(i == FD_SETSIZE){
                fprintf(stderr, "Too many clients.\n");
                exit(EXIT_FAILURE);
            }

            FD_SET(fd_client, &bset);
            if(fd_client > maxfd)
                maxfd = fd_client;

            if(--nready <= 0)
                continue;
        }

        //判断客户端
        int i;
        for(i = 0; i <= maxi; ++i){
            if(FD_ISSET(clients[i], &fset)){
                int fd = clients[i];
                char recvbuf[1024] = {0};
                int nread = readline(fd, recvbuf, 1024);
                if(nread == -1)
                    ERR_EXIT("readline");
                else if(nread == 0){
                    clients[i] = -1;
                    FD_CLR(fd, &bset);
                    close(fd);
                    printf("one client is offline.\n");
                    if(--nready <= 0)
                        break;
                    continue;
                }
                printf("recv msg: %s", recvbuf);
                writen(fd, recvbuf, strlen(recvbuf));
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
    do_select(fd_server); 
    close(fd_server);
    return 0;
}
