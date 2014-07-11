#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <sstream>

using namespace std;

ifstream &open_file(ifstream &in, const string &filename)
{
    in.close();
    in.clear();
    in.open(filename.c_str());
    return in;
}

int main(int argc, const char *argv[])
{
    ifstream is;
    string filename = "1.txt";
    try{
        if(!open_file(is, filename)){
            throw runtime_error("file open fail");
        }
    }catch(runtime_error &e){
        cout << e.what() << endl;
    }
    
    vector<string> lines;
    vector<string> words;
    string line, word;
    istringstream iss;
    while(getline(is, line)){
        lines.push_back(line);
        iss.str(line);
        while(iss >> word){
            words.push_back(word);
        }
        iss.clear();

    }
    is.close();
    is.clear();

    for(vector<string>::iterator it = lines.begin(); it != lines.end(); ++it){
        cout << *it << endl;
    }

    for(vector<string>::iterator it = words.begin(); it != words.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}
