#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char *argv[])
{
    string s = "Hello World";
    s.insert(2, 5, 's');
    cout << s << endl;

    s.insert(4, "test");
    cout << s << endl;
    
    s = "Hello, world";
    s.insert(2, "test", 3);
    cout << s << endl;

    s = "Hello, World";
    string tmp = "football";
    s.insert(5, tmp, 3, 2);
    cout << s << endl;

    s = "Hello, World";
    string tmp2 = "football";
    s.insert(0, tmp2);
    cout << s << endl;

    s = "Hello, World";
    s.erase(4, 5);
    cout << s << endl;

    s = "Hello, World";
    cout << s.substr(5, 3) << endl;

    s.append(", I am ZhangShibo, a sunflower.");
    cout << s << endl;

    s.append(string("hello", 3));

    string::size_type pos = s.find(string("sunflower"), 3);
    if(pos != string::npos){
        cout << pos << endl;
    }
    else{
        cout << "Not found" << endl;
    }
    return 0;
}
