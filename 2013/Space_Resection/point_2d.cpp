#include "point_2d.h"
#include <cstdio>

point_2d::point_2d()
{
    x = 0.0;
    y = 0.0;
}

point_2d::point_2d(double xx, double yy)
{
    x = xx;
    y = yy;
}

void point_2d::Print() const
{
    printf("( %7.3f,  %7.3f )",x, y);
}

double point_2d::getx() const
{
    return x;
}

double point_2d::gety() const
{
    return y;
}

void point_2d::set(double xx, double yy)
{
    x = xx;
    y = yy;
}
