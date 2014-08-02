#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int do_server(int fd_client)
{
    fd_set fd_info;
    int fd_stdin = fileno(stdin);
    int maxfd = (fd_client > fd_stdin) ? (fd_client) : (fd_stdin);
    int rtn_select, rtn_read;
    char recvbuf[1024];
    char sendbuf[1024];
    while(1){
        FD_ZERO(&fd_info);
        FD_SET(fd_stdin, &fd_info);
        FD_SET(fd_client, &fd_info);
        rtn_select = select(maxfd + 1, &fd_info, NULL, NULL, NULL);
        if(rtn_select == -1){
            if(errno == EINTR)
                continue;
            ERR_EXIT("select");
        }else if(rtn_select == 0){
            return;
        }else{
            if(FD_ISSET(fd_stdin, &fd_info)){
                fgets(sendbuf, 1024, stdin);
                writen(fd_client, sendbuf, strlen(sendbuf));
            }            
            if(FD_ISSET(fd_client, &fd_info)){
                rtn_read = readline(fd, recvbuf, 1024);
                if(rtn_read == -1)
                    ERR_EXIT("read");
                else if(rtn_read == 0)
                    return;
                else
                    printf("receive message:%s", recvbuf);
            }
        }
        
    }
}
