#ifndef SELECTPOLLER_H
#define SELECTPOLLER_H

#include "Poller.h"
#include <sys/select.h>
#include <errno.h>

class SelectPoller : public Poller
{
    public:
        SelectPoller(int listenfd, serverCallback func);
        ~SelectPoller();
        void wait();
        void handle();
    private:
        void handle_accept();
        void handle_data();
        void add_fd(int fd);
        void del_fd(int i);

        fd_set fset_;
        fd_set fset_bkp_;
        int clients_[FD_SETSIZE];
        int maxi_;
        int maxfd_;
};

#endif  /*POLLER_H*/

