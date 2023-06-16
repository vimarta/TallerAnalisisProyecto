#include "../include/Matrix.h"
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

Matrix::Matrix(int fil, int col) : fil(fil), col(col)
{
    initMatrix();
}
 
Matrix::Matrix(int fil, int col, double v[], int n): fil(fil), col(col)
{
    initMatrix();
 
    int k = 0;
    
    for (int i = 0; i < fil; i++)
        for (int j = 0; j < col; j++){
            if (k < n)
                matrix[i][j] = v[k++];
            else
                matrix[i][j] = 0;
        }
}

Matrix::Matrix(int fil, int col, vector<vector<double>> v): fil(fil), col(col)
{
    initMatrix();

    int k = 0;

    for (int i = 0; i < fil; i++)
        for (int j = 0; j < col; j++){
            matrix[i][j] = v[i][j];
        }
}

Matrix::Matrix(int fil, int col, double **m): fil(fil), col(col)
{
    initMatrix();

    int k = 0;

    for (int i = 0; i < fil; i++)
        for (int j = 0; j < col; j++){
            matrix[i][j] = m[i][j];
        }
}
 
Matrix::Matrix(const Matrix& m)
{
    *this = m;
}

Matrix::Matrix(int n): fil(n), col(1)
{
    initMatrix();
}

Matrix::~Matrix()
{
    for (int i = 0; i < fil; i++)
        delete[] matrix[i];
 
    delete[] matrix;
}
 
void Matrix::initMatrix()
{
    matrix = new double*[fil];
    for (int i = 0; i < fil; i++)
        matrix[i] = new double[col];
 
    for (int i = 0; i < fil; i++)
        for (int j = 0; j < col; j++)
            matrix[i][j] = 0.0;
}
 
Matrix& Matrix::operator=(const Matrix& matrix2)
{
    this->fil = matrix2.fil;
    this->col = matrix2.col;
    initMatrix();

    for (int i = 0; i < fil; i++)
        for (int j = 0; j < col; j++)
            this->matrix[i][j] = matrix2.matrix[i][j];
 
    return *this;
}
 
Matrix Matrix::operator+(const Matrix& matrix2)
{
    Matrix result(fil, col);
    
    for (int i = 0; i < fil; i++)
        for (int j = 0; j < col; j++)
            result.matrix[i][j] = matrix[i][j] + matrix2.matrix[i][j];
 
    return result;
}
 
Matrix Matrix::operator-(const Matrix& matrix2)
{
    Matrix result(fil, col);
    
    for (int i = 0; i < fil; i++)
        for (int j = 0; j < col; j++)
            result.matrix[i][j] = matrix[i][j] - matrix2.matrix[i][j];
 
    return result;
}
 
Matrix Matrix::operator*(const Matrix& matrix2)
{
    Matrix result(fil, matrix2.col);
 
    for (int i = 0; i < this->fil ; i++){
        for (int j = 0; j < matrix2.col; j++){
            result.matrix[i][j] = 0;
            for (int k = 0; k < this->col; k++){
                result.matrix[i][j] = result.matrix[i][j] + this->matrix[i][k] * matrix2.matrix[k][j];
            }
        }
    }
 
    return result;
}

Matrix Matrix::operator*(const double& a)
{
    Matrix result(fil, col);

    for (int i = 0; i < this->fil ; i++){
        for (int j = 0; j < this->col; j++){
                result.matrix[i][j] = this->matrix[i][j] * a;
        }
    }

    return result;
}

Matrix Matrix::operator/(const double& a)
{
    Matrix result(fil, col);

    for (int i = 0; i < this->fil ; i++){
        for (int j = 0; j < this->col; j++){
            result.matrix[i][j] = this->matrix[i][j] / a;
        }
    }

    return result;
}
 
 
double& Matrix::operator()(const int i, const int j) const
{
    return matrix[i][j];
}
 
void Matrix::print()
{
    for (int i = 0; i < fil; i++){
        for (int j = 0; j < col; j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

double Matrix::norm(Matrix m){
    double sum = 0;

    for(int i = 0; i < 3; i++){
        sum += m(i,0)*m(i,0);
    }
    return sqrt(sum);
}

Matrix Matrix::traspuesta() {

    Matrix traspuesta(col, fil);

    for (int i = 0; i < fil; i++) {
        for (int j = 0; j < col; j++) {
            traspuesta(j,i) = matrix[i][j];
        }
    }

    return traspuesta;
}

int Matrix::length() {
    return(max(fil,col));
}

double Matrix::dot(Matrix m1, Matrix m2){
    double pr = 0.0;

    for(int i = 0; i < m1.fil; i++){
        pr += m1(i,0)*m2(i,0);
    }
    return (pr);
}

Matrix Matrix::cross(Matrix m1, Matrix m2){
    Matrix result(3);
    for (int i = 0; i < m1.length(); i++) {
        result(i,0) = m1((i + 1) % 3, 0) * m2((i + 2) % 3,0) - m1((i + 2) % 3,0) * m2((i + 1) % 3,0);
    }
    return result;
}