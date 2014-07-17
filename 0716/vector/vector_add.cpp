#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

int main(int argc, const char *argv[])
{
    vector<string> svec;
    svec.push_back("Hello, World!");
    svec.push_back("ByMyself");
    svec.push_back("Cheers,Cheers!");
    svec.push_back("SunFlower!");
    svec.push_back("I Will success!");

    vector<string> svec2(svec);
    svec2.insert(svec2.begin(), 3, "Make great efforts!");

    for(auto &item: svec2){
        cout << item << endl;    
    }
    return 0;
}
