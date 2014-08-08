#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char x[10] = "backeopsl";
char y[10] = "amnopcskl";
int bkp[20][20];

int LCS(int i, int j)
{
    int a, b;
    if(i == 0 || j == 0)
        return 0;
    else if(x[i - 1] == y[j - 1]){
        return LCS(i - 1, j - 1) + 1;
    }
    else{
         
        return (a = LCS(i, j - 1)) > (b = LCS(i - 1, j)) ? a : b;
    }
}

void makeLCS(char *str1, char *str2, int (*lcs)[20])
{
    int i, j;
    int m = strlen(str1);
    int n = strlen(str2);
    memset(lcs, 0, sizeof(int) * 20 * 20);
    for(i = 1; i <= m; ++i)
        for(j = 1; j <= n; ++j){
            if(str1[i-1] == str2[j-1])
                lcs[i][j] = lcs[i-1][j-1] + 1;
            else
                lcs[i][j] = (lcs[i][j-1] > lcs[i-1][j] ? lcs[i][j-1] : lcs[i-1][j]);
        }
    for(i = 1; i <= m; ++i){
        for(j = 1; j <= n; ++j)
            printf("%d ", lcs[i][j]);
        printf("\n");
    }
}

void printLCS()
{
     
}

int main(int argc, const char *argv[])
{
    //int len = LCS(9, 9);
    //printf("len = %d\n", len);
    int lcs[20][20];
    char str1[] = "BDCABA";
    char str2[] = "ABCBDAB";
    makeLCS(str1, str2, lcs);
    printLCS();
    return 0;
}
