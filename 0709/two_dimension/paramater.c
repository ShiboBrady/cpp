#include <stdio.h>
#include <time.h>

#define M 10
#define N 10

typedef struct array
{
    int arr[M][N];
    int m;
    int n;
}Array;

void init_array_struct(Array *arr)
{
    srand(time(NULL));
    int i, j;
    for(i = 0; i < arr->m; ++i)
        for(j = 0; j < arr->n; ++j)
            arr->arr[i][j] = rand() % 100;
}

void print_array_struct(Array *arr)
{
    int i, j;
    for(i = 0; i < arr->m; ++i){
        for(j = 0; j < arr->n; ++j)
            printf("%d ", arr->arr[i][j]);
        printf("\n");
    }

}

void init_array_point(int *a, int m, int n)
{
    int i, j;
    srand(time(NULL));
    for(i = 0; i < m; ++i)
        for(j = 0; j < n; ++j)
            a[n * i + j] = rand() % 100;
}

void print_array_point(int *a, int m, int n)
{
    int i, j;
    for(i = 0; i < m; ++i){
        for(j = 0; j < n; ++j)
            printf("%d ", a[i * n + j]);
        printf("\n");
    }
}


int main()
{
    //Array arr;
    //arr.m = 3;
    //arr.n = 4;
    //init_array(&arr);
    //print_array(&arr);
    int a[3][4];
    init_array_point(*a, 3, 4);
    print_array_point(*a, 3, 4);
    return 0;
}
