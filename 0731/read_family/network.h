#ifndef NETWORK_H
#define NETWORK_H 

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
typedef struct sockaddr_in SA;

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

ssize_t readn(int fd, char *buf, size_t len);
ssize_t writen(int fd, char *buf, size_t len);
ssize_t recv_peek(int sockfd, char *buf, size_t len);
ssize_t readline(int sockfd, char *buf, size_t len);

#endif  /*NETWORK_H*/
