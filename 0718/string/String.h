#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <stddef.h>

class String{
    friend String operator+(const String &str1, const String &str2);
    friend String operator+(const String &str1, const char *str2);
    friend String operator+(const char *str1, const String &str2);

    friend bool operator>(const String &str1, const String &str2);
    friend bool operator<(const String &str1, const String &str2);
    friend bool operator>=(const String &str1, const String &str2);
    friend bool operator<=(const String &str1, const String &str2);
    friend bool operator==(const String &str1, const String &str2);
    friend bool operator!=(const String &str1, const String &str2);

    friend std::ostream &operator<<(std::ostream &os, const String &str);

    friend std::istream &operator>>(std::istream &is, String &str);

    public:
        String();
        String(const char *str);
        String(const String &str);
        ~String();

        size_t size() const;
        void debug() const;

        String &operator=(const String &str);
        String &operator=(const char *str);
        String &operator+=(const String &str);
        String &operator+=(const char *str);

        char &operator[](size_t index);
        const char &operator[](size_t index) const;
    private:
        char *str_;
};

#endif  /*STRING_H*/
