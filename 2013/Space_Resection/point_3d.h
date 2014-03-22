#ifndef POINT_3D_H
#define POINT_3D_H

class point_3d
{
public:
    point_3d();
    point_3d(double XX, double YY, double ZZ);
    double getX() const;
    double getY() const;
    double getZ() const;
    void set(double XX, double YY, double ZZ);
    void Print() const;

private:
    double X;
    double Y;
    double Z;
};

#endif // POINT_3D_H
