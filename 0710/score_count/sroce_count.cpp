#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef struct stu_info
{
    string name;
    float score;
}stu_info;

int main(int argc, const char *argv[])
{
    vector<stu_info> ivec;
    vector<stu_info> pvec;

    stu_info stu;
    while(cin >> stu.name){
        cin >> stu.score;
        ivec.push_back(stu);
    }

    for(vector<stu_info>::iterator it = ivec.begin(); it != ivec.end(); ++it){
        if(it->score >= 60){
            pvec.push_back(*it);
        }
    }

    cout << "There are " << pvec.size() << " student passed." << endl;
    for(vector<stu_info>::iterator it = pvec.begin(); it != pvec.end(); ++it){
        cout << it->name << ": " << it->score << endl;
    }
    return 0;
}
