#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    int fd = open("1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    FILE *fp = fdopen(fd, "w");
    char buf[1024] = "Shen Zhen long hua gong zhi long.";
    fwrite(buf, 1, strlen(buf), fp);
    return 0;
}
