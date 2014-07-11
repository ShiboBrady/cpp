#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


struct Student{
    string name_;
    int age_;
    int score_;

    bool operator< (const Student &other) const{
        if(score_ != other.score_){
            return score_ < other.score_;
        }

        if(name_ != other.name_){
            return name_ < other.name_;
        }

        return age_ < other.age_;
    }
};


int main(int argc, const char *argv[])
{
    Student arr[3] = {
        {"zhangsan", 26, 98},
        {"lisi", 27, 98},
        {"wangwu", 27, 97}
    };

    sort(arr, arr + 3);

    for(int i = 0; i < 3; ++i){
        cout << "name: " << arr[i].name_ << "age: " << arr[i].age_ << "score: " << arr[i].score_ << endl;
    }
    return 0;
}
