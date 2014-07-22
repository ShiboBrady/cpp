#ifndef STRING_H
#define STRING_H 

class String{
    friend String &operator += (String &, const String &);
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
