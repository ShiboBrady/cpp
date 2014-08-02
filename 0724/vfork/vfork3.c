#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

    int val = 1;
int main(int argc, const char *argv[])
{
    //int val = 1;
    pid_t pid = vfork();
    if(pid == -1)
        ERR_EXIT("vfork");
    else if(pid > 0){
        sleep(1);
        val++;
        printf("In parent, val = %d\n", val);
    }else{
        sleep(1);
        val++;
        printf("In child, val = %d\n", val);
        _exit(0);
    }
    return 0;
}
