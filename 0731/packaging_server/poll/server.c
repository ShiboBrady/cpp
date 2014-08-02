#include "network.h"
#include "poll_t.h"
#include <pthread.h>
#include <poll.h>

void handlerfunc(int fd, char *msg)
{
    printf("recv msg: %s", msg);
    writen(fd, msg, strlen(msg));
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

void do_poll(int fd_server)
{
    poll_t my_poll;
    poll_init(&my_poll, fd_server);
    poll_set_func(&my_poll, handlerfunc);
    while(1){
        poll_wait(&my_poll);
        poll_handle_accept(&my_poll);
        if(my_poll.nready_ == 0)
            continue;
        poll_handle_data(&my_poll);
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
