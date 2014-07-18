#include "String.h"
#include <string.h>

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
    :str_(new char[str.size() + 1])
{
    strcpy(str_, str.str_);
}

String::~String()
{
    delete[] str_;
}

size_t String::size() const
{
    return strlen(str_);    
}
void String::debug() const
{
    cout << str_ << endl;
}

String &String::operator=(const String &str)
{
    if(this != &str){
        delete[] str_;
        str_ = new char[str.size() + 1];
        strcpy(str_, str.str_);
    }
    return *this;
}
String &String::operator=(const char *str)
{
    if(strcmp(str_, str) != 0){
        delete[] str_;
        str_ = new char[strlen(str) + 1];
        strcpy(str_, str);
    }
    return *this;
}
String &String::operator+=(const String &str)
{
    char *buf = new char[strlen(str_) + str.size() + 1];
    strcpy(buf, str_);
    strcat(buf, str.str_);
    delete[] str_;
    str_ = buf;
    return *this;
}
String &String::operator+=(const char *str)
{
    return *this += String(str);
}

char &String::operator[](size_t index)
{
    return str_[index];
}
const char &String::operator[](size_t index) const
{
    return str_[index];
}
 
String operator+(const String &str1, const String &str2)
{
    String s(str1);
    s += str2;
    return s;
}
String operator+(const String &str1, const char *str2)
{
    String s(str1);
    s += str2;
    return s;
}
String operator+(const char *str1, const String &str2)
{
    String s(str1);
    s += str2;
    return s;
}

bool operator>(const String &str1, const String &str2)
{
    return strcmp(str1.str_, str2.str_) > 0;
}
bool operator<(const String &str1, const String &str2)
{
    return str2 > str1;
}
bool operator>=(const String &str1, const String &str2)
{
    return !(str1 < str2);
}
bool operator<=(const String &str1, const String &str2)
{
    return !(str1 > str2);
}
bool operator==(const String &str1, const String &str2)
{
    return strcmp(str1.str_, str2.str_) == 0;
}
bool operator!=(const String &str1, const String &str2)
{
    return !(str1 == str2);
}

std::ostream &operator<<(std::ostream &os, const String &str) 
{
    os << str.str_;
    return os;
}

std::istream &operator>>(std::istream &is, String &str)
{
    char buf[1024];
    is >> buf;
    if(is){
        strcpy(str.str_, buf);
    }
    return is;
}
