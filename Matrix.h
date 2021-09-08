#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include "Row.h"
#include <iostream>

//#define IDENTITY_MATRIX 1

template<class T>
class Matrix {
private:
    Row<T>* table;
    long long rows;
    long long cols;

    void dMatrix();

public:
    Matrix();

    Matrix(long long rows, long long cols);

    Matrix(const Matrix& other);

    Matrix(Matrix&& other) noexcept;

    ~Matrix();

    void GetMatrix();

    Matrix<T> Pow(int p);

    Row<T>& operator[](long long index) const;

    Matrix<T>& operator=(const Matrix& other);

    //Matrix<T>&& operator=(Matrix&& other) noexcept;

    bool operator==(const Matrix& other);

    Matrix<T> operator+(const Matrix& other) const;

    Matrix<T> operator-(const Matrix& other) const;

    Matrix<T> operator+=(const Matrix& other);

    Matrix<T> operator-=(const Matrix& other);

    Matrix<T> operator*(const Matrix<T>& other) const;

    Matrix<T> operator*(int a) const;

    Matrix<T>& operator*=(int a);

    Matrix<T>& operator*=(const Matrix<T>& other);

    Matrix<T> Trans();

    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
        for(int i = 1; i <= matrix.rows; ++i) {
            for(int j = 1; j <= matrix.cols; ++j) {
                os << matrix[i][j] << '\t';
            }
            os << '\n';
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Matrix& matrix) {
        long long nr, nc;
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
            for(int j = 1; j <= matrix.cols; ++j) {
                is >> matrix[i][j];
            }
        }
        return is;
    }
};

// --------------------------------------------------------------------------------------------------------------------

template<class T>
Matrix<T>::Matrix() : rows(0), cols(0), table(nullptr) {}

template<class T>
Matrix<T>::Matrix(long long int rows, long long int cols) : cols(cols), rows(rows) {
    table = new Row<T>[rows];
    for(int i = 0; i < rows; ++i) {
        table[i] = Row<T>(cols);
    }
}

template<class T>
Matrix<T>::Matrix(const Matrix& other) : cols(other.cols), rows(other.rows) {
    table = new Row<T>[rows];
    for(int i = 0; i < rows; ++i) {
        table[i] = Row<T>(cols);
    }
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
Row<T>& Matrix<T>::operator[](long long index) const {
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
    for(int i = 1; i <= rows; ++i) {
        for(int j = 1; j <= cols; ++j) {
            m[i][j] += other[i][j];
        }
    }
    return m;
}

template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix& other) const {
    Matrix m(*this);
    for(int i = 1; i <= rows; ++i) {
        for(int j = 1; j <= cols; ++j) {
            m[i][j] -= other[i][j];
        }
    }
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
    long long k = this->cols;
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
            table = new Row<T>[rows];
            for(int i = 0; i < rows; ++i) {
                table[i] = Row<T>(cols);
            }
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
    Matrix<T> m = new Matrix<T>(this->cols, this->rows);
    for(int i = 1; i <= m.rows; i++) {
        for(int j = 1; j <= m.cols; j++) {
            m[i][j] = this[j][i];
        }
    }
    return m;
}

/*template<class T>
Matrix<T>&& Matrix<T>::operator=(Matrix&& other) noexcept {
    if(this->table != other.table) { // self-assignment
        if(this->rows != other.rows || this->cols != other.cols) { // dif size
            this->rows = other.rows;
            this->cols = other.cols;
        }
        this->table = other.table;
        other.table = nullptr;
    }
    return std::move(*this);
}*/

#endif //MATRIX_MATRIX_H