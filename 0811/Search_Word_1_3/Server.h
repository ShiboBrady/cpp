#ifndef SERVER_H
#define SERVER_H 

#include "Search.h"
#include <echo/TcpServer.h>
#include <echo/Threadpool.h>
#include <echo/ThreadTimer.h>
#include <echo/NonCopyable.h>
#include <string>

class Server : NonCopyable
{
    public:
        Server(int port, const std::string &storageFile, const std::string &cacheFile);
        ~Server();
        void start();

    private:
        void onlineCallback(const TcpConnectionPtr &conn);
        void bussinessCallback(const TcpConnectionPtr &conn);
        void closeCallback(const TcpConnectionPtr &conn);
        void trimSpace(std::string &word);
        void computer(const std::string &word, const TcpConnectionPtr &conn);

        TcpServer server_;
        Search search_;
        Threadpool pool_;
        ThreadTimer timer_;
};

#endif  /*SERVER_H*/
