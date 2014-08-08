#include "TcpConnection.h"
#include "Socket.h"
#include <iostream>
#include <string>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
using namespace std;

int preprocess();

int main(int argc, const char *argv[])
{
    int listenfd;
    if(-1 == (listenfd = socket(PF_INET, SOCK_STREAM, 0)))
        ERR_EXIT("socket");
    Socket socket(listenfd);
    socket.setReusePort();
    socket.bindAddress(*InetAddress(9999).getSockAddrInet());
    socket.listen();
    listenfd = socket.fd();
    int fd_client = socket.accept();
    TcpConnection conn(fd_client);
    char recvbuf[1024] = {0};
    while(1){
        int nread = conn.readLine(recvbuf, 1024);
        if(nread == -1)
            ERR_EXIT("readline");
        else if(nread == 0)
            break;
        printf("recv msg: %s", recvbuf);
        conn.writen(recvbuf, strlen(recvbuf));
    }
    return 0;
}

