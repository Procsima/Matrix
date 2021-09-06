#ifndef MATRIX_ROW_H
#define MATRIX_ROW_H

#include <iostream>

template<class T>
class Row {
private:
    T* arr;
public:
    Row();

    explicit Row(long long size);

    //Row(const Row & other);

    //~Row();

    void dCol();

    T& operator[](long long index);
};

// --------------------------------------------------------------------------------------------------------------------

template<class T>
Row<T>::Row() : arr(nullptr) {}

template<class T>
Row<T>::Row(long long int size) {
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