#include "select_t.h"
#include "network.h"
#include <stdexcept>
#include <iostream>
#include <functional>
#include <errno.h>

using namespace std;

Select_t::Select_t(int fd, funcp fp)
    :listenfd_(fd),
     fp_(fp)
{
    for(int i = 0; i < FD_SETSIZE; ++i)
        clients_[i] = -1;
    FD_ZERO(&fset_);
    FD_ZERO(&fset_bkp_);
    FD_SET(listenfd_, &fset_bkp_);
    maxi_ = -1;
    maxfd_ = listenfd_;
    nready_ = 0;
}

void Select_t::select_wait()
{
    fset_ = fset_bkp_;
    do{
        nready_ = select(maxfd_ + 1, &fset_, NULL, NULL, NULL);
    }while((nready_ == -1 && errno == EINTR) || nready_ == 0);
    if(nready_ == -1)
        throw runtime_error("select");
}

void Select_t::select_handle_accept()
{
    if(FD_ISSET(listenfd_, &fset_)){
        SA client_addr;
        socklen_t addrlen = sizeof(client_addr);
        int fd_client = accept(listenfd_, (struct sockaddr*)&client_addr, &addrlen);
        if(fd_client == -1)
            throw runtime_error("accept");
        cout << "Client " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << " is online." << endl;
        
        select_add_fd(fd_client);
        --nready_;
    } 
}

void Select_t::select_handle_data()
{
    char recvbuf[1024] = {0};
    for(int i = 0; i <= maxi_; ++i){
        if(nready_ == 0)
            break;
        int fd = clients_[i];
        if(fd != -1 && FD_ISSET(fd, &fset_)){
            bzero(recvbuf, 1024);
            int nread = readline(fd, recvbuf, 1024);
            if(nread == -1)
                ERR_EXIT("readline");
            else if(nread == 0){
                cout << "One client is offline." << endl;
                select_del_fd(i);
                --nready_;
                continue;
            }

            fp_(fd, recvbuf);
            --nready_;
        }
    }
}

void Select_t::select_add_fd(int fd)
{
    int i;
    for(i = 0; i < FD_SETSIZE; ++i){
        if(clients_[i] == -1){
            clients_[i] = fd;
            if(maxi_ < i)
                maxi_ = i;
            break;
        }
    }

    if(i == FD_SETSIZE){
        fprintf(stderr, "Too much client.\n");
        exit(EXIT_FAILURE);
    }

    FD_SET(fd, &fset_bkp_);
    if(fd > maxfd_)
        maxfd_ = fd;
}

void Select_t::select_del_fd(int i)
{
    close(clients_[i]);
    FD_CLR(clients_[i], &fset_bkp_);
    clients_[i] = -1;
}
