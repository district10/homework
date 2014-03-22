#include "matrix.h"

//constructors
Matrix::Matrix()
{
    p = NULL;
    rows = 0;
    cols = 0;
}

Matrix::Matrix(const int row_count, const int column_count)
{
    // create a Matrix object with given number of rows and columns
    p = NULL;

    if (row_count > 0 && column_count > 0)
    {
        rows = row_count;
        cols = column_count;

        p = new double*[rows];
        for (int r = 0; r < rows; r++)
        {
            p[r] = new double[cols];

            // initially fill in zeros for all values in the matrix;
            for (int c = 0; c < cols; c++)
            {
                p[r][c] = 0;
            }
        }
    }
}

// assignment operator
Matrix::Matrix(const Matrix &a)
{
    rows = a.rows;
    cols = a.cols;
    p = new double*[a.rows];
    for (int r = 0; r < a.rows; r++)
    {
        p[r] = new double[a.cols];

        // copy the values from the matrix a
        for (int c = 0; c < a.cols; c++)
        {
            p[r][c] = a.p[r][c];
        }
    }
}

// index operator. You can use this class like myMatrix(col, row)
// the indexes are one-based, not zero based.
double &Matrix::operator()(const int r, const int c)
{
    if (p != NULL && r > 0 && r <= rows && c > 0 && c <= cols)
    {
        return p[r-1][c-1];
    }
    else
    {
        throw Exception("Subscript out of range");
    }
}

double Matrix::get(const int r, const int c) const
{
    if (p != NULL && r > 0 && r <= rows && c > 0 && c <= cols)
    {
        return p[r-1][c-1];
    }
    else
    {
        throw Exception("Subscript out of range");
    }
}

Matrix &Matrix::operator=(const Matrix &a)
{
    rows = a.rows;
    cols = a.cols;
    p = new double*[a.rows];
    for (int r = 0; r < a.rows; r++)
    {
        p[r] = new double[a.cols];

        // copy the values from the matrix a
        for (int c = 0; c < a.cols; c++)
        {
            p[r][c] = a.p[r][c];
        }
    }
    return *this;
}

Matrix &Matrix::Add(const double v)
{
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            p[r][c] += v;
        }
    }
    return *this;
}

Matrix &Matrix::Subtract(const double v)
{
    return Add(-v);
}

Matrix &Matrix::Multiply(const double v)
{
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            p[r][c] *= v;
        }
    }
    return *this;
}

Matrix &Matrix::Divide(const double v)
{
    return Multiply(1/v);
}

Matrix Matrix::Trn(const Matrix &a)
{
    Matrix mat = Matrix(a.GetCols(), a.GetRows());
    for( int i = 0; i < a.GetCols(); i++ ) {
        for( int j = 0; j < a.GetRows(); j++ ) {
            mat(i+1, j+1) = a.get(j+1 , i+1);
        }
    }
    return mat;
}

Matrix Matrix::Minor(const int row, const int col) const
{
    Matrix res;
    if (row > 0 && row <= rows && col > 0 && col <= cols)
    {
        res = Matrix(rows - 1, cols - 1);

        // copy the content of the matrix to the minor, except the selected
        for (int r = 1; r <= (rows - (row >= rows)); r++)
        {
            for (int c = 1; c <= (cols - (col >= cols)); c++)
            {
                res(r - (r > row), c - (c > col)) = p[r-1][c-1];
            }
        }
    }
    else
    {
        throw Exception("Index for minor out of range");
    }

    return res;
}

int Matrix::Size(const int i) const
{
    if (i == 1)
    {
        return rows;
    }
    else if (i == 2)
    {
        return cols;
    }
    return 0;
}

void Matrix::Print() const
{
    printf("\n[");
    if (p != NULL)
    {

        for (int r = 0; r < rows; r++)
        {
            if (r > 0)
            {
                printf(" ");
            }
            for (int c = 0; c < cols-1; c++)
            {
                printf("%.3f, ", p[r][c]);
            }
            if (r < rows-1)
            {
                printf("%.3f;\n\n", p[r][cols-1]);
            }
            else
            {
                printf("%.3f", p[r][cols-1]);
            }
        }

    }
    printf("]\n");
}

void Matrix::PrintRowCol()
{
    printf("(%d, %d)",this->GetRows(), this->GetCols());
}

Matrix Matrix::Ones(const int rows, const int cols)
{
    Matrix res = Matrix(rows, cols);

    for (int r = 1; r <= rows; r++)
    {
        for (int c = 1; c <= cols; c++)
        {
            res(r, c) = 1;
        }
    }
    return res;
}



Matrix Matrix::Zeros(const int rows, const int cols)
{
    return Matrix(rows, cols);
}

Matrix Matrix::Diag(const int n)
{
    Matrix res = Matrix(n, n);
    for (int i = 1; i <= n; i++)
    {
        res(i, i) = 1;
    }
    return res;
}

Matrix Matrix::Diag(const Matrix &v)
{
    Matrix res;
    if (v.GetCols() == 1)
    {
        // the given matrix is a vector n x 1
        int rows = v.GetRows();
        res = Matrix(rows, rows);

        // copy the values of the vector to the matrix
        for (int r=1; r <= rows; r++)
        {
            res(r, r) = v.get(r, 1);
        }
    }
    else if (v.GetRows() == 1)
    {
        // the given matrix is a vector 1 x n
        int cols = v.GetCols();
        res = Matrix(cols, cols);

        // copy the values of the vector to the matrix
        for (int c=1; c <= cols; c++)
        {
            res(c, c) = v.get(1, c);
        }
    }
    else
    {
        throw Exception("Parameter for diag must be a vector");
    }
    return res;
}

double Matrix::Det(const Matrix &a)
{
    double d = 0;    // value of the determinant
    int rows = a.GetRows();
    int cols = a.GetRows();

    if (rows == cols)
    {
        // this is a square matrix
        if (rows == 1)
        {
            // this is a 1 x 1 matrix
            d = a.get(1, 1);
        }
        else if (rows == 2)
        {
            // this is a 2 x 2 matrix
            // the determinant of [a11,a12;a21,a22] is det = a11*a22-a21*a12
            d = a.get(1, 1) * a.get(2, 2) - a.get(2, 1) * a.get(1, 2);
        }
        else
        {
            // this is a matrix of 3 x 3 or larger
            for (int c = 1; c <= cols; c++)
            {
                Matrix M = a.Minor(1, c);
                //d += pow(-1, 1+c) * a(1, c) * Det(M);
                d += (c%2 + c%2 - 1) * a.get(1, c) * Det(M); // faster than with pow()
            }
        }
    }
    else
    {
        throw Exception("Matrix must be square");
    }
    return d;

}

Matrix Matrix::Inv(const Matrix &a)
{
    Matrix res;
    double d = 0;    // value of the determinant
    int rows = a.GetRows();
    int cols = a.GetRows();

    d = Det(a);

    if (rows == cols && d != 0)
    {
        // this is a square matrix
        if (rows == 1)
        {
            // this is a 1 x 1 matrix
            res = Matrix(rows, cols);
            res(1, 1) = 1 / a.get(1, 1);
        }
        else if (rows == 2)
        {
            // this is a 2 x 2 matrix
            res = Matrix(rows, cols);
            res(1, 1) = a.get(2, 2);
            res(1, 2) = -a.get(1, 2);
            res(2, 1) = -a.get(2, 1);
            res(2, 2) = a.get(1, 1);
            res = (1/d) * res;
        }
        else
        {
            // this is a matrix of 3 x 3 or larger
            // calculate inverse using gauss-jordan elimination
            //   http://mathworld.wolfram.com/MatrixInverse.html
            //   http://math.uww.edu/~mcfarlat/inverse.htm
            res = Diag(rows);   // a diagonal matrix with ones at the diagonal
            Matrix ai = a;    // make a copy of Matrix a

            for (int c = 1; c <= cols; c++)
            {
                // element (c, c) should be non zero. if not, swap content
                // of lower rows
                int r;
                for (r = c; r <= rows && ai(r, c) == 0; r++)
                {
                }
                if (r != c)
                {
                    // swap rows
                    for (int s = 1; s <= cols; s++)
                    {
                        Swap(ai(c, s), ai(r, s));
                        Swap(res(c, s), res(r, s));
                    }
                }

                // eliminate non-zero values on the other rows at column c
                for (int r = 1; r <= rows; r++)
                {
                    if(r != c)
                    {
                        // eleminate value at column c and row r
                        if (ai(r, c) != 0)
                        {
                            double f = - ai(r, c) / ai(c, c);

                            // add (f * row c) to row r to eleminate the value
                            // at column c
                            for (int s = 1; s <= cols; s++)
                            {
                                ai(r, s) += f * ai(c, s);
                                res(r, s) += f * res(c, s);
                            }
                        }
                    }
                    else
                    {
                        // make value at (c, c) one,
                        // divide each value on row r with the value at ai(c,c)
                        double f = ai(c, c);
                        for (int s = 1; s <= cols; s++)
                        {
                            ai(r, s) /= f;
                            res(r, s) /= f;
                        }
                    }
                }
            }
        }
    }
    else
    {
        if (rows != cols)
        {
            throw Exception("Matrix must be square");
        }
        else
        {
            throw Exception("Determinant of matrix is zero");
        }
    }

    return res;
}

Matrix operator+(const Matrix &a, const double b)
{
    Matrix res = a;
    res.Add(b);
    return res;
}

Matrix operator+(const double b, const Matrix &a)
{
    Matrix res = a;
    res.Add(b);
    return res;
}

Matrix operator-(const Matrix &a, const Matrix &b)
{
    // check if the dimensions match
    if (a.rows == b.rows && a.cols == b.cols)
    {
        Matrix res(a.rows, a.cols);

        for (int r = 0; r < a.rows; r++)
        {
            for (int c = 0; c < a.cols; c++)
            {
                res.p[r][c] = a.p[r][c] - b.p[r][c];
            }
        }
        return res;
    }
    else
    {
        // give an error
        throw Exception("Dimensions does not match");
    }

    // return an empty matrix (this never happens but just for safety)
    return Matrix();
}

Matrix operator+(const Matrix &a, const Matrix &b)
{
    // check if the dimensions match
    if (a.rows == b.rows && a.cols == b.cols)
    {
        Matrix res(a.rows, a.cols);

        for (int r = 0; r < a.rows; r++)
        {
            for (int c = 0; c < a.cols; c++)
            {
                res.p[r][c] = a.p[r][c] + b.p[r][c];
            }
        }
        return res;
    }
    else
    {
        // give an error
        throw Exception("Dimensions does not match");
    }

    // return an empty matrix (this never happens but just for safety)
    return Matrix();
}


Matrix operator- (const Matrix& a, const double b)
{
    Matrix res = a;
    res.Subtract(b);
    return res;
}

Matrix operator- (const double b, const Matrix& a)
{
    Matrix res = -a;
    res.Add(b);
    return res;
}

Matrix operator- (const Matrix& a)
{
    Matrix res(a.rows, a.cols);

    for (int r = 0; r < a.rows; r++)
    {
        for (int c = 0; c < a.cols; c++)
        {
            res.p[r][c] = -a.p[r][c];
        }
    }

    return res;
}

Matrix operator* (const Matrix& a, const Matrix& b)
{
    // check if the dimensions match
    if (a.cols == b.rows)
    {
        Matrix res(a.rows, b.cols);

        for (int r = 0; r < a.rows; r++)
        {
            for (int c_res = 0; c_res < b.cols; c_res++)
            {
                for (int c = 0; c < a.cols; c++)
                {
                    res.p[r][c_res] += a.p[r][c] * b.p[c][c_res];
                }
            }
        }
        return res;
    }
    else
    {
        // give an error
        throw Exception("Dimensions does not match");
    }

    // return an empty matrix (this never happens but just for safety)
    return Matrix();
}



Matrix operator* (const Matrix& a, const double b)
{
    Matrix res = a;
    res.Multiply(b);
    return res;
}

Matrix operator* (const double b, const Matrix& a)
{
    Matrix res = a;
    res.Multiply(b);
    return res;
}

Matrix operator/ (const Matrix& a, const Matrix& b)

{
    Matrix tmp;
    // check if the dimensions match: must be square and equal sizes
    if (a.rows == a.cols && a.rows == b.cols && b.rows == b.cols)
    {
        Matrix res(a.rows, a.cols);

        res = a * tmp.Inv(b);

        return res;
    }
    else
    {
        // give an error
        throw Exception("Dimensions does not match");
    }

    // return an empty matrix (this never happens but just for safety)
    return Matrix();
}

Matrix operator/ (const Matrix& a, const double b)
{
    Matrix res = a;
    res.Divide(b);
    return res;
}

Matrix operator/ (const double b, const Matrix& a)
{
    Matrix b_matrix(1, 1);
    b_matrix(1,1) = b;

    Matrix res = b_matrix / a;
    return res;
}

int Size(const Matrix& a, const int i)
{
    return a.Size(i);
}

void Matrix::Swap(double& a, double& b)
{
    double temp = a;
    a = b;
    b = temp;
}
