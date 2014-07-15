#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Student{
    public:
        Student();
        Student(const string &name,
                int age,
                int score);
        const string &getName() const;
        Student &
    private:
        string name;
        int age;
        int score;
};

int main(int argc, const char *argv[])
{
    
    return 0;
}
