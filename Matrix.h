#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include "Row.h"
#include <iostream>

//bool DEBUG = true;

enum class MatrixTypes {
    IdentityMatrix,
    ZeroMatrix
};

template<class T>
class Matrix {
private:
    Row<T>* table;
    size_t rows;
    size_t cols;

    void dMatrix();

    void initTable();

public:
    Matrix();

    Matrix(size_t rows, size_t cols);

    Matrix(const Matrix& other);

    Matrix(Matrix&& other) noexcept;

    ~Matrix();

    void GetMatrix();

    Matrix<T> Pow(int p);

    Matrix<T> rSwap(size_t i0, size_t j0);

    Matrix<T> cSwap(size_t i0, size_t j0);

    Matrix<T> rAdd(size_t i0, size_t j0, int a);

    Matrix<T> cAdd(size_t i0, size_t j0, int a);

    Matrix<T> rMult(size_t i0, int a);

    Matrix<T> cMult(size_t i0, int a);

    Row<T>& operator[](size_t index) const;

    Matrix<T>& operator=(const Matrix& other);

    Matrix<T>& operator=(Matrix&& other) noexcept;

    bool operator==(const Matrix& other);

    bool operator!=(const Matrix& other);

    Matrix<T> operator+(const Matrix& other) const;

    Matrix<T> operator-(const Matrix& other) const;

    Matrix<T> operator+=(const Matrix& other);

    Matrix<T> operator-=(const Matrix& other);

    Matrix<T> operator*(const Matrix<T>& other) const;

    Matrix<T> operator*(int a) const;

    Matrix<T>& operator*=(int a);

    Matrix<T>& operator*=(const Matrix<T>& other);

    Matrix<T> Trans();

    Matrix<T> Minor(int i0, int j0);

    double* Gauss();

    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
        for(int i = 1; i <= matrix.rows; ++i) {
            os << matrix[i] << '\n';
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Matrix& matrix) {
        size_t nr, nc;
        is >> nr >> nc;
        if(matrix.rows != nr || matrix.cols != nc) { // dif size
            matrix.dMatrix();
            matrix.rows = nr;
            matrix.cols = nc;
            matrix.table = new Row<T>[matrix.rows];
            for(int i = 0; i < matrix.rows; ++i) {
                matrix.table[i] = Row<T>(matrix.cols);
            }
        }
        for(int i = 1; i <= matrix.rows; ++i) { // copy this <- other
            is >> matrix[i];
        }
        return is;
    }
};

// --------------------------------------------------------------------------------------------------------------------

template<class T>
Matrix<T>::Matrix() : rows(0), cols(0), table(nullptr) {}

template<class T>
Matrix<T>::Matrix(size_t rows, size_t cols) : cols(cols), rows(rows) {
    initTable();
}

template<class T>
Matrix<T>::Matrix(const Matrix& other) : cols(other.cols), rows(other.rows) {
    initTable();
    for(int i = 1; i <= rows; ++i) {
        for(int j = 1; j <= cols; ++j) {
            (*this)[i][j] = other[i][j];
        }
    }
}

template<class T>
Matrix<T>::Matrix(Matrix&& other) noexcept : cols(other.cols), rows(other.rows) {
    other.rows = other.cols = 0;
    this->table = other.table;
    other.table = nullptr;
}

template<class T>
Row<T>& Matrix<T>::operator[](size_t index) const {
    return table[index - 1];
}

template<class T>
Matrix<T>::~Matrix() {
    /*for(int i = 0; i < rows; ++i) {
        table[i].dCol();
    }
    delete[] table;*/
    dMatrix();
}

template<class T>
void Matrix<T>::GetMatrix() {
    //std::cout << "here";
    for(int i = 1; i <= rows; ++i) {
        for(int j = 1; j <= cols; ++j) {
            std::cout << (*this)[i][j] << '\t';
        }
        std::cout << '\n';
    }
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) const {
    Matrix m(*this);
    m += other;
    return m;
}

template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix& other) const {
    Matrix m(*this);
    m -= other;
    return m;
}

template<class T>
Matrix<T> Matrix<T>::operator+=(const Matrix& other) {
    for(int i = 1; i <= rows; ++i) {
        for(int j = 1; j <= cols; ++j) {
            (*this)[i][j] += other[i][j + 1];
        }
    }
    return *this;
}

template<class T>
Matrix<T> Matrix<T>::operator-=(const Matrix& other) {
    for(int i = 1; i <= rows; ++i) {
        for(int j = 1; j <= cols; ++j) {
            (*this)[i][j] -= other[i][j];
        }
    }
    return *this;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
    size_t k = this->cols;
    //throw std::runtime_error("sdf");
    Matrix<T> m(this->rows, other.cols);
    for(int i = 1; i <= m.rows; ++i) {
        for(int j = 1; j <= m.cols; ++j) {
            m[i][j] = 0;
            std::cout << "c" << i << ';' << j << " =";
            for(int l = 1; l <= k; ++l) {
                std::cout << (l == 1 ? " " : "+ ") << (*this)[i][l] << " * " << other[l][j] << ' ';
                m[i][j] += ((*this)[i][l]) * (other[l][j]);
            }
            std::cout << "= " << m[i][j] << '\n';
        }
    }
    return m;
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other) {
    if(this->table != other.table) { // self-assignment
        if(this->rows != other.rows || this->cols != other.cols) { // dif size
            dMatrix();
            this->rows = other.rows;
            this->cols = other.cols;
            initTable();
        }
        for(int i = 1; i <= rows; ++i) { // copy this <- other
            for(int j = 1; j <= cols; ++j) {
                (*this)[i][j] = other[i][j];
            }
        }
    }
    return *this;
}

template<class T>
void Matrix<T>::dMatrix() {
    if(table != nullptr) {
        for(int i = 0; i < rows; ++i) {
            table[i].dCol();
        }
        delete[] table;
    }
    rows = cols = 0;
}

template<class T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& other) {
    (*this) = ((*this) * other);
    return *this;
}

template<class T>
bool Matrix<T>::operator==(const Matrix& other) {
    if(this->rows == other.rows && this->cols == other.cols) { // checking size
        for(int i = 1; i <= rows; ++i) { // comparing this[i][j] with other[i][j]
            for(int j = 1; j <= cols; ++j) {
                if((*this)[i][j] != other[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

template<class T>
Matrix<T> Matrix<T>::Pow(int p) {
    Matrix<T> m(*this);
    for(int i = 0; i < p - 1; ++i) {
        m *= (*this);
    }
    return m;
}

template<class T>
Matrix<T> Matrix<T>::operator*(int a) const {
    Matrix<T> m(*this);
    for(int i = 1; i <= rows; ++i) {
        for(int j = 1; j <= cols; ++j) {
            m[i][j] *= a;
        }
    }
    return m;
}

template<class T>
Matrix<T>& Matrix<T>::operator*=(int a) {
    for(int i = 1; i <= rows; ++i) {
        for(int j = 1; j <= cols; ++j) {
            (*this)[i][j] *= a;
        }
    }
    return *this;
}

template<class T>
Matrix<T> Matrix<T>::Trans() {
    Matrix<T> m = Matrix<T>(this->cols, this->rows);
    for(int i = 1; i <= m.rows; i++) {
        for(int j = 1; j <= m.cols; j++) {
            m[i][j] = (*this)[j][i];
        }
    }
    return m;
}


template<class T>
Matrix<T> Matrix<T>::Minor(int i0, int j0) {
    int p = 0, q = 0;
    Matrix<T> m(this->rows - 1, this->cols - 1);
    for(int i = 1; i <= m.rows; ++i) {
        if(i == i0) {
            p = 1;
        }
        q = 0;
        for(int j = 1; j <= m.cols; ++j) {
            if(j == j0) {
                q = 1;
            }
            m[i][j] = (*this)[i + p][j + q];
        }
    }
    return m;
}

template<class T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept {
    if(this->table != other.table) { // self-assignment
        if(this->rows != other.rows || this->cols != other.cols) { // dif size
            this->rows = other.rows;
            this->cols = other.cols;
        }
        this->table = other.table;
        other.table = nullptr;
        other.rows = 0;
        other.cols = 0;
    }
    return *this;
}

template<class T>
void Matrix<T>::initTable() {
    table = new Row<T>[rows];
    for(int i = 0; i < rows; ++i) {
        table[i] = Row<T>(cols);
    }
}

template<class T>
bool Matrix<T>::operator!=(const Matrix& other) {
    return !(*this == other);
}

template<class T>
double* Matrix<T>::Gauss() {
    double* ans = new double[rows];
    Matrix<T> m1(*this);
    std::cout << m1;
    for(int k = 1; k <= rows; ++k) {
        for(int j = k; j <= rows; ++j) {
            double m = (double) m1[j][k] / m1[k][k];
            for(int i = 1; i <= rows; ++i) {
                m1[i][j] = m1[j][i] - m * m1[k][i];
            }
        }
    }

    for(int i = rows; i >= 1; --i) {
        ans[i - 1] = (double) m1[i][rows] / m1[i][i];
        for(int c = rows; c >= i; --c) {
            ans[i - 1] -= double(m1[i][c] * ans[c - 1]) / m1[i][i];
        }
    }
    std::cout << m1;
    return ans;
}

template<class T>
Matrix<T> Matrix<T>::rSwap(size_t i0, size_t j0) {
    Matrix<T> m(*this);
    for(int i = 1; i <= cols; ++i) {
        m[i0][i] = (*this)[j0][i];
        m[j0][i] = (*this)[i0][i];
    }
    return m;
}

template<class T>
Matrix<T> Matrix<T>::cSwap(size_t i0, size_t j0) {
    Matrix<T> m(*this);
    for(int i = 1; i <= rows; ++i) {
        m[i][i0] = (*this)[i][j0];
        m[i][j0] = (*this)[i][i0];
    }
    return m;
}

template<class T>
Matrix<T> Matrix<T>::rAdd(size_t i0, size_t j0, int a) {
    Matrix<T> m(*this);
    for(int i = 1; i <= cols; ++i) {
        m[i0][i] += (*this)[j0][i] * a;
    }
    return m;
}

template<class T>
Matrix<T> Matrix<T>::cAdd(size_t i0, size_t j0, int a) {
    Matrix<T> m(*this);
    for(int i = 1; i <= rows; ++i) {
        m[i][i0] += (*this)[i][j0] * a;
    }
    return m;
}

template<class T>
Matrix<T> Matrix<T>::rMult(size_t i0, int a) {
    Matrix<T> m(*this);
    for(int i = 1; i <= cols; ++i) {
        m[i0][i] *= a;
    }
    return m;
}

template<class T>
Matrix<T> Matrix<T>::cMult(size_t i0, int a) {
    Matrix<T> m(*this);
    for(int i = 1; i <= rows; ++i) {
        m[i][i0] *= a;
    }
    return m;
}

#endif //MATRIX_MATRIX_H