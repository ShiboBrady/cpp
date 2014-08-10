#ifndef SEARCH_H
#define SEARCH_H 
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <vector>

struct Word
{
    std::string word_;
    int med_;
    int frequence_;
    bool isSet_;

    bool operator < (const Word &other) const {
        if(med_ != other.med_){
            return med_ > other.med_;
        }
        return frequence_ < other.frequence_;
    }
};

class Search
{
    public:
        Search(const std::string &filename);
        std::string query(const std::string &str);
        int medCalc(const std::string &str1, const std::string &str2);
        bool isInIndex(const std::string &searchWord, const std::string &word);
        std::string search(const std::map<std::string, Word> &);
        void writeCacheFile();
    private:
        void readFile(const std::string &filename);
        void createIndex();
        void readCacheFile();

        std::ifstream &openfile(std::ifstream &os, const std::string &filename);

        std::map<std::string, Word> storage_;  //词库
        std::vector<std::set<std::string> > index_;//索引表 
        std::map<std::string, std::string> cache_; //缓存
};

#endif  /*SEARCH_H*/
