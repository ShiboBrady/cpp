#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

class Words{
    public:
        void readWords();
        void process();
        void display();
    private:
        static bool isShorter(const string &s1, const string &s2);
        static bool GT6(const string &s);
        vector<string> words_;
        size_t wc;
};

void Words::readWords()
{
    istream_iterator<string> cin_it(cin);
    istream_iterator<string> end_of_stream;
    while(cin_it != end_of_stream){
        words_.push_back(*cin_it++);
    }
}

void Words::process()
{
    sort(words_.begin(), words_.end());
    vector<string>::iterator end_unique = unique(words_.begin(), words_.end());
    words_.erase(end_unique, words_.end());
    stable_sort(words_.begin(), words_.end(), isShorter);
    wc = count_if(words_.begin(), words_.end(), GT6);
}

void Words::display()
{
    cout << wc << " " << " 6 characters or longer " << endl;
}

bool Words::isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

bool Words::GT6(const string &s)
{
    return s.size() >= 6;
}

int main(int argc, const char *argv[])
{
    Words words;
    words.readWords();
    words.process();
    words.display();
    return 0;
}
