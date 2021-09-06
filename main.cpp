#include <iostream>
#include <vector>
#include "Matrix.h"

int main() {
    /*Matrix<int> A (2, 3);
    Matrix<int> B (3, 2);

    A[1][1] = 0;
    A[1][2] = 1;
    A[1][3] = 2;
    A[2][1] = 1;
    A[2][2] = 0;
    A[2][3] = 1;

    B[1][1] = 1;
    B[1][2] = 2;
    B[2][1] = 2;
    B[2][2] = 2;
    B[3][1] = 3;
    B[3][2] = 3;

    A.GetMatrix();
    std::cout << '\n';
    B.GetMatrix();
    std::cout << '\n';

    A *= B;

    A.GetMatrix();
    std::cout << '\n';

    C[1][1] = -2;
    C[1][2] = 1;
    C[1][3] = -1;
    C[2][1] = -4;
    C[2][2] = 2;
    C[2][3] = -1;
    C[3][1] = 0;
    C[3][2] = 0;
    C[3][3] = 1;*/

    Matrix<int> C (2, 2);
    Matrix<int> D (2, 2);

    std::cin >> C >> D;
    std::cout << '\n';
    std::cout << C * D;


    //std::cout << A[1][1];

    //A += B;
    //A * B;
    /*(B * A).GetMatrix();
    //A*B;*/

    return 0;
}