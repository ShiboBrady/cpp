#ifndef SEARCH_H
#define SEARCH_H 

#include <string>
#include <fstream>
#include <map>

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
        Search(const std::string &filename);
        std::string query(const std::string &str);
        int medCalc(const std::string &str1, const std::string &str2);
        std::string search();
    private:
        void readFile(const std::string &filename);
        std::ifstream &openfile(std::ifstream &os, const std::string &filename);
        std::map<std::string, Word> storage_; 
        int medArray_[20][20];
};

#endif  /*SEARCH_H*/
