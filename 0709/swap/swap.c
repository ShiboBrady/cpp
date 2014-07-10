#include <stdio.h>

void swap(int **a, int **b)
{
    int *temp = *a;
    *a = *b;
    *b = temp;
}
int main()
{
    int i, j;
    i = 3; 
    j = 4;
    int *a = &i;
    int *b = &j;
    printf("Before swap: *a = %d, *b = %d\n", *a, *b);
    swap(&a, &b);
    printf(" After swap: *a = %d, *b = %d\n", *a, *b);
    return 0;
}
