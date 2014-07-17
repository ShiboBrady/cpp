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

    vector<string>::iterator pos = find(svec.begin(), svec.end(), "Hello, World!");
    if(pos == svec.end()){
        cout << "Not found!" << endl;
    }
    else{
        svec.erase(pos);
    }

    for(auto &item: svec){
        cout << item << endl;    
    }
    return 0;
}
