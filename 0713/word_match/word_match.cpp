#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>

using namespace std;

class Query{
    public:
        void save_words(const string &filename){
            if(!open_file(filename)){
                throw runtime_error("can't open file!");
            }
            while(in >> word){
                words.push_back(word);
            }
        }

        vector<string> query(const string &user_input){
            vector<string> result;
            for(vector<string>::iterator it = words.begin(); it != words.end(); ++it){
                if((*it).find(user_input) != string::npos){
                    result.push_back(*it);
                }    
            }
            return result;
        }
    private:
        vector<string> words;
        string word;
        ifstream in;

        ifstream &open_file(const string &filename){
            in.close();
            in.clear();
            in.open(filename.c_str());
            return in;
        }
};

int main(int argc, const char *argv[])
{
    Query q;
    vector<string> result;
    string filename = "in.txt";
    q.save_words(filename);
    string user_input;
    while(cin >> user_input){
        result = q.query(user_input);
        cout << "size = " << result.size() << endl;
        for(vector<string>::iterator it = result.begin(); it != result.end(); ++it){
            cout << *it << endl;    
        }
    }
    return 0;
}
