#include "handle.hpp"
#include "Animal.h"
#include <vector>
using namespace std;

int main(int argc, const char *argv[])
{
    vector<Handle<Animal> > vec;
    Cat c1, c2;
    Dog d1, d2, d3;
    Chicken ch1, ch2;
    vec.push_back(Handle<Animal>(&c1));
    vec.push_back(&c2);
    vec.push_back(&d1);
    vec.push_back(&d2);
    vec.push_back(&d3);
    vec.push_back(&ch1);
    vec.push_back(&ch2);

    for(vector<Handle<Animal> >::iterator it = vec.begin(); it != vec.end(); ++it){
        (*it)->display();    
    }
    return 0;
}
