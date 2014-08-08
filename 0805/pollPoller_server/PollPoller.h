#ifndef POLLPOLLER_H
#define POLLPOLLER_H 
#include "Poller.h"
#include <poll.h>


class PollPoller : public Poller
{
    public:
        PollPoller(int listenfd, serverCallback func);
        ~PollPoller();
        void wait();
        void handle();
    private:
        void handle_accept();
        void handle_data();
        void add_fd(int fd);
        void del_fd(int i);

        struct pollfd clients_[2048];
        int maxi_;
};

#endif  /*POLLPOLLER_H*/
