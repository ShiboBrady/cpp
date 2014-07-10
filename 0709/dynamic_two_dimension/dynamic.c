#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    int **arr, i;
    //allocation
    arr = (int **)malloc(3 * sizeof(int*));
    for(i = 0; i < 3; ++i)
        arr[i] = (int*)malloc(4 * sizeof(int));
    //free
    for(i = 0; i < 3; ++i)
        free(arr[i]);
    free(arr);
    return 0;
}
