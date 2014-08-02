#include "network.h"
#include <pthread.h>

void do_service(int fd_client)
{
    char recvbuf[1024] = {0};
    int ret;
    while(1){
        ret = readline(fd_client, recvbuf, 1024);
        if(ret == 0)
            break;
        if(ret == -1)
            exit(EXIT_FAILURE);
        printf("recv data: %s", recvbuf);
        writen(fd_client, recvbuf, strlen(recvbuf));
    }
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

void *threadHandler(void *arg)
{
    pthread_detach(pthread_self());
    int *p = (int *)arg;
    int fd_client = *p;
    free(p);
    do_service(fd_client);
    close(fd_client);
    pthread_exit(NULL);
}

int main(int argc, const char *argv[])
{
    int fd_server, fd_client;
    pthread_t tid;
    SA client_addr;
    socklen_t addrlen = sizeof(client_addr);   

    preprocess(&fd_server);

    while(1){
        if(-1 == (fd_client = accept(fd_server, (struct sockaddr*)&client_addr, &addrlen)))
        ERR_EXIT("accept");
        printf("Client %s:%d is online.\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        int *p = (int *)calloc(1, sizeof(int));
        *p = fd_client;
        if(pthread_create(&tid, NULL, threadHandler, (void *)p))
            free(p);
    }
    return 0;
}
