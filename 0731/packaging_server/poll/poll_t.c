#include "poll_t.h"

void poll_add_fd(poll_t *poll, int fd);
void poll_del_fd(poll_t *poll, int i);

void poll_init(poll_t *poll, int listenfd)
{
    poll->listenfd_ = listenfd;
    poll->clients_[0].fd = listenfd;
    poll->clients_[0].events = POLLIN;
    int i;
    for(i = 1; i < 2048; ++i)
        poll->clients_[i].fd = -1;
    poll->maxi_ = 0;
    poll->nready_ = 0;
    poll->func_ = NULL;
}

void poll_wait(poll_t *pol)
{
    int nready;
    do{
        nready = poll(pol->clients_, pol->maxi_ + 1, -1);
    }while((nready == -1 && errno == EINTR));
    if(nready == -1)
        ERR_EXIT("poll");
    pol->nready_ = nready;
}

void poll_handle_accept(poll_t *poll)
{
    if(poll->clients_[0].revents & POLLIN){
        SA client_addr;
        socklen_t addrlen = sizeof(client_addr);
        int fd = accept(poll->listenfd_, (struct sockaddr *)&client_addr, &addrlen);
        if(fd == -1)
            ERR_EXIT("accept");
        printf("Client %s:%d is online.\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        poll_add_fd(poll, fd);

        --poll->nready_;
    }
}

void poll_handle_data(poll_t *poll)
{
    int i;
    for(i = 1; i <= poll->maxi_; ++i){
        if(poll->nready_ == 0)
            break;
        if(poll->clients_[i].fd != -1 && (poll->clients_[i].revents & POLLIN)){
            int fd = poll->clients_[i].fd;
            char recvbuf[1024] = {0};
            int rtn = readline(fd, recvbuf, 1024);
            if(rtn == -1)
                ERR_EXIT("readline");
            else if(rtn == 0){
                printf("one client is offline.\n");
                poll_del_fd(poll, i);
                --poll->nready_;
                continue;
            }

            poll->func_(fd, recvbuf);
            --poll->nready_;
        }
    }
}

void poll_set_func(poll_t *poll, handler_callback func)
{
    poll->func_ = func; 
}

void poll_add_fd(poll_t *poll, int fd)
{
    int i;
    for(i = 1; i < 2048; ++i){
        if(poll->clients_[i].fd == -1){
            poll->clients_[i].fd = fd;
            poll->clients_[i].events = POLLIN;
            if(i > poll->maxi_)
                poll->maxi_ = i;
            break;
        }
    }

    if(i == 2048){
        fprintf(stderr, "Too much client.\n");
        exit(EXIT_FAILURE);
    }
}

void poll_del_fd(poll_t *poll, int i)
{
    int fd = poll->clients_[i].fd;
    poll->clients_[i].fd = -1;
    close(fd);
}

