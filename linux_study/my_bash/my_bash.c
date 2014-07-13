#include "bash.h"
#define INFO "[shibo @localhost ~]"

int main(int argc, const char *argv[])
{
    char cmd_line[100];
    char **cmd;
    pid_t pid;
    int irst;
    while(1){
        printf("%s ", INFO);
        fgets(cmd_line, 100, stdin);
        del_space(cmd_line);
        cmd_parse(cmd_line, &cmd);
        pid = fork();
        if(pid > 0){
            wait(NULL);
        }
        else{
            irst = execvp(cmd[0], cmd);
            if(irst == -1){
                fprintf(stderr, "-my_bash:%s:command not found.\n", cmd[0]);
            }
        }
    }    
    return 0;
}
