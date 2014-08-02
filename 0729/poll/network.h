#ifndef NETWORK_H
#define NETWORK_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

typedef struct sockaddr_in SA;

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

ssize_t readn(int fd, char *buf, size_t n);
ssize_t writen(int fd, char *buf, size_t n);
ssize_t recv_peek(int sockfd, char *buf, size_t n);
ssize_t readline(int sockfd, char *buf, size_t n);

#endif  /*NETWORK_H*/
