#include "PollPoller.h"
#include "Socket.h"
#include "InetAddress.h"
#include <iostream>
#include <string.h>
using namespace std;

void onConnect(const TcpConnectionPtr &conn)
{
    conn->writen("Hello\r\n", 7);    
}

void onMessage(const TcpConnectionPtr &conn)
{
    char recvbuf[1024] = {0};
    conn->readLine(recvbuf, 1024);
    conn->writen(recvbuf, strlen(recvbuf));
}

void onClose(const TcpConnectionPtr &conn)
{
    //conn->writen("Bye\r\n", 5);
}

int main(int argc, const char *argv[])
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1)
        ERR_EXIT("socket");
    Socket my_socket(listenfd);
    my_socket.setsockopt();
    my_socket.bind(InetAddress(9999).getInetAddress());
    my_socket.listen();
    
    PollPoller my_poll(listenfd);
    my_poll.setOnlineCallback(&onConnect);
    my_poll.setBussinessCallback(&onMessage);
    my_poll.setCloseCallback(&onClose);
    while(1){
        my_poll.wait();
        my_poll.handle();
    }

    return 0;
}
