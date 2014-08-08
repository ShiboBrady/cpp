#ifndef SERVER_H_
#define SERVER_H_ 

#include <echo/TcpServer.h>
#include <echo/Threadpool.h>
#include <echo/NonCopyable.h>
#include <string>

class Server : NonCopyable
{
    public:
        Server(int port);
        ~Server();
        void start();
    private:
        void onlineCallback(const TcpConnectionPtr &conn);
        void bussinessCallback(const TcpConnectionPtr &conn);
        void closeCallback(const TcpConnectionPtr &conn);

        void calculate(const std::string &str, const TcpConnectionPtr &conn);
        TcpServer server_;
        Threadpool pool_;

};
#endif  /*TCP_SERVER_H_*/



