#include "network.h"
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>


void preprocess(int *listenfd)
{
    SA server_addr;
    int reuse = 1;
    socklen_t addrlen = sizeof(server_addr);
    if(-1 == (*listenfd = socket(PF_INET, SOCK_STREAM, 0)))
        ERR_EXIT("socket");

    if(-1 == setsockopt(*listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)))
        ERR_EXIT("setsockopt");

    bzero(&server_addr, addrlen);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(-1 == bind(*listenfd, (struct sockaddr*)&server_addr, addrlen))
        ERR_EXIT("bind");

    if(-1 == listen(*listenfd, SOMAXCONN))
        ERR_EXIT("listen");
}

void do_service(int fd_client)
{
    char recvbuf[1024] = {0};
    while(1){
        int nread = readline(fd_client, recvbuf, 1024);
        if(nread == -1)
            ERR_EXIT("readline");
        else if(nread == 0){
            break;
        }
        printf("recv msg: %s", recvbuf);
        writen(fd_client, recvbuf, strlen(recvbuf));
    } 
}

void handler(int signum)
{
    pid_t pid;
    int status;
    while((pid = waitpid(-1, &status, WNOHANG)) > 0){
        if(WIFEXITED(status)){
            printf("Child %d terminated success, and exit value is %d.\n", pid, WEXITSTATUS(status));
        }else{
            printf("Child %d terminated abnormal.\n", pid);
        }
    }
}

int main(int argc, const char *argv[])
{
    if(signal(SIGCHLD, handler) == SIG_ERR)
        ERR_EXIT("signal");
    int fd_server, fd_client;
    SA client_addr;
    socklen_t addrlen = sizeof(client_addr);
    pid_t pid;

    preprocess(&fd_server);
    
    while(1){
        if(-1 == (fd_client = accept(fd_server, (struct sockaddr*)&client_addr, &addrlen)))
            ERR_EXIT("accept");
        if((pid = fork()) < 0)
            ERR_EXIT("fork");
        else if(pid == 0){
            close(fd_server);
            do_service(fd_client);
            exit(EXIT_SUCCESS);
        }

        close(fd_client);               
    }

    return 0;
}
