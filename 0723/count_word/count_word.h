#ifndef COUNT_WORD_H
#define COUNT_WORD_H 

#include <string.h>
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

class GT_cls{
    public:
        GT_cls(size_t val = 0)
            :bound_(val){}
        bool operator()(const std::string &s){
            return s.size() >= bound_;
        }
    private:
        std::string::size_type bound_;
};

class Word_count{
    public:
        Word_count(size_t val)
            :GT_(val), wc_(0){}
        void readWord();
        void process();
        void display();
    private:
        static bool isShorter(const std::string &s1, const std::string &s2);
        std::vector<std::string> words_;
        GT_cls GT_;
        size_t wc_;
};

inline void Word_count::readWord(){
    std::istream_iterator<std::string> cin_it(std::cin);
    std::istream_iterator<std::string> end_of_stream;
    while(cin_it != end_of_stream){
        words_.push_back(*cin_it++);
    }
}

inline void Word_count::process(){
    sort(words_.begin(), words_.end());
    std::vector<std::string>::iterator end_unique = \
        unique(words_.begin(), words_.end());
    words_.erase(end_unique, words_.end());
    stable_sort(words_.begin(), words_.end(), isShorter);
    wc_ = count_if(words_.begin(), words_.end(), GT_);
}

inline void Word_count::display(){
    std::cout << "There are " << wc_ << " words." << std::endl;
    for(std::vector<std::string>::iterator it = words_.begin(); it != words_.end(); ++it){
        std::cout << *it << " ";    
    }
    std::cout << std::endl;
}

inline bool Word_count::isShorter(const std::string &s1, const std::string &s2){
    return s1.size() < s2.size();
}

#endif  /*COUNT_WORD_H*/
