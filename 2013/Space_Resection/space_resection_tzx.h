#ifndef SPACE_RESECTION_TZX_H
#define SPACE_RESECTION_TZX_H
#include "matrix.h"
#include "point_2d.h"
#include "point_3d.h"

const int maximum_iteration_time = 20;
const double tolerance = 0.00003;// 1' is about 0.00003(rand)

class space_resection_tzx
{
public:
    space_resection_tzx();
    bool satisfyTolerance(const double phi, const double omega, const double kappa);

    Matrix compose_A_onePoint(const point_2d p2d, const point_3d p3d);
    Matrix compose_A_allPoints();
    Matrix compose_X(double xs, double ys, double zs, double p, double o, double k);
    Matrix compose_R(double phi, double omega, double kappa);
    Matrix compose_L();

    double control_points_X_even();
    double control_points_Y_even();

    void chooseMode();
    void modeLocalExample();
    void modeInputParametersManually();
    void modeExit();

    void preCalc();
    void globalIter();
    void calcApprox_init();
    void calcAprrox_adjust();
    void X_feedBack(const Matrix feed);

    void printParameters();
    void printResult();

    double d_phi();
    double d_omega();
    double d_kappa();


private:
    int    num_control_points;
    double m;
    double f;
    double H;
    double x0, y0;
    double phi, omega, kappa;
    double Xs, Ys, Zs;
    double a1, a2, a3, b1, b2, b3, c1, c2, c3;

    Matrix  V;
    Matrix  A;
    Matrix  X;
    Matrix  dX;
    Matrix  L;
    Matrix  R;

    point_2d * control_points_2d;
    point_2d * control_points_2d_approx;
    point_3d * control_points_3d;

};

#endif // SPACE_RESECTION_TZX_H
