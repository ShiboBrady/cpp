#include "string.h"
#include <iostream>
using namespace std;
String::String()
    :str_(new char[1])
{
    str_[0] = 0;
}

String::String(const char *str)
    :str_(new char[strlen(str) + 1])
{
    strcpy(str_, str);
}

String::String(const String &str)
    :str_(new char[strlen(str.str_) + 1])
{
    strcpy(str_, str.str_);
}

String &String::operator = (const String &str)
{
    if(this != &str){
        delete[] str_;
        str_ = new char[strlen(str.str_) + 1];
        strcpy(str_, str.str_);
    }
    return *this;
}

String &String::operator = (const char *str)
{
    delete[] str_;
    str_ = new char[strlen(str) + 1];
    strcpy(str_, str);
    return *this;
}

String &String::operator += (const String &str)
{
    char *tmp = new char[strlen(str_) + strlen(str.str_) + 1];
    strcpy(tmp, str_);
    strcat(tmp, str.str_);
    delete[] str_;
    str_ = NULL;
    str_ = tmp;
    return *this;
}

String &String::operator += (const char *str)
{
    *this += String(str);
    return *this;
}
void String::debug()
{
    cout << str_ << endl;
}
char &String::operator [] (size_t index)
{
    return str_[index];
}

const char &String::operator [] (size_t index) const
{
    return str_[index];
}

String::~String()
{
    delete[] str_;
}
