#include "Search.h"
#include <sstream>
#include <stdexcept>
#include <strings.h>
#include <iostream>
#include <stdlib.h>
#include <queue>
using namespace std;

Search::Search(const string &storageFile, const string &cacheFile)
    :index_(26),
     storageFile_(storageFile),
     cacheFile_(cacheFile)
{
    readFile();
    createIndex();
    readCacheFile();
}

void Search::UpdateFile()
{
    writeCacheFile();
    writeFile();
}

void Search::readFile()
{
    ifstream in;
    if(!openfileRead(in, storageFile_))
        throw runtime_error("openfile");
    string line;
    while(getline(in, line)){
        istringstream iss(line);
        string word;
        int fre;
        iss >> word >> fre;
        Word new_word;
        new_word.word_ = word;
        new_word.med_ = 20;
        new_word.frequence_ = fre;
        storage_.insert(make_pair(word, new_word));
    }
    in.close();
    in.clear();
}

void Search::writeFile()
{
    ofstream out;
    if(!openfileWrite(out, storageFile_))
        throw runtime_error("open file to write failed.");
    map<string, Word>::iterator mapit;
    for(mapit = storage_.begin(); mapit != storage_.end(); ++mapit)
        out << mapit->first << " " << mapit->second.frequence_ << endl;
    cout << "write storage file once." << endl;
    out.close();
    out.clear();
}

void Search::createIndex()
{
    map<string, Word>::iterator mapit;
    for(mapit = storage_.begin(); mapit != storage_.end(); ++mapit){
        string word = mapit->first;
        //按照word[i]将word插入到字母word[i]对应的单词集合中
        for(size_t i = 0; i != word.size(); ++ i){
            index_[word[i] - 97].insert(word);
        }         
    }
}

void Search::readCacheFile()
{
    ifstream in;
    if(!openfileRead(in, cacheFile_))
        throw runtime_error("open cache file to read fail.");
    string line;
    string usrword;
    string mapword;
    while(getline(in, line)){
        istringstream iss(line);
        iss >> usrword >> mapword;
        cache_.insert(make_pair(usrword, mapword));
    }
    in.close();
    in.clear();
}

void Search::writeCacheFile()
{
    ofstream out;
    if(!openfileWrite(out, cacheFile_))
        throw runtime_error("open cache file to write fail.");
    map<string, string>::iterator vecit;
    for(vecit = cache_.begin(); vecit != cache_.end(); ++vecit)
        out << vecit->first << " " << vecit->second << endl;
    cout << "write cache file once." << endl;
    out.close();
    out.clear();
}

string Search::query(const string &word)
{
    //定义一个优先级队列
    priority_queue<Word>queue; 
    //map<string, Word> curSearch = storage_;
    map<string, Word>::iterator it;
    //先从词库中查找
    it = storage_.find(word);
    if(it != storage_.end())
        return word;
    //如果不存在，则先从cache中查找
    map<string, string>::iterator cacheit;
    cacheit = cache_.find(word);
    if(cacheit != cache_.end())
        return cacheit->second;
    //cache中不存在，则执行以下的查找策略
    for(it = storage_.begin(); it != storage_.end(); ++ it){
        //根据长度差是否大于3来排除一部分词
        if(::abs(word.size() - it->first.size()) > 3)
            continue;
        //根据所要比对的词是否在索引表中来排除一部分词
        if(!isInIndex(word, it->first))
            continue;
        Word new_word = it->second;
        //现在开始计算最短编辑距离
        new_word.med_ = medCalc(word, it->first);
        //将最短编辑距离大于5的单词排除掉
        if(new_word.med_ >= 5)
            continue;
        //将真正符合条件的单词标记为true，用来将来查找最匹配单词
        queue.push(new_word);
    }
    //取出优先级队列中第一个元素， 即最大的那个元素
    string result = queue.top().word_;
    //将查询结果插入cache中
    cache_.insert(make_pair(word, result));
    //更新内存中的词库
    if(result.size() != 0)
        storage_[result].frequence_++;
    return result; 
}

int Search::medCalc(const string &x, const string &y)
{
    int medArray_[20][20]; //用以计算最短编辑距离的数组
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

bool Search::isInIndex(const string &searchWord, const string &usrword)
{
    string word = usrword;
    for(size_t i = 0; i != usrword.size(); ++i){
        //索引表中的每一项对应的迭代器
        set<string>::iterator setit;
        //每一项迭代器的最后一项
        set<string>::iterator endit = index_[word[i] - 97].end();
        //在包含字母word[i]的单词集合中查找单词word
        setit = index_[word[i] - 97].find(word);
        //如果找到了，就返回true，否则继续在下一个字母的单词集合中查找
        if(setit != endit)
            return true;
    }
    return false;
}

ifstream &Search::openfileRead(ifstream &os, const string &filename)
{
    os.close();
    os.clear();
    os.open(filename.c_str());
    return os;
}

ofstream &Search::openfileWrite(ofstream &os, const string &filename)
{
    os.close();
    os.clear();
    os.open(filename.c_str());
    return os;
}
