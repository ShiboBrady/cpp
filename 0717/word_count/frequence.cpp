#include "frequence.h"
#include <iostream>
#include <stdexcept>

using namespace std;

Frequence::Frequence(const string &excludeFile, const string &fileName)
    :excludeFile_(excludeFile),
     fileName_(fileName)
{
    readExcludeWord();
    word_count();
}

void Frequence::print()
{
    for(map<string, int>::iterator it = words_.begin(); it != words_.end(); ++it){
        cout << it->first << " occurs: " << it->second << " times. " << endl;
    }
}

ifstream &Frequence::open_file(const string &filename)
{
    os_.close();
    os_.clear();
    os_.open(filename.c_str());
    return os_;
}

void Frequence::readExcludeWord()
{
    if(!(open_file(excludeFile_))){
        throw runtime_error("open file failed.");
    }
    string word;
    while(os_ >> word){
        exclude_.insert(word);
    }
    os_.close();
    os_.clear();
}

void Frequence::word_count()
{
    if(!(open_file(fileName_))){
        throw runtime_error("open file failed.");
    }

    string word;

    while(os_ >> word){
        if(!exclude_.count(word)){
            words_[word]++;
        }
    }

    os_.close();
    os_.clear();
}
