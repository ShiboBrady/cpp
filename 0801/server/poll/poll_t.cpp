#include "poll_t.h"
#include "network.h"
#include <stdexcept>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

Poll_t::Poll_t(int fd, funcp func)
    :listenfd_(fd),
     func_(func),
     maxi_(0),
     nready_(0)
{
    clients_[0].fd = fd;
    clients_[0].events = POLLIN;
    for(int i = 1; i < 2048; ++i)
        clients_[i].fd = -1;
}

void Poll_t::poll_wait()
{
    do{
        nready_ = poll(clients_, maxi_ + 1, -1);
    }while(nready_ == -1 && errno == EINTR);
    if(nready_ == -1)
        throw runtime_error("poll");
}

void Poll_t::poll_handle_accept()
{
    if(clients_[0].revents & POLLIN){
        int fd_client;
        SA client_addr;
        socklen_t addrlen = sizeof(client_addr);
        if(-1 == (fd_client = accept(listenfd_, (struct sockaddr*)&client_addr, &addrlen)))
            throw runtime_error("accept");
        cout << "Client " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << " is online." << endl;
        poll_add_fd(fd_client);
        --nready_;
    }
}

void Poll_t::poll_handle_data()
{
    int fd;
    int nread;
    char recvbuf[1024] = {0};
    for(int i = 0; i <= maxi_; ++i){
        fd = clients_[i].fd;
        if(nready_ == 0)
            break;
        if(fd != -1 && (clients_[i].revents & POLLIN)){
            bzero(recvbuf, 1024);
            nread = readline(fd, recvbuf, 1024);
            if(nread == -1)
                throw runtime_error("readline");
            else if(nread == 0){
                poll_del_fd(i);
                --nready_;
                continue;
            }
            cout << recvbuf << endl;
            func_(fd, recvbuf);
            --nready_;
        }
    }
}

void Poll_t::poll_add_fd(int fd)
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
    if(i == 2048){
        cout << "Too many clients." << endl;
        throw runtime_error("Too many clients.");
    }
}

void Poll_t::poll_del_fd(int i)
{
    close(clients_[i].fd);
    clients_[i].fd = -1;
    cout << "One client is offline." << endl;
}
