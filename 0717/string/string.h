#ifndef STRING_H
#define STRING_H 
#include <iostream>
#include <string.h>

class String{
        friend std::ostream &operator << (std::ostream &os, const String &str);
        friend std::istream &operator >> (std::istream &os, String &str);
        friend String operator + (const String &str1, const String &str2);
        friend String operator + (const String &str1, const char *str2);
        friend String operator + (const char *str1, const String &str2);
        friend bool operator > (const String &str1, const String &str2);
        friend bool operator < (const String &str1, const String &str2);
        friend bool operator >= (const String &str1, const String &str2);
        friend bool operator <= (const String &str1, const String &str2);
        friend bool operator == (const String &str1, const String &str2);
        friend bool operator != (const String &str1, const String &str2);
    public:
        String();
        String(const char *str);
        String(const String &str);
        String &operator = (const String &str);
        String &operator = (const char *str);
        String &operator += (const String &str);
        String &operator += (const char *str);
        char &operator [] (std::size_t index);
        const char &operator [] (std::size_t index) const;
        void debug();
        ~String();
    private:
        char *str_;
};

inline std::ostream &operator << (std::ostream &os, const String &str)
{
    os << str.str_;
    return os;
}

inline std::istream &operator >> (std::istream &is, String &str)
{
    char buf[1024];
    if(is){
        is >> buf;
    }
    if(is){
        str = buf;
    }
    return is;
}

inline String operator + (const String &str1, const String &str2)
{
    String S(str1);
    S += str2;
    return S;
}

inline String operator + (const String &str1, const char *str2)
{
    String S;
    S = str1;
    S += str2;
    return S;
}

inline String operator + (const char *str1, const String &str2)
{
    String S;
    S += str1;
    S += str2;
    return S;
}
inline bool operator > (const String &str1, const String &str2)
{
    return strcmp(str1.str_, str2.str_) > 0;
}
inline bool operator < (const String &str1, const String &str2)
{
    return strcmp(str1.str_, str2.str_) < 0;
}
inline bool operator >= (const String &str1, const String &str2)
{
    return !(str1 < str2);
}
inline bool operator <= (const String &str1, const String &str2)
{
    return !(str1 > str2);
}
inline bool operator == (const String &str1, const String &str2)
{
    return strcmp(str1.str_, str2.str_) == 0;
}
inline bool operator != (const String &str1, const String &str2)
{
    return !(str1 == str2);
}
#endif  /*STRING_H*/
