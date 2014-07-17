#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <fstream>
#include <stdexcept>

using namespace std;

void print(const map<string, int>::value_type &p)
{
    cout << p.first << " occurs: " << p.second << " times." << endl;
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
    pair<map<string, int>::iterator, bool> ret;
    string word;
    ifstream os;
    string filename = "in.txt";
    if(!(open_file(os, filename))){
        throw runtime_error("open file failed!");
    }

    while(os >> word){
        ret = word_count.insert(make_pair(word, 1));
        if(!ret.second){
            ++ret.first->second;
        }
    }

    for_each(word_count.begin(), word_count.end(), print);
    return 0;
}
