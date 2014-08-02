#ifndef POLL_T_H
#define POLL_T_H 
#include "network.h"
#include <poll.h>
    
typedef void (*handler_callback)(int fd, char *msg);

typedef struct poll_t
{
    struct pollfd clients_[2048];
    int maxi_;
    int nready_;
    int listenfd_;
    handler_callback func_;
}poll_t;

void poll_init(poll_t *poll, int listenfd);
void poll_wait(poll_t *poll);
void poll_handle_accept(poll_t *poll);
void poll_handle_data(poll_t *poll);
void poll_set_func(poll_t *poll, handler_callback func_);

#endif  /*POLL_T_H*/
