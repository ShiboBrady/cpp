#include <iostream>
#include <string>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

using namespace std;

void handler(int signum)
{
    cout << signum << endl; 
}

int main(int argc, const char *argv[])
{
    if(signal(SIGALRM, handler) == SIG_ERR) 
        ERR_EXIT("signal");
    
    alarm(1);
    while(1);
    return 0;
}
