#include "network.h"
#include <poll.h>

void do_service(int fd_client)
{
    char recvbuf[1024] = {0};
    char sendbuf[1024] = {0};

    struct pollfd client[2];
    client[0].fd = fileno(stdin);
    client[0].events = POLLIN;
    client[1].fd = fd_client;
    client[1].events = POLLIN;

    int maxi = 1;
    int nready;

    while(1){
        nready = poll(client, maxi + 1, -1);
        if(nready == -1){
            if(errno == EINTR)
                continue;
            ERR_EXIT("poll");
        }else if(nready == 0)
            continue;
        if(client[0].revents & POLLIN){
            if(fgets(sendbuf, 1024, stdin) == NULL){
                shutdown(fd_client, SHUT_WR);
                client[0].fd = -1;
            }else{
                writen(fd_client, sendbuf, strlen(sendbuf));
            }
        }

        if(client[1].revents & POLLIN){
            int ret = readline(fd_client, recvbuf, 1024);
            if(ret == -1)
                ERR_EXIT("readline");
            else if(ret == 0){
                printf("server close\n");
                close(fd_client);
                break;
            }
            printf("recv data: %s", recvbuf);
        }
    }
}


int main(int argc, const char *argv[])
{
    int fd_server;
    SA server_addr;
    int addrlen = sizeof(server_addr);

    if(-1 == (fd_server = socket(PF_INET, SOCK_STREAM, 0)))
        ERR_EXIT("socket");

    bzero(&server_addr, addrlen);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(-1 == connect(fd_server, (struct sockaddr*)&server_addr, addrlen))
        ERR_EXIT("connect");

    do_service(fd_server);

    close(fd_server);
    return 0;
}
