#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student
{
    string name_;
    int age_;
    int score_;

    void print_(){
        cout << name_ << " " << age_ << " " << score_ << endl;
    }
};

int main(int argc, const char *argv[])
{
    Student s;
    s.name_ = "zhangsan";
    s.age_ = 20;
    s.score_ = 100;
    s.print_();
    return 0;
}
