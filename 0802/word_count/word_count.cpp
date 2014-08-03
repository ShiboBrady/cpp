#include "word_count.h"
#include <iterator>
#include <algorithm>
#include <iostream>

using namespace std;
Word_count::Word_count(size_t val)
    :wl_(val), wc_(0)
{}

void Word_count::readword()
{
    std::istream_iterator<std::string> cin_it(std::cin);
    std::istream_iterator<std::string> end_of_stream;
    while(cin_it != end_of_stream)
        words_.push_back(*cin_it++);
}

void Word_count::process()
{
    sort(words_.begin(), words_.end());
    std::vector<std::string>::iterator end_unique = \
         unique(words_.begin(), words_.end());
    words_.erase(end_unique, words_.end());
    stable_sort(words_.begin(), words_.end(), isShorter);
    wc_ = count_if(words_.begin(), words_.end(), wl_);
}

void Word_count::display()
{
    readword();
    process();
    cout << "There are " << wc_ << " words." << endl;
}

bool Word_count::isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}
