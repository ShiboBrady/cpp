#ifndef RIO
#define RIO 

class Rio
{
    public:
        Rio();
        ssize_t readn() 
    private:
        char buffer_[8092];
};

#endif  /*RIO*/
