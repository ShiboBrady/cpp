#include "Server.h"
#include <iostream>
#include <string>
#include <string.h>
using namespace std;
using namespace std::placeholders;

Server::Server(int port, const string &filename)
    :server_(port),
     search_(filename),
     pool_(1000, 5)
{
    server_.setOnlineCallback(bind(&Server::onlineCallback, this, _1));
    server_.setBussinessCallback(bind(&Server::bussinessCallback, this, _1));
    server_.setCloseCallback(bind(&Server::closeCallback, this, _1));
    timer_.setTime(3, 3);
    timer_.setFunc(bind(&Search::writeCacheFile, &search_));
}

Server::~Server()
{
    pool_.stop();
    timer_.stop();
}

void Server::start()
{
    timer_.start();
    pool_.start();
    server_.start();
}

void Server::onlineCallback(const TcpConnectionPtr &conn)
{
    cout << "Client " << conn->getPeerAddr().getIp() << ":"
         << conn->getPeerAddr().getPort() << " is online." << endl;
    conn->send("Input a word to query.\r\n");
}

void Server::bussinessCallback(const TcpConnectionPtr &conn)
{
    string word = conn->receive();
    pool_.add_task(bind(&Server::computer, this, word, conn));
}

void Server::closeCallback(const TcpConnectionPtr &conn)
{ 
    cout << "Client " << conn->getPeerAddr().getIp() << ":"
         << conn->getPeerAddr().getPort() << " is offline." << endl;
}

void Server::trimSpace(string &word)
{
    char temp[200] = {0};
    strcpy(temp, word.c_str());
    temp[strlen(temp) - 2] = 0;
    word = string(temp);
}

void Server::computer(const string &usrword, const TcpConnectionPtr &conn)
{
    string word = usrword;
    trimSpace(word);
    string result = search_.query(word);
    result += "\n";
    conn->send(result);
}
