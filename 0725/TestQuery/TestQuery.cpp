#include "TextQuery.h"
#include <stdexcept>
#include <sstream>

void TextQuery::readFile(const string &filename)
{
    ifstream in;
    if(!openfile(in, filename)){
        throw runtime_error("open file failed!");
    }
    string line, word;
    size_t line_no = 0;
    while(getline(in, line)){
        line_no ++;
        istringstream stream(line);
        lines_.push_back(line);
        while(line >> word){
            words[word].insert(line_no);
        }    
    }
    in.close();
    in.clear();
}

const set<int> &query(const string &str)
{
    map<string, map<int> >::iterator it = words_.find(str);
    if(it != words_.end()){
        return it->second;
    }
    else
        return set<int>();
}

ifstream &TextQuery::openfile(ifstream &os, const string &filename)
{
    os.close();
    os.clear();
    os.open(filename.c_str());
    return os;
}
