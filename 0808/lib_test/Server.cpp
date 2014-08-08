#include "Server.h"
#include <iostream>
using namespace std;
using namespace std::placeholders;

Server::Server(int port)
    :server_(port),
     pool_(100, 10)
{
    pool_.start();
}

Server::~Server()
{
    pool_.stop();
}

void Server::onlineCallback(const TcpConnectionPtr &conn)
{

    conn->writen("Hello\r\n", 7);
    cout << "Client " << conn->getPeerAddr().getIp() << ":"
         << conn->getPeerAddr().getPort() << " is online." <<endl;
}

void Server::bussinessCallback(const TcpConnectionPtr &conn)
{
    string str;
    str = conn->receive();
    pool_.add_task(bind(&Server::calculate, this, str, conn));
}

void Server::closeCallback(const TcpConnectionPtr &conn)
{  
    cout << "Client " << conn->getPeerAddr().getIp() << ":"
         << conn->getPeerAddr().getPort() << " is offline." <<endl;
}

void Server::calculate(const string &str, const TcpConnectionPtr &conn)
{
    cout << "Recv msg: " << str;
    conn->send(str);
}

void Server::start()
{
    server_.setOnlineCallback(bind(&Server::onlineCallback, this, _1));
    server_.setBussinessCallback(bind(&Server::bussinessCallback, this, _1));
    server_.setCloseCallback(bind(&Server::closeCallback, this, _1));

    server_.start();
}
