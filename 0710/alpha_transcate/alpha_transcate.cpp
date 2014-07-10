#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

int main(int argc, const char *argv[])
{
    string s;
    cout << "Enter a string: " << endl;
    getline(cin, s);
    for(string::iterator it = s.begin(); it != s.end(); ++it){
        if(isupper(*it)){
            *it = tolower(*it);
        }
        else if(islower(*it)){
            *it = toupper(*it);
        }
    }

    cout << s << endl;
    return 0;
}
