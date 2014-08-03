#ifndef SELECT_T_H
#define SELECT_T_H 
#include <functional>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string>
typedef struct sockaddr_in SA;

class Select_t
{
    public:
        typedef std::function<void (int, char *)> funcp;
        Select_t(int listenfd, funcp fp);
        void select_wait();
        void select_handle_accept();
        void select_handle_data();
    private:
        fd_set fset_;
        fd_set fset_bkp_;
        int listenfd_;
        int clients_[FD_SETSIZE];
        int nready_;
        int maxi_;
        int maxfd_;
        funcp fp_;

        void select_add_fd(int fd);
        void select_del_fd(int i);
};

#endif  /*SELECT_T_H*/
