#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <dirent.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc, const char *argv[])
{
    DIR *dir = opendir(".");
    if(dir == NULL){
        ERR_EXIT("opendir");
    }

    struct dirent *file_info;
    while((file_info = readdir(dir)) != NULL){
        printf("%10s\t", file_info->d_name);
    }
    return 0;
}

