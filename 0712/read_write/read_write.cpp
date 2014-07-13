#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, const char *argv[])
{
    ifstream ios;
    ofstream oos;
    ios.open("in.txt");
    oos.open("out.txt");
    
    string line;

    while(ios >> line){
        oos << line << " ";
    }
    oos << endl;
    
    ios.close();
    oos.close();
    return 0;
}
