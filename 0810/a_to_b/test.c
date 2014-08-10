#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10
void print(int *a)
{
    int i;
    for(i = 0; i < N; ++i)
        printf("%d ", a[i]);
    printf("\n");
}

int main(int argc, const char *argv[])
{
    int A[N], B[N];
    int i;
    srand(time(NULL));
    for(i = 0; i < N; ++i)
        A[i] = rand() % 10;

    printf("Array A:\n");
    print(A);

    for(i = N-1; i >= 0; --i){
        if(i == N-1)
            B[i] = A[i];
        else if(i == 0)
            B[i] = B[i+1]; 
        else
            B[i] = A[i] * B[i+1];
    }

    for(i = 1; i < N; ++i){
        if(i == N-1){
            B[i] = A[0];
            continue;
        }
        B[i] = A[0] * B[i+1];
        A[0] *= A[i];
    }
    printf("Array B:\n");
    print(B);
    return 0;
}
