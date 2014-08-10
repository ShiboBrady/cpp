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
        Search(const std::string &storageFile, const std::string &cacheFile);
        std::string query(const std::string &str);
        int medCalc(const std::string &str1, const std::string &str2);
        bool isInIndex(const std::string &searchWord, const std::string &word);
        void UpdateFile();
    private:
        void readFile();
        void writeFile();
        void createIndex();
        void readCacheFile();
        void writeCacheFile();

        std::ifstream &openfileRead(std::ifstream &os, const std::string &filename);
        std::ofstream &openfileWrite(std::ofstream &os, const std::string &filename);

        std::map<std::string, Word> storage_;  //词库
        std::vector<std::set<std::string> > index_;//索引表 
        std::map<std::string, std::string> cache_; //缓存

        const std::string storageFile_; //词库文件
        const std::string cacheFile_; //缓存文件
};

#endif  /*SEARCH_H*/
