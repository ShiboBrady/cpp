#ifndef WORDCOUNT_h
#define WORDCOUNT_H

#include <vector>
#include <map>
#include <string>
#include <fstream>

class WordCount
{
    public:
        void readfile(const std::string &filename);
        void writefile(const std::string &filename);
    private:
        std::ifstream &openfileRead(std::ifstream &os, const std::string &filename);
        std::ofstream &openfileWrite(std::ofstream &os, const std::string &filename);
        std::vector<std::string> lines_;
        std::map<std::string, size_t>words_; 
};

#endif  /*WORDCOUNT_H*/
