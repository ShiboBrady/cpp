#include "network.h"
#include "epoll_t.h"
#include <stdexcept>
#include <iostream>

using namespace std;

Epoll_t::Epoll_t(int fd, funcp func)
    :listenfd_(fd),
     nready_(0),
     func_(func)
{
    epollfd_ = epoll_create(2048);
    if(epollfd_ == -1)
        throw runtime_error("epoll_create");
    epoll_add_fd(fd);
}

Epoll_t::~Epoll_t()
{
    close(epollfd_);
}

void Epoll_t::epoll_wait_signal()
{
    do{
        nready_ = epoll_wait(epollfd_, events_, 2048, -1);
    }while(nready_ == -1 && errno == EINTR);
    if(nready_ == -1)
        throw runtime_error("epoll_wait");
}

void Epoll_t::epoll_handle()
{
    for(int i = 0; i < nready_ ;++i){
        if(listenfd_ == events_[i].data.fd)
            epoll_handle_accept();
        else
            epoll_handle_data(events_[i].data.fd);
    }
}

void Epoll_t::epoll_handle_accept()
{
    SA client_addr;
    socklen_t addrlen = sizeof(client_addr);
    int fd_client;
    if(-1 == (fd_client = accept(listenfd_, (struct sockaddr*)&client_addr, &addrlen)))
        throw runtime_error("accept");
    cout << "Client " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << " is online." << endl;
    epoll_add_fd(fd_client);
}

void Epoll_t::epoll_handle_data(int fd)
{
    char recvbuf[1024] = {0};
    int nread = readline(fd, recvbuf, 1024);
    if(nread == -1)
        throw runtime_error("readline");
    else if(nread == 0){
        epoll_del_fd(fd);
        return;
    }
    func_(fd, recvbuf);
}

void Epoll_t::epoll_add_fd(int fd)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if(-1 == epoll_ctl(epollfd_, EPOLL_CTL_ADD, fd, &ev))
        ERR_EXIT("epoll_ctl");
}

void Epoll_t::epoll_del_fd(int fd)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    if(-1 == epoll_ctl(epollfd_, EPOLL_CTL_DEL, fd, &ev))
        ERR_EXIT("epoll_ctl");
    cout << "One client is offline." << endl;
}
