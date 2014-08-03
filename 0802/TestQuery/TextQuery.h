#ifndef TEXTQUERY_H
#define TEXTQUERY_H 

#include <vector>
#include <map>
#include <set>
#include <string>
#include <fstream>

class TextQuery{
    public:
        void readFile(const std::string &filename);
        const std::set<int> query(const std::string &str);
        void print(std::set<int> lines, const std::string &word);
    private:
        std::ifstream &openfile(std::ifstream &os, const std::string &filename);
        std::string readline(int line_no);
        std::string make_plural(int size, std::string s1, std::string s2);

        std::vector<std::string> lines_;
        std::map<std::string, std::set<int> > words_;
};

#endif  /*TEXTQUERY_H*/
