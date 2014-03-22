#include "space_resection_tzx.h"
#include "matrix.h"
#include "point_2d.h"
#include "point_3d.h"
#include <stdint-gcc.h>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <QDebug>
#include <QDateTime>




space_resection_tzx::space_resection_tzx()
{
    QDateTime date =QDateTime::currentDateTime();

    qDebug() <<"# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #";
    qDebug() <<"#  S P A C E                                                  #";
    qDebug() <<"#      R E S E C T I O N             by  Tang ZhiXiong        #";
    qDebug() <<"# # # # # # # # # # # # # # # # #"<<date.toString()<<"#$";

    m = 15000.0;
    f = 153.24/1000.0;
    x0 = 0.0;
    y0 = 0.0;

    phi = 0.0;
    omega = 0.0;
    kappa = 0.0;

    num_control_points = 4;

    control_points_2d        = new point_2d[num_control_points];
    control_points_3d        = new point_3d[num_control_points];
    control_points_2d_approx = new point_2d[num_control_points];

    control_points_2d[0].set(86.15/1000.0, -68.99/1000.0);
    control_points_2d[1].set(-53.40/1000.0, 82.21/1000.0);
    control_points_2d[2].set(-14.78/1000.0, -76.63/1000.0);
    control_points_2d[3].set(10.46/1000.0, 64.43/1000.0);

    control_points_3d[0].set(36589.41, 25273.32, 2195.17);
    control_points_3d[1].set(37631.08, 31324.51, 728.69);
    control_points_3d[2].set(39100.97, 24934.98, 2386.50);
    control_points_3d[3].set(40426.54, 30319.81, 757.31);

//    printParameters();

///////////////////////

    preCalc();

    for(int i = 0; i < 2; i++) {
        globalIter();
    }

    printResult();


}



bool space_resection_tzx::satisfyTolerance(const double p, const double o, const double k)
{
    if(p < tolerance && o < tolerance && k < tolerance) {
        return true;
    } else {
        return false;
    }
}

Matrix space_resection_tzx::compose_X(double xs, double ys, double zs, double p, double o, double k)
{
    Matrix mat(6, 1);
    mat(1,1) = xs;
    mat(2,1) = ys;
    mat(3,1) = zs;
    mat(4,1) = p;
    mat(5,1) = o;
    mat(6,1) = k;
    return mat;
}



Matrix space_resection_tzx::compose_R(double p, double o, double k)
{
    Matrix matPhi(3, 3), matOmega(3, 3), matKappa(3, 3);
    Matrix R(3, 3);

    matPhi(1,1) = cos(p),    matPhi(1,2) = 0.0,    matPhi(1,3) = -sin(p);
    matPhi(2,1) =    0.0,    matPhi(2,2) = 1.0,    matPhi(2,3) =     0.0;
    matPhi(3,1) = sin(p),    matPhi(3,2) = 0.0,    matPhi(3,3) =  cos(p);

    matOmega(1,1) = 1.0, matOmega(1,2) =    0.0,  matOmega(1,3) =     0.0;
    matOmega(2,1) = 0.0, matOmega(2,2) = cos(o),  matOmega(2,3) = -sin(o);
    matOmega(3,1) = 0.0, matOmega(3,2) = sin(o),  matOmega(3,3) =  cos(o);

    matKappa(1,1) = cos(k), matKappa(1,2) = -sin(k),  matKappa(1,3) = 0;
    matKappa(2,1) = sin(k), matKappa(2,2) = cos(k),   matKappa(2,3) = 0;
    matKappa(3,1) = 0,          matKappa(3,2) = 0,            matKappa(3,3) = 1;

    R = matPhi * matOmega * matKappa;

    a1 = R.get(1,1); a2 = R.get(1,2); a3 = R.get(1,3);
    b1 = R.get(2,1); b2 = R.get(2,2); b3 = R.get(2,3);
    c1 = R.get(3,1); c2 = R.get(3,2); c3 = R.get(3,3);

    return R;
}

Matrix space_resection_tzx::compose_L()
{
    Matrix L(2 * num_control_points, 1);
    for(int i = 0; i < num_control_points; i++) {
        L(2 * i + 1, 1) = control_points_2d[i].getx() - control_points_2d_approx[i].getx();
        L(2 * i + 2, 1) = control_points_2d[i].gety() - control_points_2d_approx[i].gety();
    }
    return L;
}

Matrix space_resection_tzx::compose_A_onePoint(const point_2d p2d, const point_3d p3d)
{
    double xs, ys, zs, p, o, k;
    xs = Xs; ys = Ys; zs = Zs;
    p = phi; o = omega; k = kappa;

    Matrix invR = Matrix::Inv(R);
    Matrix delt(3,1);
    delt(1,1) = p3d.getX() - xs;//X - Xs
    delt(2,1) = p3d.getY() - ys;//Y - Ys
    delt(3,1) = p3d.getZ() - zs;//Z - Zs
    Matrix deltP = invR * delt;
    double dx, dy;
    dx = p2d.getx() - x0;
    dy = p2d.gety() - y0;

    Matrix A(2, 6);
    double zz = deltP.get(3, 1);
    A(1, 1) = 1/zz * (a1 * f + a3 * dx);
    A(1, 2) = 1/zz * (b1 * f + b3 * dx);
    A(1, 3) = 1/zz * (c1 * f + c3 * dx);
    A(1, 4) = dy * sin(o) - (dx / f * ( dx * cos(k) - dy * sin(k)) + f * cos(k)) * cos(o) ;
    A(1, 5) = -f * sin(k) - dx / f * (dx * sin(k) + dy * cos(k));
    A(1, 6) = dy;
    A(2, 1) = 1/zz * (a2 * f + a3 * dy);
    A(2, 2) = 1/zz * (b2 * f + b3 * dy);
    A(2, 3) = 1/zz * (c2 * f + c3 * dy);
    A(2, 4) = -dx * sin(o) - (dy / f * ( dx * cos(k) - dy * sin(k)) - f * sin(k)) * cos(o) ;
    A(2, 5) = -f * cos(k) - dy / f * (dx * sin(k) + dy * cos(k));
    A(2, 6) = -dx;
    return A;
}


///////////////////////////////////////
//    Matrix A(2, 6);
//    double x = p2d.getx();
//    double y = p2d.gety();
//    A(1, 1) = - f / H;
//    A(1, 2) =       0;
//    A(1, 3) = - x / H;
//    A(1, 4) = - f / ( 1 + x * x / f /f);
//    A(1, 5) = -x * y /f;
//    A(1, 6) =       y;
//    A(2, 1) =       0;
//    A(2, 2) = - f / H;
//    A(2, 3) = - y / H;
//    A(2, 4) = -x * y /f;
//    A(2, 5) = - f / ( 1 + y * y / f /f);
//    A(2, 6) = - x;
//    return A;


Matrix space_resection_tzx::compose_A_allPoints()
{
    Matrix A(2 * num_control_points, 6);
    for(int i = 0; i < num_control_points; i++) {
        for(int j = 0; j < 6; j++) {
            Matrix one = compose_A_onePoint(control_points_2d[i], control_points_3d[i]);
            A(2 * i + 1, j + 1) = one.get(1, j + 1);
            A(2 * i + 2, j + 1) = one.get(2, j + 1);
        }
    }

    return A;
}

double space_resection_tzx::control_points_X_even()
{
    double sum, average;
    sum = average = 0.0;
    for(int i = 0; i < num_control_points; i++) {
        sum += control_points_3d[i].getX();
    }
    average = sum/num_control_points;
    return average;
}

double space_resection_tzx::control_points_Y_even()
{
    double sum, average;
    sum = average = 0.0;
    for(int i = 0; i < num_control_points; i++) {
        sum += control_points_3d[i].getY();
    }
    average = sum/num_control_points;
    return average;
}

void space_resection_tzx::chooseMode()
{
    qDebug() <<"\n\nMode: "<<"\n\t[1]: use built-in example;"
             <<"\n\t[2]: input parameters manually;"<<"\n\t[3]: Exit\n"
             <<"\tPlease input 1, 2 or 3: ";

        char c;
        c = getchar();

        if(c == '1') {
            modeLocalExample();
        } else if (c == '2') {
            modeInputParametersManually();
        } else if (c == '3') {
            modeExit();
        } else {
            printf("Error!Please input 1, 2 or 3\n");
            chooseMode();
        }
}

void space_resection_tzx::modeLocalExample()
{
    printf("\nMode [1]: using local example: ");
}

void space_resection_tzx::modeInputParametersManually()
{

}

void space_resection_tzx::modeExit()
{

}

void space_resection_tzx::preCalc()
{
    H  = m * f;
    Xs = control_points_X_even();
    Ys = control_points_Y_even();
    Zs = H;
    X = compose_X(Xs, Ys, Zs, phi, omega, kappa);
    dX = Matrix::Ones(6,1);
    calcApprox_init();
}

void space_resection_tzx::globalIter()
{
    R = compose_R(phi, omega, kappa);
    A = compose_A_allPoints();
    L = compose_L();
    V = A * X - L;
    calcApprox_init();
//    calcAprrox_adjust();
    dX = Matrix::Inv( Matrix::Trn(A) * A ) * Matrix::Trn(A) * L;
    X = X + dX;
    X_feedBack(X);
}

void space_resection_tzx::calcApprox_init()
{
    double x, y, divide;
    double xx, yy, zz;
    for(int i = 0; i < num_control_points; i++) {

        xx = control_points_3d[i].getX();
        yy = control_points_3d[i].getY();
        zz = control_points_3d[i].getZ();

        divide =      a3 * (xx - Xs) + b3 * (yy - Ys) + c3 * (zz - Zs);
        x = x0 - f * (a1 * (xx - Xs) + b1 * (yy - Ys) + c1 * (zz - Zs)) / divide;
        y = x0 - f * (a2 * (xx - Xs) + b2 * (yy - Ys) + c2 * (zz - Zs)) / divide;
        control_points_2d_approx[i].set(x , y);
    }

}

void space_resection_tzx::calcAprrox_adjust()
{
    double xx, yy;
    for(int i = 0; i < num_control_points; i++) {
        xx = control_points_2d_approx[i].getx() + V.get(2 * i + 1, 1);
        yy = control_points_2d_approx[i].gety() + V.get(2 * i + 2, 1);
        control_points_2d_approx[i].set(xx, yy);
    }
}

void space_resection_tzx::X_feedBack(const Matrix feed)
{
    Xs =    feed.get(1, 1);
    Ys =    feed.get(2, 1);
    Zs =    feed.get(3, 1);
    phi =   feed.get(4, 1);
    omega = feed.get(5, 1);
    kappa = feed.get(6, 1);
}



double space_resection_tzx::d_phi()
{
    return dX.get(4, 1);
}

double space_resection_tzx::d_omega()
{
    return dX.get(5, 1);
}

double space_resection_tzx::d_kappa()
{
    return dX.get(6, 1);
}

void space_resection_tzx::printParameters()
{
    printf("Parameters: \n\t");
    printf("m = %f, f = %f, x0 = %f, y0 = %f \n", m, f, x0, y0);
    printf("Control Points: \n   ");
    for(int i = 0; i < num_control_points; i++) {
            control_points_2d[i].Print();
            printf("   <-->   ");
            control_points_3d[i].Print();
            printf("\n   ");
    }
}

void space_resection_tzx::printResult()
{
    printf("\nXs = \t\t%f,\nYs = \t\t%f,\nZs = \t\t%f,\nphi = \t\t%f,\nomega = \t\t%f,\nkappa = \t\t%f\n", Xs, Ys, Zs, phi, omega, kappa);
    Matrix::Trn(X).Print();
    printf("\nR: \n");
    R.Print();
}

