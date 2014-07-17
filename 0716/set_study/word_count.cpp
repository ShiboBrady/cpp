#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <stdexcept>

using namespace std;

void print(const string &s)
{
    cout << s << " ";
}

void print_map(const map<string, int>::value_type &p)
{
    cout << p.first << " occures: " << p.second << " times." << endl;
}

void word_counts(ifstream &os, const set<string> &except, map<string, int> &word_count){
    string word;
    while(os >> word){
        if(!except.count(word)){
            ++word_count[word];
        }
    }
}

ifstream &open_file(ifstream &os, const string &filename)
{
    os.close();
    os.clear();
    os.open(filename.c_str());
    return os;
}

int main(int argc, const char *argv[])
{
    ifstream in;
    string filename = "in.txt";
    if(!(open_file(in, filename))){
        throw runtime_error("open file failed.");
    }

    map<string, int> word_count;
    set<string> except;

    except.insert("I");
    except.insert("am");
    except.insert("is");
    except.insert("are");
    except.insert("a");
    except.insert("A");
    except.insert("An");
    except.insert("the");

    word_counts(in, except, word_count);

    in.close();
    in.clear();

    for_each(except.begin(), except.end(), print);
    cout << endl << "------------------" << endl;
    for_each(word_count.begin(), word_count.end(), print_map);
    return 0;
}
