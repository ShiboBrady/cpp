#ifndef NONCOPY_H
#define NONCOPY_H 

class Noncopy{
    public:
        Noncopy();
        ~Noncopy();
    private:
        Noncopy(const Noncopy &other);
        Noncopy &operator = (const Noncopy &other);
};

#endif  /*NONCOPY_H*/
