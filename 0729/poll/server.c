#include "network.h"

void preprocess(int *fd_server)
{
    SA server_addr;
    int reuse = 1;
    int addrlen = sizeof(server_addr);

    if(-1 == (*fd_server = socket(PF_INET, SOCK_STREAM, 0)))
        ERR_EXIT("socket");
    
    if(-1 == setsockopt(*fd_server, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)))
        ERR_EXIT("setsockopt");

    bzero(&server_addr, addrlen);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(-1 == bind(*fd_server, (struct sockaddr*)&server_addr, addrlen))
        ERR_EXIT("bind");

    if(-1 == listen(*fd_server, SOMAXCONN))
        ERR_EXIT("listen");
}

void do_service(int fd_client)
{
    char recvbuf[1024] = {0};
    int ret;
    while(1){
        ret = readline(fd_client, recvbuf, 1024);
        if(ret == 0)
            break;
        printf("recv data: %s", recvbuf);
        writen(fd_client, recvbuf, strlen(recvbuf));
    }
}

int main(int argc, const char *argv[])
{
    int fd_server, fd_client;
    SA client_addr;
    int addrlen = sizeof(client_addr);

    preprocess(&fd_server);

    if(-1== (fd_client = accept(fd_server, (struct sockaddr*)&client_addr, &addrlen)))
        ERR_EXIT("accept");

    do_service(fd_client);

    close(fd_client);
    close(fd_server);
    return 0;
}
