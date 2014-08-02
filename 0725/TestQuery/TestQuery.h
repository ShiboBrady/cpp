#ifndef TEXTQUERY_H
#define TEXTQUERY_H 

#include <vector>
#include <map>
#include <string>
#include <fstream>

class TextQuery{
    public:
        void readFile(const string &filename);
        const std::set<int> &query(const string &str);
    private:
        std::ifstream &openfile(std::ifstream &os, const string &filename);
        std::vector<std::string> lines_;
        std::map<std::string, std::set<int> > words_;
};

#endif  /*TEXTQUERY_H*/
