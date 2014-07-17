#ifndef FREQUENCE_H
#define FREQUENCE_H

#include <map>
#include <set>
#include <fstream>
#include <string>

class Frequence{
    public:
        Frequence(const std::string &excludeFile, const std::string &fileName);
        void print();
    private:
        std::map<std::string, int> words_;
        std::set<std::string> exclude_;
        std::string excludeFile_;
        std::string fileName_;
        std::ifstream os_;
        void readExcludeWord();
        void word_count();
        std::ifstream &open_file(const std::string &filename);
};

#endif  /*FREQUENCE_H*/
