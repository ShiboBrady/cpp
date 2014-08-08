#ifndef POLLER_H
#define POLLER_H 
#include <functional>
#include "network.h"
#include <stdexcept>

typedef struct sockaddr_in SA;

class Poller
{
    public:
        typedef std::function<void (int, char*)> serverCallback;
        
        Poller(int listenfd, serverCallback func)
            :listenfd_(listenfd),
             nready_(0),
             func_(func){}
        ~Poller(){}
        
        virtual void wait() = 0;
        virtual void handle() = 0;
    protected:
        /*
        virtual void handle_accept() = 0;
        virtual void handle_data() = 0;
        virtual void add_fd(int fd) = 0;
        virtual void del_fd(int fd) = 0;
        */
        int listenfd_;
        int nready_;
        serverCallback func_;
};


#endif  /*POLLER_H*/
