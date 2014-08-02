#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(void)
{
    pid_t pid;
    int cnt = 0;
    pid = vfork();
    if(pid == -1)
        ERR_EXIT("vfork");
    else if(pid > 0){
        cnt ++;
        printf("In parent, val = %d, my pid is %d\n", cnt, getpid());
    }
    else{
        //execl("/bin/ps", "ps", "ax", NULL);
        //exit(0);
        while(1){
        sleep(1);
        cnt ++;
        printf("In child, val = %d, my pid is %d\n", cnt, getpid());}
        exit(0);
    }
    return 0;
}
