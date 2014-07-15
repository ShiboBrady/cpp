#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student{
    public:
        Student(const string &name,
                int age,
                int score)
        {
            name_ = name;
            age_ = age;
            score_ = score;
        }
        void set(const string &name,
                int age,
                int score)
        {
            name_ = name;
            age_ = age;
            score_ = score;
        }

        void print() const{
            cout << "in const " << endl;
            cout << name_ << " " << age_ << " " << score_ << endl;
        }

        /*
        void print() {
            cout << "in non-const " << endl;
            cout << name_ << " " << age_ << " " << score_ << endl;
        } */

    private:
        string name_;
        int age_;
        int score_;
};



int main(int argc, const char *argv[])
{
    Student s("zhangsna", 34, 77);
    s.print();


    const Student s2("zhangsna", 45, 88);
    s2.set("lisi", 32, 45);
    s2.print();

    return 0;
}
