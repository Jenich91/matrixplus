#include "sfleta_matrix_oop.h"
// *** Конструкторы и деструкторы *** //

// Базовый конструктор, инициализирующий матрицу некоторой заранее заданной размерностью
sfleta_Matrix::sfleta_Matrix() {
    _rows = 1;
    _cols = 1;
    _matrix = allocateMemory(1, 1);
    _matrix[0][0] = 0;
}

// Параметризированный конструктор с количеством строк и столбцов
sfleta_Matrix::sfleta_Matrix(int rows, int cols) : _rows(rows), _cols(cols) {
    _matrix = nullptr;
    if (rows < 1 || cols < 1) {
        throw invalid_argument("wrong matrix size");
    }
    _matrix = allocateMemory(rows, cols);
}

// Конструктор копирования
sfleta_Matrix::sfleta_Matrix(const sfleta_Matrix &other) : _rows(other._rows), _cols(other._cols) {
    _matrix = allocateMemory(_rows, _cols);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            _matrix[i][j] = other._matrix[i][j];
        }
    }
}

// Конструктор переноса
sfleta_Matrix::sfleta_Matrix(sfleta_Matrix&& other) : _rows(other._rows), _cols(other._cols), _matrix(other._matrix) {
    other._rows = 0;
    other._cols = 0;
    other._matrix = nullptr;
}

// Деструктор
sfleta_Matrix::~sfleta_Matrix() {
    remove_matrix();
}

// *** Акцессоры, мутаторы rows и columns *** //

// Mutator, изменение элемента по индексу
void sfleta_Matrix::setElem(int newRows, int newCols, double value) {
    if (newRows < 0 || newRows >= _rows || newCols < 0 || newCols >= _cols) {
        throw out_of_range("Array index out of bound");
    }
    _matrix[newRows][newCols] = value;
}

// Accessor, чтение элемента по индексу
double sfleta_Matrix::getElem(int newRows, int newCols) {
    return _matrix[newRows][newCols];
}

// Mutator, изменение колличества строк
void sfleta_Matrix::setRows(int rowsCount) {
    if (rowsCount < 1) {
        throw invalid_argument("Invalid rows");
    }

    if (rowsCount < _rows) {
        for (int i = rowsCount; i < _rows; i++) {
            delete[] _matrix[i];
            _matrix[i] = NULL;
        }
        _rows = rowsCount;
    } else if (rowsCount > _rows) {
        sfleta_Matrix newMatrix(rowsCount, _cols);

        for (int i = 0; i < rowsCount; i++) {
            if (i < _rows) {
                memcpy(newMatrix._matrix[i], _matrix[i], sizeof(double) * _cols);
            } else {
                for (int j = 0; j < _cols; j++) {
                    newMatrix._matrix[i][j] = 0;
                }
            }
        }

        *this = newMatrix;
    }
}

// Mutator, изменение колличества столбцов
void sfleta_Matrix::setCols(int colsCount) {
    if (colsCount < 1) {
        throw invalid_argument("Invalid cols");
    }
    if (colsCount < _cols) {
    _cols = colsCount;
    } else if (colsCount > _cols) {
        sfleta_Matrix newMatrix(_rows, colsCount);
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < colsCount; j++) {
                if (j < _cols) {
                    newMatrix._matrix[i][j] = _matrix[i][j];
                } else {
                    newMatrix._matrix[i][j] = 0;
                }
            }
        }

        *this = newMatrix;
    }
}

// *** Операции над матрицами *** //

// Проверяет матрицы на равенство между собой
bool sfleta_Matrix::eq_matrix(const sfleta_Matrix& other) {
    if (_cols != other._cols || _rows != other._rows) {
        return false;
    }

    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            if (!isEqual(_matrix[i][j], other._matrix[i][j])) {
                return false;
            }
        }
    }
    return true;
}

// Сравнение вещественных чисел через эпсилон
bool sfleta_Matrix::isEqual(double src1, double src2) {
    if (fabs(src1 - src2) < 1e-6) {
        return true;
    }
    return false;
}

// Прибавляет вторую матрицы к текущей
void sfleta_Matrix::sum_matrix(const sfleta_Matrix &other) {
    if (_rows != other._rows || _cols != other._cols) {
        throw invalid_argument("Different dimensions of matrices");
    }

    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            _matrix[i][j] = _matrix[i][j] + other._matrix[i][j];
        }
    }
}

// Вычитает из текущей матрицы другую
void sfleta_Matrix::sub_matrix(const sfleta_Matrix &other) {
    if (_rows != other._rows || _cols != other._cols) {
        throw invalid_argument("Different dimensions of matrices");
    }

    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            _matrix[i][j] = _matrix[i][j] - other._matrix[i][j];
        }
    }
}

// Умножает текущую матрицу на число
void sfleta_Matrix::mul_number(const double num) {
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            if (isEqual(num, 0) || isEqual(_matrix[i][j], -0)) {
                _matrix[i][j] = 0;
            } else {
                _matrix[i][j] = _matrix[i][j] * num;
            }
        }
    }
}

// Умножает текущую матрицу на вторую
void sfleta_Matrix::mul_matrix(const sfleta_Matrix &other) {
    if (_rows != other._cols || _cols != other._rows) {
        throw invalid_argument
        ("The rows/columns count first matrix is not equal rows/columns of the second matrix");
    }

    sfleta_Matrix tempMatrix(_rows, _cols);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            tempMatrix._matrix[i][j] = 0.0f;
            for (int k = 0; k < other._cols; k++) {
                tempMatrix._matrix[i][j] += _matrix[i][k] * other._matrix[k][j];
            }
        }
    }

    *this = tempMatrix;
}

// Создает новую транспонированную матрицу из текущей и возвращает ее
sfleta_Matrix sfleta_Matrix::transpose() {
    sfleta_Matrix resultMatrix(_rows, _cols);

    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            resultMatrix._matrix[j][i] = _matrix[i][j];
        }
    }
    return resultMatrix;
}

// Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает ее
sfleta_Matrix sfleta_Matrix::calc_complements() {
        if (_rows != _cols) {
            throw invalid_argument("matrix is not square");
        }

        sfleta_Matrix resultMatrix(_rows, _cols);

        for (int i = 0; i < _cols; i++)  {
            for (int j = 0; j < _cols; j++) {
                sfleta_Matrix subMatrix = getSubMatrix(i, j);
                resultMatrix._matrix[i][j] = pow(-1, ((j+1)+(i+1))) * subMatrix.determinant();
            }
        }

    return resultMatrix;
}

// Вычисляет и возвращает определитель текущей матрицы
double sfleta_Matrix::determinant() {
    double determinant = nan("");

    if (_rows != _cols) {
        throw invalid_argument("matrix is not square");
    }

    int size = _cols;
    if (size == 1) {
        determinant = _matrix[0][0];
    } else if (size == 2) {
        determinant = (_matrix[0][0] * _matrix[1][1]) - (_matrix[1][0] * _matrix[0][1]);
    } else if (size > 2) {
        determinant = 0;
        int sign = 1;

        for (int i = 0; i < size; i++) {
            sfleta_Matrix newMatrix = getSubMatrix(i, 0);

            determinant = determinant + sign * _matrix[i][0] * newMatrix.determinant();
            sign =- sign;
        }
    }

    return determinant;
}

// Вычисляет и возвращает обратную матрицу
sfleta_Matrix sfleta_Matrix::getSubMatrix(int rowForDelete, int columnForDelete) {
    sfleta_Matrix subMatrix(_rows-1, _cols-1);

    int offsetRow = 0;
    for (int i = 0; i < _rows-1; i++) {
        if ((int)i == rowForDelete) {
            offsetRow = 1;
        }
        int offsetCollum = 0;
        for (int j = 0; j < _cols-1; j++)  {
            if (j == columnForDelete) {
                offsetCollum = 1;
            }
            subMatrix._matrix[i][j] = _matrix[i + offsetRow][j + offsetCollum];
        }
    }

    return subMatrix;
}

//  Вычисляет и возвращает обратную матрицу
sfleta_Matrix sfleta_Matrix::inverse_matrix() {
    double det = determinant();

    if (isEqual(det, 0) || std::isnan(det)) {
        throw invalid_argument("Inverse matrix does not exist, matrix determinant is 0");
    }

    sfleta_Matrix resultMatrix = calc_complements().transpose();
    resultMatrix.mul_number(1/det);
    return resultMatrix;
}

//  *** Операторы  *** //

// Сложение двух матриц
sfleta_Matrix sfleta_Matrix::operator+(const sfleta_Matrix &other) {
    sfleta_Matrix resultMatrix(*this);
    resultMatrix.sum_matrix(other);
    return resultMatrix;
}

// Вычитание одной матрицы из другой
sfleta_Matrix sfleta_Matrix::operator-(const sfleta_Matrix &other) {
    sfleta_Matrix resultMatrix(*this);
    resultMatrix.sub_matrix(other);
    return resultMatrix;
}

// Умножение матриц
sfleta_Matrix sfleta_Matrix::operator*(const sfleta_Matrix &other) {
    sfleta_Matrix resultMatrix(*this);
    resultMatrix.mul_matrix(other);
    return resultMatrix;
}

// Умножение матрицы на число
sfleta_Matrix sfleta_Matrix::operator*(const double num) {
    sfleta_Matrix resultMatrix(*this);
    resultMatrix.mul_number(num);
    return resultMatrix;
}

// Умножение матрицы на число, когда первым параметром передали число
sfleta_Matrix operator*(double num, const sfleta_Matrix &other) {
  sfleta_Matrix resultMatrix(other);
  return resultMatrix * num;
}

// Проверка на равенство матриц
bool sfleta_Matrix::operator==(const sfleta_Matrix &other) {
    return eq_matrix(other);
}

// Присвоение матрице значений другой матрицы
sfleta_Matrix& sfleta_Matrix::operator=(const sfleta_Matrix &other) {
    if (this == &other) {
        return *this;
    }

    remove_matrix();
    _rows = other._rows;
    _cols = other._cols;
    _matrix = allocateMemory(other._rows, other._cols);

    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++)  {
            _matrix[i][j] = other._matrix[i][j];
        }
    }

    return *this;
}

// Присвоение сложения (sum_matrix)
void sfleta_Matrix::operator+=(const sfleta_Matrix &other) {
    sum_matrix(other);
}

// Присвоение разности (sub_matrix)
void sfleta_Matrix::operator-=(const sfleta_Matrix &other) {
    sub_matrix(other);
}

// Присвоение умножения
void sfleta_Matrix::operator*=(const sfleta_Matrix &other) {
    mul_matrix(other);
}

// Присвоение умножения на число
void sfleta_Matrix::operator*=(const double num) {
    mul_number(num);
}

// Индексация по элементам матрицы
double sfleta_Matrix::operator()(int i, int j) {
    if (i < 0 || i >= _rows || j < 0 || j >= _cols) {
        throw out_of_range("Array index out of bound");
    }
    return _matrix[i][j];
}

// *** Дополнительные функции *** //

// Выделение памяти под двухмерный массив
double** sfleta_Matrix::allocateMemory(int rows, int cols) {
    double** buffer_p = new double*[rows];
    for (int i = 0; i < rows; i++) {
        buffer_p[i] = new double[cols];
    }
    return buffer_p;
}

// Удаление матрицы
void sfleta_Matrix::remove_matrix() {
    if (_matrix != nullptr) {
    for (int i = 0; i < _rows; i++) {
        delete[] _matrix[i];
        _matrix[i] = NULL;
    }
    delete[] _matrix;
    _matrix = NULL;
    _rows = 0;
    _cols = 0;
    }
}

// Заполнение матрицы из вектора
void sfleta_Matrix::fill_matrix_from_vector(vector<double> vect) {
    for (int i = 0, k = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++, k++) {
            _matrix[i][j] = vect[k];
        }
    }
}
