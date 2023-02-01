#ifndef SRC_sfleta_MATRIX_OOP_H_
#define SRC_sfleta_MATRIX_OOP_H_

#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>

using std::invalid_argument;
using std::out_of_range;
using std::vector;

class S21Matrix {
 private:
    int _rows, _cols;
    double** _matrix;

 public:
    // Конструкторы и деструкторы
    S21Matrix();
    S21Matrix(int rows, int cols);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other);
    ~S21Matrix();

    // Операции над матрицами
    bool eq_matrix(const S21Matrix& other);
    void sum_matrix(const S21Matrix& other);
    void sub_matrix(const S21Matrix& other);
    void mul_number(const double num);
    void mul_matrix(const S21Matrix& other);
    S21Matrix transpose();
    double determinant();
    S21Matrix calc_complements();
    S21Matrix inverse_matrix();

    // Акцессоры, мутаторы
    inline int getRows() { return _rows; }
    inline int getCols() { return _cols; }
    void setRows(int rowsCount);
    void setCols(int colsCount);
    void setElem(int i, int j, double value);
    double getElem(int i, int j);

    // Операторы
    S21Matrix operator+(const S21Matrix &other);
    S21Matrix operator-(const S21Matrix &other);
    S21Matrix operator*(const S21Matrix &other);
    S21Matrix operator*(const double num);
    friend S21Matrix operator*(const double num, const S21Matrix &other);
    bool operator==(const S21Matrix &other);
    S21Matrix& operator=(const S21Matrix &other);
    void operator+=(const S21Matrix &other);
    void operator-=(const S21Matrix &other);
    void operator*=(const S21Matrix &other);
    void operator*=(const double num);
    double operator()(int i, int j);

// Дополнительные функции
 private:
    void remove_matrix();
    S21Matrix getSubMatrix(int rowForDelete, int columnForDelete);

 public:
    double** allocateMemory(int rows, int cols);
    bool isEqual(double a, double b);
    void print_Matrix();
    void fill_matrix_from_vector(vector<double> vect);
};
S21Matrix operator*(const double num, const S21Matrix &other);

#endif  // SRC_sfleta_MATRIX_OOP_H_
