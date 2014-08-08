#include "PollPoller.h"
#include <assert.h>
#include <iostream>
#include <poll.h>
#include <stdexcept>

using namespace std;

PollPoller::PollPoller(int listenfd, serverCallback func)
    :Poller(listenfd, func)
{
    for(int i = 0; i < 2048; ++i)
        clients_[i].fd = -1;

    clients_[0].fd = listenfd_;
    clients_[0].events = POLLIN;
    maxi_ = 0;
}

PollPoller::~PollPoller()
{
    close(listenfd_);
}

void PollPoller::wait()
{
    do{
        nready_ = poll(clients_, maxi_ + 1, -1);
    }while(nready_ == -1 && errno == EINTR);
    if(nready_ == -1)
        throw runtime_error("poll");
}

void PollPoller::handle()
{
    handle_accept();
    handle_data();
}

void PollPoller::handle_accept()
{
    SA client_addr;
    socklen_t addrlen = sizeof(client_addr);
    if(clients_[0].revents & POLLIN){
        int fd_client = accept(listenfd_, (struct sockaddr*)&client_addr, &addrlen);
        if(fd_client == -1)
            throw runtime_error("accept");
        cout << "Client " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << " is online." << endl;
        add_fd(fd_client);
        --nready_;
    }
}

void PollPoller::handle_data()
{
    for(int i = 1; i <= maxi_; ++i){
        if(nready_ == 0)
            break;

        int fd = clients_[i].fd;
        if(fd != -1 && (clients_[i].revents & POLLIN)){
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

void PollPoller::add_fd(int fd)
{
    int i;
    for(i = 1; i < 2048; ++i){
        if(clients_[i].fd == -1){
            clients_[i].fd = fd;
            clients_[i].events = POLLIN;
            if(maxi_ < i)
                maxi_ = i;
            break;
        }
    }
    if(i == 2048)
        throw runtime_error("Too much clients.");
}

void PollPoller::del_fd(int i)
{
    assert(i >= 0 && i < 2048);
    close(clients_[i].fd);
    clients_[i].fd = -1;
    cout << "One client is offline." << endl;
}
