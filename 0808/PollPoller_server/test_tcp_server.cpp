#include "TcpServer.h"
#include "Threadpool.h"
#include <iostream>
#include <string.h>
using namespace std;

Threadpool pool(50, 10);

void computer(char *recvbuf, const TcpConnectionPtr &conn)
{
    cout << "Recv msg: " << recvbuf << endl;
    conn->writen(recvbuf, strlen(recvbuf));
}

void onConnect(const TcpConnectionPtr &conn)
{
    cout << "Client " << conn->getPeerAddr().getIp() << ":" << conn->getPeerAddr().getPort() << " is online." << endl;
    conn->writen("Hello\r\n", 7);    
}

void onMessage(const TcpConnectionPtr &conn)
{
    char recvbuf[1024] = {0};
    conn->readLine(recvbuf, 1024);
    pool.add_task(bind(&computer, recvbuf, conn));
}

void onClose(const TcpConnectionPtr &conn)
{
    //conn->writen("Bye\r\n", 5);
    cout << "Client " << conn->getPeerAddr().getIp() << ":" << conn->getPeerAddr().getPort() << " is offline." << endl;
    
}

int main(int argc, const char *argv[])
{
    pool.start();
    TcpServer server(9999);
    server.setOnlineCallback(&onConnect);
    server.setBussinessCallback(&onMessage);
    server.setCloseCallback(&onClose);
    server.start();
    pool.stop();
    return 0;
}
