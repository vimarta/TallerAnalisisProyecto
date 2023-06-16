#ifndef _MATRIX_
#define _MATRIX_
#include <vector>
using namespace std;

class Matrix
{
    public:
        Matrix(int fil, int col);
        Matrix(int fil, int col, double v[], int n);
        Matrix(int fil, int col, vector<vector<double>> v);
        Matrix(const Matrix& m);
        Matrix(int n);
        Matrix(int fil, int col, double **m);
        ~Matrix();
 
        Matrix& operator=(const Matrix& matrix2);
        Matrix  operator+(const Matrix& matrix2);
        Matrix  operator-(const Matrix& matrix2);
        Matrix  operator*(const Matrix& matrix2);
        Matrix  operator*(const double& a);
        Matrix  operator/(const double& a);
        double& operator()(const int i, const int j) const;
        Matrix traspuesta();
        int length();

        static double norm(Matrix m);
        static double dot(Matrix m1, Matrix m2);
        static Matrix cross(Matrix m1, Matrix m2);
 
        void print();
 
    private:
        void initMatrix();
 
    private:
        int fil;
        int col;
        double **matrix;
};

#endif
