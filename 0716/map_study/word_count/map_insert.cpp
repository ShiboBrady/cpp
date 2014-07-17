#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

void print(const map<string, int>::value_type &p)
{
    cout << p.first << " occers: " << p.second << " times." << endl;
}

int main(int argc, const char *argv[])
{
    map<string, int> word_count;
    word_count.insert(map<string, int>::value_type("Hello", 1));

    for_each(word_count.begin(), word_count.end(), print);

    cout << "-----------------" << endl;

    word_count.insert(make_pair("test", 3));
    for_each(word_count.begin(), word_count.end(), print);
    cout << "-----------------" << endl;

    pair<map<string, int>::iterator, bool> ret = word_count.insert(map<string, int>::value_type("Hello", 3));

    for_each(word_count.begin(), word_count.end(), print);
    cout << "-----------------" << endl;

    cout << ret.first->first << endl;
    cout << ret.first->second << endl;
    cout << ret.second << endl;
    return 0;
}
