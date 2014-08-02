#include "network.h"
#include "select_t.h"
#include <pthread.h>
#include <sys/select.h>

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

void do_select(int fd_server)
{
    select_t my_select;
    select_init(&my_select, fd_server);
    select_set_func(&my_select, handlerfunc);
    while(1){
        select_wait(&my_select);
        select_handle_accept(&my_select);
        if(my_select.nready_ == 0)
            continue;
        select_handle_data(&my_select);
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
