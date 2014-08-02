#ifndef SELECT_T_H
#define SELECT_T_H 
#include "network.h"

typedef void (*handler_callback)(int, char*);

typedef struct select_t
{
    fd_set fset_;
    fd_set fset_bkp_;
    int clients_[FD_SETSIZE];
    int maxi_;
    int maxfd_;
    int listenfd_;
    int nready_;
    handler_callback func_;
}select_t;

void select_init(select_t *sel, int listenfd);
void select_wait(select_t *sel);
void select_handle_accept(select_t *sel);
void select_handle_data(select_t *sel);
void select_set_func(select_t *sel, handler_callback func);

#endif  /*SELECT_T_H*/
