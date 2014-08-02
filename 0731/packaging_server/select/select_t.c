#include "select_t.h"

void select_add_fd(select_t *sel, int fd);
void select_del_fd(select_t *sel, int i);

void select_init(select_t *sel, int listenfd)
{
    sel->listenfd_ = listenfd;
    FD_ZERO(&sel->fset_);
    FD_ZERO(&sel->fset_bkp_);
    FD_SET(listenfd, &sel->fset_bkp_);
    int i;
    for(i = 0; i < FD_SETSIZE; ++i)
        sel->clients_[i] = -1;
    sel->maxi_ = -1;
    sel->maxfd_ = listenfd;
    sel->nready_ = 0;
    sel->func_ = NULL;
}

void select_wait(select_t *sel)
{
    int nready;
    sel->fset_ = sel->fset_bkp_;
    do{
        nready = select(sel->maxfd_ + 1, &sel->fset_, NULL, NULL, NULL);
    }while((nready == -1 && errno == EINTR)); 
    if(nready == -1)
        ERR_EXIT("select");
    sel->nready_ = nready;
}

void select_handle_accept(select_t *sel)
{
    if(FD_ISSET(sel->listenfd_, &sel->fset_)){
        SA client_addr;
        socklen_t addrlen = sizeof(client_addr);
        int fd_client;
        fd_client = accept(sel->listenfd_, (struct sockaddr*)&client_addr, &addrlen);
        if(fd_client == -1)
            ERR_EXIT("accept");
        printf("Client %s:%d is online.\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        
        select_add_fd(sel, fd_client);
        --sel->nready_;
    }
}

void select_handle_data(select_t *sel)
{
    int i;
    for(i = 0; i <= sel->maxi_; ++i){
        if(sel->nready_ == 0)
            break;
        if(sel->clients_[i] != -1 && FD_ISSET(sel->clients_[i], &sel->fset_)){
            int fd = sel->clients_[i];
            char recvbuf[1024];
            int nread = readline(fd, recvbuf, 1024);
            if(nread == -1)
                ERR_EXIT("readline");
            else if(nread == 0){
                printf("one client is offline.\n");
                select_del_fd(sel, i);
                --sel->nready_;
                continue;
            }

            sel->func_(fd, recvbuf);
            --sel->nready_;
        }
    }
}

void select_set_func(select_t *sel, handler_callback func)
{
    sel->func_ = func;
}

void select_add_fd(select_t *sel, int fd)
{
    int i;
    for(i = 0; i < FD_SETSIZE; ++i){
        if(sel->clients_[i] == -1){
            sel->clients_[i] = fd;
            if(i > sel->maxi_)
                sel->maxi_ = i;
            break;
        }
    }
    if(i == FD_SETSIZE){
        fprintf(stderr, "Too many client.\n");
        exit(EXIT_FAILURE);
    }

    FD_SET(fd, &sel->fset_bkp_);
    if(fd > sel->maxfd_)
        sel->maxfd_ = fd;
}

void select_del_fd(select_t *sel, int i)
{
    int fd = sel->clients_[i];
    sel->clients_[i] = -1;
    FD_CLR(fd, &sel->fset_bkp_);
    close(fd);
}
