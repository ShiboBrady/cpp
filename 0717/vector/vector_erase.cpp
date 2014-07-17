#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char *argv[])
{
    vector<int> ivec;
    ivec.push_back(1);
    ivec.push_back(3);
    ivec.push_back(4);
    ivec.push_back(6);
    ivec.push_back(10);
    ivec.push_back(15);
    ivec.push_back(21);
    ivec.push_back(28);

    for(vector<int>::iterator it = ivec.begin(); it != ivec.end(); ++it){
        if(*it % 2 == 0){
            //cout << *it << endl;
            it = ivec.erase(it);
            --it;
        }
    }
    
    for(vector<int>::iterator it = ivec.begin(); it != ivec.end(); ++it){
        cout << *it << endl;    
    }
    return 0;
}
