#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char *argv[])
{
    vector<int> ivec;
    ivec.push_back(1);
    ivec.push_back(2);
    ivec.push_back(3);
    ivec.push_back(4);
    ivec.push_back(5);

    cout << "size of vector = " << ivec.size() << endl;

    for(vector<int>::size_type ix = 0; ix != ivec.size(); ++ix){
        cout << ivec[ix] << " ";
    }
    cout << endl;

    vector<string> svec;
    svec.push_back("Shenzhen ");
    svec.push_back("Beijing ");
    svec.push_back("Shanghai");

    cout << "size of string vector = " << svec.size() << endl;
    for(vector<string>::size_type ix = 0; ix != svec.size(); ++ix){
        cout << svec[ix] << " ";
    }
    cout << endl;
    return 0;
}
