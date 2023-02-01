#ifndef SRC_sfleta_MATRIX_OOP_H_
#define SRC_sfleta_MATRIX_OOP_H_

#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>

using std::invalid_argument;
using std::out_of_range;
using std::vector;

class sfleta_Matrix {
 private:
    int _rows, _cols;
    double** _matrix;

 public:
    // Конструкторы и деструкторы
    sfleta_Matrix();
    sfleta_Matrix(int rows, int cols);
    sfleta_Matrix(const sfleta_Matrix& other);
    sfleta_Matrix(sfleta_Matrix&& other);
    ~sfleta_Matrix();

    // Операции над матрицами
    bool eq_matrix(const sfleta_Matrix& other);
    void sum_matrix(const sfleta_Matrix& other);
    void sub_matrix(const sfleta_Matrix& other);
    void mul_number(const double num);
    void mul_matrix(const sfleta_Matrix& other);
    sfleta_Matrix transpose();
    double determinant();
    sfleta_Matrix calc_complements();
    sfleta_Matrix inverse_matrix();

    // Акцессоры, мутаторы
    inline int getRows() { return _rows; }
    inline int getCols() { return _cols; }
    void setRows(int rowsCount);
    void setCols(int colsCount);
    void setElem(int i, int j, double value);
    double getElem(int i, int j);

    // Операторы
    sfleta_Matrix operator+(const sfleta_Matrix &other);
    sfleta_Matrix operator-(const sfleta_Matrix &other);
    sfleta_Matrix operator*(const sfleta_Matrix &other);
    sfleta_Matrix operator*(const double num);
    friend sfleta_Matrix operator*(const double num, const sfleta_Matrix &other);
    bool operator==(const sfleta_Matrix &other);
    sfleta_Matrix& operator=(const sfleta_Matrix &other);
    void operator+=(const sfleta_Matrix &other);
    void operator-=(const sfleta_Matrix &other);
    void operator*=(const sfleta_Matrix &other);
    void operator*=(const double num);
    double operator()(int i, int j);

// Дополнительные функции
 private:
    void remove_matrix();
    sfleta_Matrix getSubMatrix(int rowForDelete, int columnForDelete);

 public:
    double** allocateMemory(int rows, int cols);
    bool isEqual(double a, double b);
    void print_Matrix();
    void fill_matrix_from_vector(vector<double> vect);
};
sfleta_Matrix operator*(const double num, const sfleta_Matrix &other);

#endif  // SRC_sfleta_MATRIX_OOP_H_
