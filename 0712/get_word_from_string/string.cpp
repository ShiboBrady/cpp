#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

ifstream &open_file(ifstream &is, const string &filename){
    is.close();
    is.clear();
    is.open(filename.c_str());
    return is;
}

int main(int argc, const char *argv[])
{
    ifstream in;
    string infile = "in.txt";
    if(!open_file(in, infile)){
        throw std::runtime_error("file open failed!");
    }

    vector<string> lines;
    string line;
    vector<string> words;
    while(getline(in, line)){
        lines.push_back(line);
        lines.istringstream
        istringstream ss(line);
        string word;
        while(ss >> word){
            words.push_back(word);
        }
    }
    return 0;
}

