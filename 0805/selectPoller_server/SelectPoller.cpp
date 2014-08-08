#include "SelectPoller.h"
#include <stdexcept>
#include <iostream>
using namespace std;

SelectPoller::SelectPoller(int listenfd, serverCallback func)
    :Poller(listenfd, func)
{
    FD_ZERO(&fset_);    
    FD_ZERO(&fset_bkp_);
    FD_SET(listenfd_, &fset_bkp_);
    
    for(int i = 0; i < FD_SETSIZE; ++i)
        clients_[i] = -1;

    maxi_ = -1;
    maxfd_ = listenfd_;
}     

SelectPoller::~SelectPoller()
{
    close(listenfd_);
}


void SelectPoller::wait()
{
    fset_ = fset_bkp_;
    do{
        nready_ = select(maxfd_ + 1, &fset_, NULL, NULL, NULL);
    }while(nready_ == -1 && errno == EINTR);
    if(nready_ == -1)
        throw runtime_error("select");
}

void SelectPoller::handle()
{
    handle_accept();
    handle_data();
}

void SelectPoller::handle_accept()
{
    SA client_addr;
    socklen_t addrlen = sizeof(client_addr);
    if(FD_ISSET(listenfd_, &fset_)){
        int fd_client = accept(listenfd_, (struct sockaddr*)&client_addr, &addrlen);
        if(fd_client == -1)
            throw runtime_error("accpet");
        cout << "Client " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << " is online." << endl;
        add_fd(fd_client);
        --nready_;
    }
}

void SelectPoller::handle_data()
{
    for(int i = 0; i <= maxi_; ++i){
        if(nready_ == 0)
            break;
        int fd = clients_[i];
        if(fd != -1 && FD_ISSET(fd, &fset_)){
              char recvbuf[1024] = {0};
              int nread = readline(fd, recvbuf, 1024);
              if(nread == -1)
                  throw runtime_error("readline");
              else if(nread == 0){
                   del_fd(i);
                   --nready_;
                   continue;
              }
              func_(fd, recvbuf);
              --nready_;
        }
    }
}

void SelectPoller::add_fd(int fd)
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

    if(i == FD_SETSIZE)
        throw runtime_error("Too much clients.");

    FD_SET(fd, &fset_bkp_);
    if(fd > maxfd_)
        maxfd_ = fd;
}

void SelectPoller::del_fd(int i)
{
    close(clients_[i]);
    FD_CLR(clients_[i], &fset_bkp_);
    clients_[i] = -1;
    cout << "One client is offline." << endl;
}

/*
void SelectPoller::setfd()
{
    FD_SET(listenfd_, &fset_bkp_);
    maxfd_ = listenfd_;
}
*/
