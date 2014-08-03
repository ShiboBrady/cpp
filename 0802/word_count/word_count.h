#ifndef WORD_COUNT_H
#define WORD_COUNT_H 

#include <string>
#include <vector>


class Word_len
{
    public:
        Word_len(size_t val = 0)
            :bound_(val){}
        bool operator()(const std::string &s){
            return s.size() >= bound_;
        }
    private:
        std::string::size_type bound_;
};

class Word_count
{
    public:
        Word_count(size_t val);
        void display();
    private:
        void readword();
        void process();
        static bool isShorter(const std::string &s1, const std::string &s2);
        std::vector<std::string> words_;
        Word_len wl_;
        size_t wc_;
};

#endif  /*WORD_COUNT_H*/
