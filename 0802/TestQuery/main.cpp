#include "TextQuery.h"
#include <iostream>

using namespace std;
int main(int argc, const char *argv[])
{
    string filename;
    cout << "Enter you filename: " << endl;
    cin >> filename;
    TextQuery tq;
    tq.readFile(filename);
    while(true){
        cout << "enter a word to query:" << endl;
        string s;
        cin >> s;
        if(!cin || s == "q")
            break;
        set<int> lines = tq.query(s);
        tq.print(lines, s);
    }
    return 0;
}
