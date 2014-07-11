#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Student{
    string name_;
    int age_;
    int score_;
};

bool cmp(const Student &s1, const Student &s2)
{
    if(s1.score_ != s2.score_){
        return s1.score_ < s2.score_;
    }
    if(s1.name_ != s2.name_){
        return s1.name_ < s2.name_;
    }
    return s1.age_ < s2.age_;
}

int main(int argc, const char *argv[])
{
    Student arr[3] = {
        {"zhangsan", 26, 98},
        {"lisi", 26, 98},
        {"wangwu", 28, 97}
    };

    sort(arr, arr + 3, cmp);
    for(int i = 0; i < 3; ++i){
        cout << "name: " << arr[i].name_ << " age: " << arr[i].age_ << " score: " << arr[i].score_ << endl;
    }
    return 0;
}
