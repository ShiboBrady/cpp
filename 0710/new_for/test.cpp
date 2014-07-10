#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char *argv[])
{
    vector<string> svec;
    svec.push_back("Beijing");
    svec.push_back("Shanghai");
    svec.push_back("Guangzhou");
    svec.push_back("Yiwu");
    svec.push_back("Shenzhen");

    //C++11提供的新式for循环
    //auto是C++11提供哦那个的自动类型推断
    for(const auto &s : svec){
        cout << s << endl;
    }

    //自动推断迭代器类型
    for(auto it = svec.begin(); it != svec.end(); ++it){
        cout << *it << endl;
    }
    return 0;
}
