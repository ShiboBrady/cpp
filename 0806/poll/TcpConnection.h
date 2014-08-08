#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H 

#include "NonCopyable.h"
#include "InetAddress.h"
#include "Socket.h"
#include "Rio.h"
#include <string>
#include <memory>

class TcpConnection;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

class TcpConnection : private NonCopyable
{
    public:
        explicit TcpConnection(int sockfd);
        ~TcpConnection();

        int fd() const
        { return sockfd_.fd();}

        ssize_t readn(char *usrbuf, size_t n);
        ssize_t readLine(char *usrbuf, size_t maxline);
        ssize_t writen(const char *usrbuf, size_t n);
        void send(const std::string &s);
        void shutdown();

    private:
        Socket sockfd_;  //fd
        Rio buffer_;     //该连接的读写缓冲区
};


#endif  /*TCP_CONNECTION_H*/

