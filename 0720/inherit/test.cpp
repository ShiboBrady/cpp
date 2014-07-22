#include <iostream>
#include <string>

using namespace std;

class Person{
    public:
        Person()
            :id_(-1),
             name_(""),
             age_(-1)
    {}
        Person(int id, const string &name, int age)
            :id_(id),
             name_(name),
             age_(age)
    {}
       void print(ostream &os) const
        {
            os << "id: " << id_ << ", name: " << name_ << ", age: "<< age_ << endl;
        }
    private:
        int id_;
        string name_;
        int age_;
};

class Student:public Person{
    public:
        Student()
            :school_("")
        {}

        Student(int id, const string name, int age, const string &school)
            :Person(id, name, age),
             school_(school)
        {}

        Student(const Student &s)
            :Person(s),
             school_(s.school_)
        {}

        Student &operator = (const Student &s)
        {
            if(this != &s){
                Person::operator = (s);
                school_ = s.school_;
            }
            return *this;
        }

        void print(ostream &os) const
        {
            Person::print(os);
            os << school_ << endl;
        }
        void test(){
            cout << "test" << endl;
        }
    private:
        string school_;
};

class Worker:public Person{
    private:
        string factory_;
};


int main(int argc, const char *argv[])
{
    Student s1(12, "zhangsan", 11111, "test1");
    Person *p = &s1;
    Student *s2 = (Student*)p;
    s2->print(cout);
    //p->test();
    return 0;
}
