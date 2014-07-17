#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

void print(const map<string, int>::value_type &p)
{
    cout << p.first << " orrurs: " << p.second << " times" << endl;
}

ifstream &open_file(ifstream &os, const string &filename)
{
    os.close();
    os.clear();
    os.open(filename.c_str());
    return os;
}

int main(int argc, const char *argv[])
{
    map<string, int> word_count;
    string word;
    ifstream in;
    string filename = "in.txt";
    if(!(open_file(in, filename))){
        throw runtime_error("file open fail.");        
    }
    
    while(in >> word){
        word_count[word]++;
    }

    for_each(word_count.begin(), word_count.end(), print);
    in.close();
    in.clear();
    return 0;
}
