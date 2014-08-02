#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, const char *argv[])
{
    int fd = open("1.txt", O_RDONLY);
    char buf[1024];
    bzero(buf, 1024);
    read(fd, buf, 5);
    off_t len = lseek(fd, 0, SEEK_CUR);
    printf("%d\n", (int)len);
    return 0;
}
