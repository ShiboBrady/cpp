#ifndef EPOLL_T_H
#define EPOLL_T_H 

#include <sys/epoll.h>
#include <functional>

class Epoll_t
{
    public:
        typedef std::function<void (int, char *)> funcp;
        Epoll_t(int fd, funcp func);
        ~Epoll_t();
        void epoll_wait_signal();
        void epoll_handle();
        void epoll_handle_accept();
        void epoll_handle_data(int fd);
    private:
        void epoll_add_fd(int fd);
        void epoll_del_fd(int fd);

        int listenfd_;
        int nready_;
        funcp func_;
        int epollfd_;
        struct epoll_event events_[2048];

};

#endif  /*EPOLL_T_H*/
