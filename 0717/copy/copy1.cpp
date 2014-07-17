#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Student{
    public:
        Student()
            :name_(""),
             age_(0),
             score_(0)
        {}
        Student(const Student &other)
        {
            name_ = other.name_;
            age_ = other.age_;
            score_ = other.score_;
        }
        void set(const string &name, int age, int score)
        {
            name_ = name;
            age_ = age;
            score_ = score;
        }
        
        void print()
        {
            cout << name_ << " " << age_ << " " << score_ << endl;
        }
    private:
        string name_;
        int age_;
        int score_;
};

int main(int argc, const char *argv[])
{
    Student s1;
    s1.set("ZhangSan", 23, 88);
    Student s2;
    s2 = s1;
    s2.print();
    return 0;
}

