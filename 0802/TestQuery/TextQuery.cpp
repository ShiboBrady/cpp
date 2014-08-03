#include "TextQuery.h"
#include <stdexcept>
#include <sstream>
#include <iostream>
using namespace std;
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
        while(stream >> word){
            words_[word].insert(line_no);
        }    
    }
    in.close();
    in.clear();
}

const set<int> TextQuery::query(const string &str)
{
    map<string, set<int> >::iterator it = words_.find(str);
    if(it != words_.end()){
        return it->second;
    }
    else
        return set<int>();
}

void TextQuery::print(set<int> lines, const string &word)
{
    set<int>::size_type size = lines.size();
    cout << endl << word << " occurs " << size << " " << make_plural(size, "time", "s") << endl;
    set<int>::const_iterator it = lines.begin();
    while(it != lines.end()){
        cout << "\t" << "(line " << *it << ") " << readline(*it) << endl; 
        it++;
    }
}


string TextQuery::readline(int line_no)
{
    return lines_[line_no - 1]; 
}

string TextQuery::make_plural(int size, string s1, string s2)
{
    return (size == 1) ? s1 : (s1 + s2);
}

ifstream &TextQuery::openfile(ifstream &os, const string &filename)
{
    os.close();
    os.clear();
    os.open(filename.c_str());
    return os;
}
