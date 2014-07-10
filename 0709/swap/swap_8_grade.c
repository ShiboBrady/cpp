#include <stdio.h>

void swap(int *********a, int *********b)
{
    int ********temp = *a;
    *a = *b;
    *a = temp;
}

int main()
{
    
    int ********a, ********b;
    swap(&a, &b);
    printf("a = %d, b = %d\n", ********a, ********b);
    return 0;
}
