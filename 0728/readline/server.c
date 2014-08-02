#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

void preprocess(int *fd_server)
{
   int reuse = 1;
   struct sockaddr_in server_addr;
   int addrlen = sizeof(server_addr);
   
   if(-1 == (fd_server = socket(PF_INET, SOCK_STREAM, 0)))
       ERR_EXIT("socket");

   if(-1 == setsockopt(fd_server, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)))
       ERR_EXIT("setsockopt");

   bzero(&server_addr, addrlen);
   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htonl(9999);
   server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

   if(-1 == bind(fd_server, (struct sockaddr*)&server_addr, addrlen))
       ERR_EXIT("bind");
   
   if(-1 == listen(fd_server, SOMAXCONN))
       ERR_EXIT("listen");
}

void do_server(int fd_client)
{
    char recvbuf[1024] = {0};
    int ret;
    while(1){
        ret = readline(fd_client, recvbuf, 1024);
        if(ret == 0)
            break;
        writen(fd_client, recvbuf, strlen(recvbuf));
        bzero(&recvbuf, sizeof(recvbuf));
    }
}

int main(int argc, const char *argv[])
{
    int fd_server, fd_client;
    int reuse = 1; 
    struct sockaddr_in client_addr;
    int addrlen = sizeof(client_addr);

    preprocess(&fd_server);

    if((fd_client = accept(fd_server, (struct sockaddr*)&client_addr, &addrlen)) == -1)
        ERR_EXIT("accept");

    do_service(fd_client);

    close(fd_client);
    close(fd_server);
   
    return 0;
}
