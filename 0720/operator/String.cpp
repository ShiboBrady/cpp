#include "string.h"
#include <string.h>
#include <iostream>
#include <stddef.h>

using namespace std;

String::String()
    :str_(new char[1])
{
    str_[0] = 0;
}

String::String(const String &str)
    :str_(new char[strlen(str.str_) + 1])
{
    strcpy(str_, str.str_);
}

String::String(const char *str)
    :str_(new char[strlen(str) + 1])
{
    strcpy(str_, str);
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
    if(strcmp(str_, str) != 0){
        delete[] str_;
        str_ = new char[strlen(str) + 1];
        strcpy(str_, str);
    }
    return *this;
}

/*
String &operator = (String &str1, const String &str2)
{
    if(str1 != str2){
        delete[] str1.str_;
        str1.str_ = new char[strlen(str2.str_) + 1];
        strcpy(str1.str_, str2.str_);
    }
    return str1;
}

String &operator = (String &str1, const char *str2)
{
    if(strcmp(str1.str_, str2) != 0){
        delete[] str1.str_;
        str1.str_ = new char[strlen(str2) + 1];
        strcpy(str1.str_, str2);
    }
    return str1;
}
*/


char &operator [] (size_t index)
{
    return str_[index];
}


String &operator += (String &str1, const String &str2)
{
    char *buf = new char[strlen(str1.str_) + strlen(str2.str_) + 1];
    strcpy(buf, str1.str_);
    strcat(buf, str2.str_);
    return str1;
}

void String::debug()
{
    cout << str_ << endl;
}
