#include "PollPoller.h"
#include "network.h"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h> 

using namespace std;
void func(int fd, char *msg)
{
    cout << "Recv msg: " << msg;
    writen(fd, msg, strlen(msg));
}

void do_service(int listenfd)
{
    PollPoller poll_t(listenfd, func);
    while(1){
        poll_t.wait();
        poll_t.handle();
    }
}

void preprocess(int *listenfd)
{
    SA server_addr;
    socklen_t addrlen = sizeof(server_addr);
    int reuse = 1;
    
    if(-1 == (*listenfd = socket(PF_INET, SOCK_STREAM, 0)))
        throw runtime_error("socket");

    if(-1 == setsockopt(*listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)))
        throw runtime_error("setsockopt");

    bzero(&server_addr, addrlen);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(-1 == ::bind(*listenfd, (struct sockaddr *)&server_addr, addrlen))
        throw runtime_error("bind");

    if(-1 == listen(*listenfd, SOMAXCONN))
        throw runtime_error("listen");
}

int main(int argc, char *argv[])
{
    int listenfd;
    preprocess(&listenfd);
    do_service(listenfd);
    return 0;
}
