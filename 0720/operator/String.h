#ifndef STRING_H
#define STRING_H 

#include <stddef.h>

class String{
    friend String &operator += (String &, const String &);
    //friend String &operator = (String &, const String &);
    //friend String &operator = (String &, const char *);
    //friend char &operator [] (String &, size_t index);
    friend 
    public:
        String();
        String(const String &);
        String(const char *);
        String &operator = (const String &);
        String &operator = (const char *);
        void debug();
    private:
        char *str_;
};

#endif  /*STRING_H*/
