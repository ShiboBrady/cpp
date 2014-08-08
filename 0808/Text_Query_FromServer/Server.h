#ifndef SERVER_H_
#define SERVER_H_ 

#include "TextQuery.h"
#include <echo/TcpServer.h>
#include <echo/Threadpool.h>
#include <echo/NonCopyable.h>
#include <string>
#include <unordered_map>

class Server : NonCopyable
{
    public:
        typedef std::shared_ptr<TextQuery> TextQueryPtr;
        typedef std::unordered_map<int, TextQueryPtr>::iterator ClientsIterator;
        Server(int port);
        ~Server();
        void start();
    private:
        void onlineCallback(const TcpConnectionPtr &conn);
        void bussinessCallback(const TcpConnectionPtr &conn);
        void closeCallback(const TcpConnectionPtr &conn);

        void calculate(std::string str, const TcpConnectionPtr &conn);
        void trimEnter(std::string &str);
        TcpServer server_;
        Threadpool pool_;
        std::unordered_map<int, TextQueryPtr> clients_;

};
#endif  /*TCP_SERVER_H_*/



