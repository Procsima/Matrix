#include <iostream>
#include "Matrix.h"

int main() {
    Matrix<int> a(3, 3);
    std::cin >> a;
    std::cout << a.Minor(3, 1);
    return 0;
}