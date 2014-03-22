#ifndef EXCEPTION_H
#define EXCEPTION_H

class Exception
{
public:
    Exception();
    Exception(const char * arg);
private:
    const char *msg;
};

#endif // EXCEPTION_H
