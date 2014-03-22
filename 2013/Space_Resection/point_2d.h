#ifndef POINT_2D_H
#define POINT_2D_H

class point_2d
{
public:
    point_2d();
    point_2d(double xx, double yy);
    void Print() const;
    double getx() const;
    double gety() const;
    void set(double xx, double yy);

private:
    double x;
    double y;
};

#endif // POINT_2D_H
