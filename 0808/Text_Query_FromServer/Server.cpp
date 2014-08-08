#include "Server.h"
#include <iostream>
#include <sstream>
#include <string.h>
#include <strings.h>
#include <assert.h>
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
    pair<ClientsIterator, bool> result;
    result = clients_.insert(make_pair(conn->getFd(), new TextQuery()));
    assert(result.second);
    cout << "Client " << conn->getPeerAddr().getIp() << ":"
         << conn->getPeerAddr().getPort() << " is online." <<endl;
    string sendinfo("Please input a filename:\n");
    conn->send(sendinfo);
}

void Server::bussinessCallback(const TcpConnectionPtr &conn)
{
    string recvmsg = conn->receive();
    pool_.add_task(bind(&Server::calculate, this, recvmsg, conn));
}

void Server::closeCallback(const TcpConnectionPtr &conn)
{  
    ClientsIterator result = clients_.find(conn->getFd());
    assert(result != clients_.end());
    clients_.erase(result);
    cout << "Client " << conn->getPeerAddr().getIp() << ":"
         << conn->getPeerAddr().getPort() << " is offline." <<endl;
}

void Server::calculate(string word, const TcpConnectionPtr &conn)
{
    int fd = conn->getFd();
    trimEnter(word);
    if(!clients_[fd]->isStart()){
        ifstream in;
        if(!clients_[fd]->openfile(in, word)){
            string errinfo("File doesn't exist, please try again.\nPlease input a filename.\n");
            conn->send(errinfo);
        }else{
            clients_[fd]->readFile(word);
        }
    }
    else{
        string sendinfo;
        ostringstream os;
        char temp[1024] = {0};
        set<int> lines = clients_[fd]->query(word);
        set<int>::size_type size = lines.size();
        sprintf(temp, "Words %s occurs %u times\n", word.c_str(), size);
        sendinfo = string(temp);
        //os.clear();
        //os << "Words " << word << " occurs " << size << " times\n";
        //sendinfo = os.str();
        conn->send(sendinfo);
        for(set<int>::iterator it = lines.begin(); it != lines.end(); ++it){
            bzero(temp, 1024);
            sprintf(temp, "\t(line %u): %s\n", *it, clients_[fd]->readline(*it).c_str());
            sendinfo = string(temp);
            //os << "\t(line " << *it << " ): " << clients_[fd]->readline(*it) << "\n";
            //sendinfo = os.str();
            conn->send(sendinfo);
        }
    }
}

void Server::trimEnter(string &str)
{
    char temp[1024];
    bzero(temp, 1024);
    strcpy(temp, str.c_str());
    temp[strlen(temp) - 2] = 0;
    str = string(temp); 
}

void Server::start()
{
    server_.setOnlineCallback(bind(&Server::onlineCallback, this, _1));
    server_.setBussinessCallback(bind(&Server::bussinessCallback, this, _1));
    server_.setCloseCallback(bind(&Server::closeCallback, this, _1));

    server_.start();
}
