#ifndef EPOLLPOLLER_H
#define EPOLLPOLLER_H 
#include "Poller.h"
#include <sys/epoll.h>

class EpollPoller : public Poller
{
    public:
        EpollPoller(int listenfd, serverCallback func);
        ~EpollPoller();
        void wait();
        void handle();
    private:
        void handle_accept();
        void handle_data(int fd);
        void add_fd(int fd);
        void del_fd(int fd);

        struct epoll_event clients_[2048];
        int epollfd_;
};

#endif  /*EPOLLPOLLER_H*/
