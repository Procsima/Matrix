#include <iostream>
#include "Matrix.h"

int main() {
    Matrix<int> m;
    std::cin>>m;
    std::cout<<m.Adj();
    return 0;
}
