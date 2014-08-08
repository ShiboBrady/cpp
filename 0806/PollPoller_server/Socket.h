#ifndef SOCKET_H
#define SOCKET_H 
#include "Copyable.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

class Socket : Copyable
{
    public:
        explicit Socket(int fd):fd_(fd){}
        void setsockopt();
        void bind(struct sockaddr_in &addr);
        void listen();
        int accept();
        void setFd(int fd) {fd_ = fd; }
        int getFd() {return fd_; }
        void shutdown(){::shutdown(fd_, SHUT_WR); }
    private:
        int fd_;
};


inline void Socket::setsockopt()
{
    int reuse = 1;
    if(-1 == ::setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &reuse, static_cast<socklen_t>(sizeof(reuse)))) 
        ERR_EXIT("setsockopt");
}

inline void Socket::bind(struct sockaddr_in &addr)
{
    if(-1 == ::bind(fd_, (struct sockaddr*)&addr, sizeof(addr)))
        ERR_EXIT("bind");
}

inline void Socket::listen()
{
    if(-1 == ::listen(fd_, SOMAXCONN))
        ERR_EXIT("listen");
}

inline int Socket::accept()
{
    int fd_client;
    struct sockaddr_in client_addr;
    socklen_t addrlen = sizeof(client_addr);
    if(-1 == ::accept(fd_, (struct sockaddr*)&client_addr, &addrlen))
        ERR_EXIT("accept");
    return fd_client;
}


#endif  /*SOCKET_H*/
