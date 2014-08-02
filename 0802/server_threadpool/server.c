#include "network.h"
#include "threadpool.h"
#include <pthread.h>
#include <sys/select.h>

void preprocess(int *fd_server);
void do_service(int fd_client);

int main(int argc, const char *argv[])
{
    if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        ERR_EXIT("signal");
    int fd_server;
    SA client_addr;
    socklen_t addrlen = sizeof(client_addr);
    preprocess(&fd_server);
    Threadpool pool(5, do_service);
    pool.start();
    while(1){
        int fd_client = accept(fd_server, (struct sockaddr*)&client_addr, &addrlen);
        if(fd_client == -1)
            ERR_EXIT("accept");
        printf("Client %s:%d is online.\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        pool.add_task(fd_client);
    }
    pool.stop();
    close(fd_server);
    return 0;
}

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

void do_service(int fd_client)
{
    char recvbuf[1024] = {0};
    while(1){
        int nread = readline(fd_client, recvbuf, 1024);
        if(nread == -1)
            ERR_EXIT("readline");
        else if(nread == 0){
            printf("One client is offline");
            close(fd_client);
            break;
        }
        printf("recv msg: %s", recvbuf);
        writen(fd_client, recvbuf, strlen(recvbuf));
    }
}
