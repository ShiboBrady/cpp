#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person{
    public:
        
        Person(){}
        
        Person(string name, int age)
            :name_(name), age_(age)
        {}        
        
        /*
        Person(const Person &other)
            :name_(other.name_),
             age_(other.age_)
        {}

        Person& operator = (const Person &other)
        {
            if(this != &other){
                name_ = other.name_;
                age_ = other.age_;
            }
        }
        */
        void set(string name, int age)
        {
            name_= name;
            age_ = age;
        }

        void print()
        {
            cout << name_ << " " << age_ << endl;
        }
    protected:
        string name_;
        int age_;
};

class Student:public Person{
    public:
        Student(){}

        
        Student(string name, int age, string school)
            :Person(name, age),
             //name_(name),
             //age_(age),
             school_(school)
        {}
        

        /*
        Student(const Student &other)
            :Person(other),
             school_(other.school_)
        {}
        */

        void set(string name, int age, string school)
        {
            Person::set(name, age);
            //name_ = name;
            //age_ = age;
            school_ = school;
        }

        void print()
        {
            Person::print();
            cout << school_ << endl;
        }
    private:
        string school_;
};

int main(int argc, const char *argv[])
{
    Student s1;
    s1.set("zhangsan", 10, "qinghua");
    s1.print();
    Student s2(s1);
    s2.print();
    Student s3;
    s3 = s2;
    s3.print();
    Student s4("lisi", 11, "beida");
    s4.print();
    return 0;
}
