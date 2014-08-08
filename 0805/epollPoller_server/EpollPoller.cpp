#include "EpollPoller.h"
#include <iostream>
#include <stdexcept>
using namespace std;

EpollPoller::EpollPoller(int listenfd, serverCallback func)
    :Poller(listenfd, func)
{
    epollfd_ = epoll_create(2048);
    add_fd(listenfd_);
}

EpollPoller::~EpollPoller()
{
    close(epollfd_);
    close(listenfd_);
}

void EpollPoller::wait()
{
    do{
        nready_ = epoll_wait(epollfd_, clients_, 2048, -1); 
    }while(nready_ == -1 && errno == EINTR);
    if(nready_ == -1)
        throw runtime_error("epoll_wait");
}

void EpollPoller::handle()
{
    for(int i = 0; i < nready_; ++i){
        if(listenfd_ == clients_[i].data.fd)
            handle_accept();
        else
            handle_data(clients_[i].data.fd);
    } 
}

void EpollPoller::handle_accept()
{
    SA client_addr;
    socklen_t addrlen = sizeof(client_addr);
    int fd_client = accept(listenfd_, (struct sockaddr*)&client_addr, &addrlen);
    if(fd_client == -1)
        throw runtime_error("accept");
    cout << "Client " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << " is online." << endl;
    add_fd(fd_client);
}

void EpollPoller::handle_data(int fd)
{
    char recvbuf[1024] = {0};
    int nread = readline(fd, recvbuf, 1024);
    if(nread == -1)
        throw runtime_error("readline");
    else if(nread == 0){
        del_fd(fd);
        return;
    }
    func_(fd, recvbuf);
}

void EpollPoller::add_fd(int fd)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if(-1 == epoll_ctl(epollfd_, EPOLL_CTL_ADD, fd, &ev))
        throw runtime_error("epoll_ctl");
}

void EpollPoller::del_fd(int fd)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if(-1 == epoll_ctl(epollfd_, EPOLL_CTL_DEL, fd, &ev))
        throw runtime_error("epoll_ctl");
    cout << "One client is offline." << endl;
}
