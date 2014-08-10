#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;

int backup[10][10];
int count = 0;

int med(const string &x, int i, const string &y, int j)
{
    count ++;
    if(i == 0)
        return j;
    if(j == 0)
        return i;
    if(x[i-1] == y[j-1])
        return  med(x, i-1, y, j-1);
    else{
        int a = med(x, i, y, j-1);
        int b = med(x, i-1, y, j);
        int c = med(x, i-1, y, j-1);
        int temp;
        return (((temp = (a < b ? a : b)) < c ? temp : c) + 1);
    }
}

int med1(const string &x, int i, const string &y, int j)
{
    if(backup[i][j] != -1)
        return backup[i][j];
    count ++;
    if(i == 0){
        backup[i][j] = j;
        return j;
    }
    if(j == 0){
        backup[i][j] = i;
        return i;
    }
    if(x[i-1] == y[j-1]){
        backup[i-1][j-1] = med1(x, i-1, y, j-1);
        return backup[i-1][j-1];
    }
    else{
        int a = med1(x, i, y, j-1) + 1;
        int b = med1(x, i-1, y, j) + 1;
        int c = med1(x, i-1, y, j-1) + 1;
        int temp;
        backup[i][j] = (temp = a < b ? a : b) < c ? temp : c;
        return temp;
    }
}

int med2(const string &x, int m, const string &y, int n)
{
    for(int i = 0; i <= n; ++i)
        backup[0][i] = i;
    for(int i = 0; i <= m; ++i)
        backup[i][0] = i;
    for(int i = 1; i <= m; ++i){
        for(int j = 1; j <= n; ++j){
            if(x[i-1] == y[j-1])
                backup[i][j] = backup[i-1][j-1];
            else{
                int a = backup[i-1][j];
                int b = backup[i][j-1];
                int c = backup[i-1][j-1];
                int temp;
                backup[i][j] = ((temp = a < b ? a : b) < c ? temp : c) + 1;
            }
        }
    }
    return backup[m][n];
}

void print(int (*arr)[10])
{
    for(int i = 0; i < 10; ++i){
        for(int j = 0; j < 10; ++j){
            printf("%2d ", arr[i][j]);
        }
        cout << endl;
    }
}

int main(int argc, const char *argv[])
{
    string x;
    string y;
    cout << "Input string one: ";
    cin >> x;
    cout << "Input string two: ";
    cin >> y;
    memset(backup, -1, sizeof(backup));
    int k = med2(x, x.size(), y, y.size());
    cout << "Minimum edit distance is: " << k << endl;
    cout << "Calculate times: " << count << endl;
    print(backup);
    return 0;
}
