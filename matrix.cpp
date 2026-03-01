/**
 * @file matrix.cpp
 * @author Xavier
 * @brief implimentation of matrix object
 * @version 0.1
 * @date 2026-02-26
 * 
 * @copyright Copyright (c) 2026
 * 
 */

//includes
#include <string>
#include <sstream>
#include <iomanip>
#include "matrix.h"

using namespace std;

//Constructor
Matrix::Matrix(unsigned int rows, unsigned int columns): m(rows), n(columns){
    //**ar=nullptr; if this doesn't work, make this not a comment
    ar = new double*[m];
    for (int i=0; i<rows; i++){
        ar[i]=new double[n];
        for (int j = 0; j<n; j++){
            ar[i][j]=0.0;
        }
    }
}


//Copy constructor
Matrix::Matrix(const Matrix& rhs):m(rhs.m), n(rhs.n){
    ar = new double*[m];
    for (int i=0; i<m; i++){
        ar[i]=new double[n];
        for (unsigned int j = 0; j < n; j++) {
            ar[i][j] = rhs.ar[i][j];
        }
    }
}

//Delete
Matrix::~Matrix(){
    for (int i=0; i<m; i++){
        delete[] ar[i];
    }
    delete[] ar;
}

//the gets
int Matrix::getRows() const{
    return m;
}
int Matrix::getCols() const{
    return n;
}

//at
double& Matrix::at(unsigned int row, unsigned int col){return ar[row][col];}

//at (const)
const double& Matrix::at(unsigned int row, unsigned int col) const {return ar[row][col];}

//operator=
Matrix& Matrix::operator=(const Matrix& rhs){
    if (this == &rhs) return *this;
    m = rhs.m;
    n = rhs.n;

    ar = new double*[m];
    for (int i=0; i<m; i++){
        ar[i]=new double[n];
        for (unsigned int j = 0; j < n; j++) {
            ar[i][j] = rhs.ar[i][j];
        }
    }
    return *this;
}


//Adding
Matrix operator+(const Matrix& m1, const Matrix& m2){
    //Creates the matrix for the sum
    Matrix result(m1.getRows(), m1.getCols());
    for (int i = 0; i < m1.getRows(); ++i) {
        for (int j = 0; j < m1.getCols(); ++j) {
            result.at(i, j) = m1.at(i, j) + m2.at(i, j);
        }
    }
    return result;
}

//Subtracting
Matrix operator-(const Matrix& m1, const Matrix& m2){
    //Creates the matrix for the difference
    Matrix result(m1.getRows(), m1.getCols());
    for (int i = 0; i < m1.getRows(); ++i) {
        for (int j = 0; j < m1.getCols(); ++j) {
            result.at(i, j) = m1.at(i, j) - m2.at(i, j);
        }
    }
    return result;
}

//mult
Matrix operator*(const Matrix& m1, const Matrix& m2){
    //Creates the matrix for the product
    Matrix result(m1.getRows(), m1.getCols());
    for (int i = 0; i < m1.getRows(); ++i) {
        for (int j = 0; j < m1.getCols(); ++j) {
            result.at(i, j) = 0;
            for (int k=0;k<m1.getCols(); ++k){
                result.at(i,j) = result.at(i,j) + (m1.at(i,k)*m2.at(k,j));
            }
        }
    }
    return result;
}

//Scalar Mult 1
Matrix operator*(double scalar, const Matrix& m){
    Matrix result(m.getRows(), m.getCols());
    for (int i=0; i<m.getRows(); i++){
        for (int j=0; j<m.getCols(); j++){
            result.at(i,j) = scalar*m.at(i,j);
        }
    }
    return result;
}

//scalar mult 2
Matrix operator*(const Matrix& m, double scalar){
    Matrix result(m.getRows(), m.getCols());
    for (int i=0; i<m.getRows(); i++){
        for (int j=0; j<m.getCols(); j++){
            result.at(i,j) = m.at(i,j)*scalar;
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m){
    for (int i=0; i<m.getRows(); i++){
        for (int j=0; j<m.getCols(); j++){
            os << setw(10) << m.at(i,j) << " ";
        }
        os << endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Matrix& m){
    for (int i=0; i<m.getRows(); i++){
        for (int j=0; j<m.getCols(); j++){
            is >> m.at(i,j);
        }
    }
    return is;
}