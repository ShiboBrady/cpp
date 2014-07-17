#include "frequence.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char *argv[])
{
    string excludeFile = "exclude.txt";
    string filename = "in.txt";
    Frequence fre(excludeFile, filename);
    fre.print();
    return 0;
}
