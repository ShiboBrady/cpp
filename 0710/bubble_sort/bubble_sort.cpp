#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

void swap(int &a, int &b)
{
    int temp(a);
    a = b; 
    b = temp;
}

bool cmp(int a, int b)
{
    return a < b;
}

void bubbleSort(vector<int> &ivec, bool (*cmp)(int a, int b))
{
    auto len = ivec.size();
    for(size_t i = 0; i < len - 1; ++i){
        int flag = 1;
        for(size_t j = 0; j < len - 1 - i; ++j){
            if(!cmp(ivec[j], ivec[j + 1])){
                swap(ivec[j], ivec[j + 1]);
                flag = 0;
            }
        }
        if(flag){
            break;
        }
    }
}

int main(int argc, const char *argv[])
{
    srand(time(NULL));
    vector<int> ivec;
    for(int i = 0; i != 5; ++i){
        ivec.push_back(rand() % 100);
    }

    bubbleSort(ivec, cmp);

    for(const auto &val : ivec){
        cout << val << " ";
    }
    cout << endl;
    return 0;
}
