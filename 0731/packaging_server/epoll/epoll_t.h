#ifndef EPOLL_T_H
#define EPOLL_T_H 
#include <sys/epoll.h>
#include <errno.h>
#include "network.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

typedef void (*handlerfunc)(int, char*);

typedef struct epoll_t
{
    int epollfd_;
    struct epoll_event events_[2048];
    int nready_;    
    int listenfd_;
    handlerfunc func_;
}epoll_t;

void epoll_init(epoll_t *epoll, int listenfd, handlerfunc func);
void epoll_wait_signal(epoll_t *epoll);
void epoll_handle(epoll_t *epoll);
void epoll_handle_accept(epoll_t *epoll);
void epoll_handle_data(epoll_t *epoll, int fd);
void epoll_close(epoll_t *epoll);

#endif  /*EPOLL_T_H*/
