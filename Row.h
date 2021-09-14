#ifndef MATRIX_ROW_H
#define MATRIX_ROW_H

#include <iostream>

template<class T>
class Row {
private:
    T* arr;
    size_t size;
public:
    Row();

    explicit Row(size_t size);

    //Row(const Row & other);

    //~Row();

    void dCol();

    T& operator[](long long index);

    friend std::ostream& operator<< (std::ostream& os, Row<T> r) {
        for(int j = 1; j <= r.size; ++j) {
            os << r[j] << '\t';
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Row<T> r) {
        for(int j = 1; j <= r.size; ++j) {
            is >> r[j];
        }
        return is;
    }
};

// --------------------------------------------------------------------------------------------------------------------

template<class T>
Row<T>::Row() : arr(nullptr) {}

template<class T>
Row<T>::Row(size_t size) : size(size) {
    arr = new T[size];
}

template<class T>
T& Row<T>::operator[](long long int index) {
    return arr[index - 1];
}

template<class T>
void Row<T>::dCol() {
    delete[] arr;
}

/*template<class T>
Row<T>::~Row() {
    delete[] arr;
}*/

#endif //MATRIX_ROW_H