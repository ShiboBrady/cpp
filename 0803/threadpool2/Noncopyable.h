#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H 

class Noncopyable
{
    public:
        Noncopyable(){}
        ~Noncopyable(){}
    private:
        Noncopyable(const Noncopyable &other){}
        void operator = (const Noncopyable &other){}
};

#endif  /*NONCOPYABLE_H*/
