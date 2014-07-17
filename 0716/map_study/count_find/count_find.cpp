#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

void print(const map<string, int>::value_type &p)
{
    cout << p.first << " occurs: " << p.second << " times." << endl;
}

int main(int argc, const char *argv[])
{
    map<string, int> word;
    word.insert(make_pair("HeNan", 1));
    word.insert(map<string, int>::value_type("XinJiang", 2));
    word["GuangDong"] = 3;
    
    for_each(word.begin(), word.end(), print);
    cout << "--------------" << endl;

    cout << word.count("HeNan") << endl;
    cout << word.count("ShangHai") << endl;
    cout << word.count("GuangDong") << endl;

    map<string, int>::iterator it = word.find("HeNan");
    if(it == word.end()){
        cout << "not found" << endl;
    }
    else{
        cout << it->first << " " << it->second << endl;
    }

    word.erase("XinJiang");
    cout << "---------------" << endl;
    for_each(word.begin(), word.end(), print);
    return 0;
}
