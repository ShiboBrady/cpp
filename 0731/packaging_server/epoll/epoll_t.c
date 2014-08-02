#include "epoll_t.h"
#include <errno.h>
#include "network.h"
#include <sys/types.h>
#include <sys/socket.h>

void epoll_add_fd(epoll_t *, int);
void epoll_del_fd(epoll_t *, int);

void epoll_init(epoll_t *epoll, int listenfd, handlerfunc func)
{
    epoll->epollfd_ = epoll_create(2048);
    epoll->listenfd_ = listenfd;
    epoll_add_fd(epoll, listenfd);
    epoll->nready_ = 0;
    epoll->func_ = func;
}

void epoll_wait_signal(epoll_t *epoll)
{
    int nready;
    do{
        nready = epoll_wait(epoll->epollfd_, epoll->events_, 2048, -1); 
    }while(nready == -1 && errno == EINTR);
    if(nready == -1)
        ERR_EXIT("epoll_wait");
    epoll->nready_ = nready;
}

void epoll_handle(epoll_t *epoll)
{
    int i;
    for(i = 0; i < epoll->nready_; ++i){
        if(epoll->listenfd_ == epoll->events_[i].data.fd){
            epoll_handle_accept(epoll);
        }else{
            epoll_handle_data(epoll, epoll->events_[i].data.fd);
        }
    }
}

void epoll_handle_accept(epoll_t *epoll)
{
    SA client_addr;
    socklen_t addrlen = sizeof(client_addr);
    int fd_client = accept(epoll->listenfd_, (struct sockaddr*)&client_addr, &addrlen);
    if(fd_client == -1)
        ERR_EXIT("accept");
    printf("Client %s:%d is online.\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    epoll_add_fd(epoll, fd_client);
}

void epoll_handle_data(epoll_t *epoll, int fd)
{
    char recvbuf[1024] = {0};
    int rtn = readline(fd, recvbuf, 1024);
    if(rtn == -1)
        ERR_EXIT("readline");
    else if(rtn == 0){
        printf("One client is offline.\n");
        epoll_del_fd(epoll, fd);
        return;
    }
    epoll->func_(fd, recvbuf);
}

void epoll_close(epoll_t *epoll)
{
    close(epoll->epollfd_);
}
void epoll_add_fd(epoll_t *epoll, int fd)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if(-1 == epoll_ctl(epoll->epollfd_, EPOLL_CTL_ADD, fd, &ev))
        ERR_EXIT("epoll_ctl");
}

void epoll_del_fd(epoll_t *epoll, int fd)
{
      struct epoll_event ev;
      ev.data.fd = fd;
      ev.events = EPOLLIN;
      if(-1 == epoll_ctl(epoll->epollfd_, EPOLL_CTL_DEL, fd, &ev))
          ERR_EXIT("epoll_ctl");
}


