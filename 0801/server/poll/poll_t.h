#ifndef POLL_H
#define POLL_H 

#include <poll.h>
#include <functional>

class Poll_t
{
    public:
        typedef std::function<void (int, char *)> funcp;
        Poll_t(int listenfd, funcp func);
        void poll_wait();
        void poll_handle_accept();
        void poll_handle_data();
    private:
        void poll_add_fd(int fd);
        void poll_del_fd(int i);

        int listenfd_;
        funcp func_;
        int maxi_;
        int nready_;
        struct pollfd clients_[2048];
};

#endif  /*POLL_H*/
