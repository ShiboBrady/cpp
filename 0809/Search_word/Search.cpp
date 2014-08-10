#include "Search.h"
#include <sstream>
#include <stdexcept>
#include <strings.h>
#include <iostream>
using namespace std;

Search::Search(const string &filename)
{
    readFile(filename);
}

void Search::readFile(const string &filename)
{
    ifstream in;
    if(!openfile(in, filename))
        throw runtime_error("openfile");
    string line;
    while(getline(in, line)){
        istringstream iss(line);
        string word;
        int fre;
        iss >> word >> fre;
        Word new_word;
        new_word.word_ = word;
        new_word.frequence_ = fre;
        storage_.insert(make_pair(word, new_word));
    }
    in.close();
    in.clear();
}

string Search::query(const string &word)
{
    map<string, Word>::iterator it;
    it = storage_.find(word);
    if(it != storage_.end())
        return word;
    for(it = storage_.begin(); it != storage_.end(); ++ it){
        it->second.med_ = medCalc(word, it->first);
        //cout << it->first << " " << it->second.med_ << endl;
    }
    return search();
}

int Search::medCalc(const string &x, const string &y)
{
    bzero(medArray_, sizeof(medArray_));
    int m = x.size();
    int n = y.size();
    for(int i = 0; i <= n; ++i)
        medArray_[0][i] = i;
    for(int i = 0; i <= m; ++i)
        medArray_[i][0] = i;
    for(int i = 1; i <= m; ++i){
        for(int j = 1; j <= n; ++j){
            if(x[i-1] == y[j-1])
                medArray_[i][j] = medArray_[i-1][j-1];
            else{
                int a = medArray_[i-1][j];
                int b = medArray_[i][j-1];
                int c = medArray_[i-1][j-1];
                int temp;
                medArray_[i][j] = ((temp = a < b ? a : b) < c ? temp : c) + 1;
            }   
        }   
    }   
    return medArray_[m][n];
}

string Search::search()
{
    Word maxWord;
    maxWord.word_= "";
    maxWord.med_ = 5;
    maxWord.frequence_ = 0;
    for(map<string, Word>::iterator it = storage_.begin(); it != storage_.end(); ++it){
        if(maxWord < it->second)
            maxWord = it->second;
    }
    return maxWord.word_;
}

ifstream &Search::openfile(ifstream &os, const string &filename)
{
    os.close();
    os.clear();
    os.open(filename.c_str());
    return os;
}
