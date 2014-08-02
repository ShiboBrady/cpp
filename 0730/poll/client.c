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
    int ready;

    while(1){
        nready = poll(client, maxi + 1, -1);
        if(neady == -1){
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
