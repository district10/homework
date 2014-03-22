#include "point_3d.h"
#include <cstdio>

point_3d::point_3d()
{
    X = 0.0;
    Y = 0.0;
}

point_3d::point_3d(double XX, double YY, double ZZ)
{
    X = XX;
    Y = YY;
    Z = ZZ;
}

double point_3d::getX() const
{
    return X;
}

double point_3d::getY() const
{
    return Y;
}

double point_3d::getZ() const
{
    return Z;
}

void point_3d::set(double XX, double YY, double ZZ)
{
    X = XX;
    Y = YY;
    Z = ZZ;
}

void point_3d::Print() const
{
    printf("( %9.3f,  %9.3f,  %9.3f )",X, Y, Z);
}
