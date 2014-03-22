/* adapted from a matrix class on the Internet
 from : http://www.speqmath.com/tutorials/matrix/matrix.html

 reorginazed by    tangzhixiong
                   RS, WHU
                   2013/09/26
*///there is the original statements
/*
A simple matrix class
c++ code
Author: Jos de Jong, Nov 2007. Updated March 2010

With this class you can:
  - create a 2D matrix with custom size
  - get/set the cell values
  - use operators +, -, *, /
  - use functions Ones(), Zeros(), Diag(), Det(), Inv(), Size()
  - print the content of the matrix

Usage:
  you can create a matrix by:
    Matrix A;
    Matrix A = Matrix(rows, cols);
    Matrix A = B;

  you can get and set matrix elements by:
    A(2,3) = 5.6;    // set an element of Matix A
    value = A(3,1);   // get an element of Matrix A
    value = A.get(3,1); // get an element of a constant Matrix A
    A = B;        // copy content of Matrix B to Matrix A

  you can apply operations with matrices and doubles:
    A = B + C;
    A = B - C;
    A = -B;
    A = B * C;
    A = B / C;

  the following functions are available:
    A = Ones(rows, cols);
    A = Zeros(rows, cols);
    A = Diag(n);
    A = Diag(B);
    d = Det(A);
    A = Inv(B);
    cols = A.GetCols();
    rows = A.GetRows();
    cols = Size(A, 1);
    rows = Size(A, 2);

  you can quick-print the content of a matrix in the console with:
    A.Print();
*/

#ifndef MATRIX_H
#define MATRIX_H
#include "exception.h"
#include "point_2d.h"
#include "point_3d.h"
#include <cstdlib>
#include <cstdio>
#include <math.h>

#define PAUSE {printf("Press \"Enter\" to continue\n"); fflush(stdin); getchar(); fflush(stdin);}

class Matrix
{
public:
    Matrix();
    Matrix(const int row_count, const int column_count);
    Matrix(const Matrix& a);

    double& operator()(const int r, const int c);
    double get(const int r, const int c) const;

    Matrix& operator= (const Matrix& a);
    Matrix& Add(const double v);
    Matrix& Subtract(const double v);
    Matrix& Multiply(const double v);
    Matrix& Divide(const double v);


    friend Matrix operator+(const Matrix& a, const Matrix& b);
    friend Matrix operator+ (const Matrix& a, const double b);
    friend Matrix operator+ (const double b, const Matrix& a);
    friend Matrix operator- (const Matrix& a, const Matrix& b);
    friend Matrix operator- (const Matrix& a, const double b);
    friend Matrix operator- (const double b, const Matrix& a);
    friend Matrix operator- (const Matrix& a);
    friend Matrix operator* (const Matrix& a, const Matrix& b);
    friend Matrix operator* (const Matrix& a, const double b);
    friend Matrix operator* (const double b, const Matrix& a);
    friend Matrix operator/ (const Matrix& a, const Matrix& b);
    friend Matrix operator/ (const Matrix& a, const double b);
    friend Matrix operator/ (const double b, const Matrix& a);


    /**
         * returns the minor from the given matrix where
         * the selected row and column are removed
         */
    Matrix Minor(const int row, const int col) const;

    /*
         * returns the size of the i-th dimension of the matrix.
         * i.e. for i=1 the function returns the number of rows,
         * and for i=2 the function returns the number of columns
         * else the function returns 0
         */
    int Size(const int i) const;

    int GetRows() const
    {
        return rows;
    }

    // returns the number of columns
    int GetCols() const
    {
        return cols;
    }

    // print the contents of the matrix
    void Print() const;
    void PrintRowCol();

public:
    // destructor
    ~Matrix()
    {
        // clean up allocated memory
        for (int r = 0; r < rows; r++)
        {
            delete p[r];
        }
        delete p;
        p = NULL;
    }

    static Matrix Ones(const int rows, const int cols);
    static Matrix Zeros(const int rows, const int cols);
    static Matrix Diag(const int n);
    static Matrix Diag(const Matrix& v);
    static double Det(const Matrix& a);
    static Matrix Inv(const Matrix& a);
    static void Swap(double& a, double& b);
    static Matrix Trn(const Matrix& a);

private:
    int rows;
    int cols;
    double **p;
};



#endif // MATRIX_H
