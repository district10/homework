#include "exception.h"

Exception::Exception()
{
}

Exception::Exception(const char *arg)
{
    msg = arg;
}
