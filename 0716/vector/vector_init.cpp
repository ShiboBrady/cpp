#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, const char *argv[])
{
    //声明一个空的容器
    vector<string> svec;
    svec.push_back("HeNan");
    svec.push_back("HeBei");
    svec.push_back("ShanXi");
    svec.push_back("ShanDong");
    svec.push_back("HuBei");

    cout << "svec: " << endl;
    for(auto &item: svec){
        cout << item << endl;    
    }

    //声明一个大小为5的容器
    vector<string> svec1(5);
    for(vector<string>::size_type it = 0; it != 5; ++it){
        svec1[it] = "Hello";    
    }

    for(vector<string>::iterator it = svec1.begin(); it != svec1.end(); ++it){
        cout << *it << endl;    
    }

    //声明一个大小为10的容器，且全部为“shenzhen”;
    vector<string> svec2(10, string("shenzhen"));

    for(vector<string>::iterator it = svec2.begin(); it != svec2.end(); ++it){
        cout << *it << endl;    
    }

    //用一个容器初始化另一个容器
    vector<string> svec3(svec);
    
    for(vector<string>::iterator it = svec3.begin(); it != svec3.end(); ++it){
        cout << *it << endl;    
    }
    
    vector<string>::iterator rtn = find(svec.begin(), svec.end(), string("ShanXi"));
    if(rtn == svec.end()){
        cout << "not found!" << endl;
    }
    else{
        cout << "found!" << endl;
    }

    //用一对迭代器初始化一个容器
    vector<string> svec4(svec.begin(), rtn);
    
    for(auto &item: svec4){
        cout << item << endl;
    }
    return 0;
}
