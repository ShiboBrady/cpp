#include "Search.h"
#include <string>
#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
    Search search("out.txt");
    string word;
    while(cin >> word){
        cout << search.query(word) << endl;
    }
    return 0;
}
