#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
    if(argc != 2){
        fprintf(stderr, "usage: EXE filename\n");
        exit(1);
    }


    if(!freopen(argv[1], "r", stdin)){
        fprintf(stderr, "could not redirect stdin from file %s\n", argv[1]);
        exit(1);
    }

    execl("./upper", "upper", NULL, 0);

    perror("could not exec ./upper");
    return 0;
}
