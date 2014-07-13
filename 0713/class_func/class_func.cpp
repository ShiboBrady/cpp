#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Student
{
    private:
        string name_;
        int age_;
        int score_;

    public:
        void setName(const string &name){
            name_ = name;
        }

        const string &getName() const{
            return name_;
        }

        void setAge(const int age){
            age_ = age;
        }

        int getAge() const{
            return age_;
        }

        void setScore(const int score){
            score_ = score;
        }

        int getScore() const{
            return score_;
        }

        void print(){
            cout << name_ <<　" " << age_ << " " << score_ << endl;
        }
}

int main(int argc, const char *argv[])
{
    Student stu;
    stu.setName("zhangsan");
    stu.setAge()
    return 0;
}
