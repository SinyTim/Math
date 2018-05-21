#include <iostream>
#include "Matrix.h"


using namespace std;


int main() {
    int** arr = new int*[3];
    for (size_t i = 0; i < 3; ++i) {
        arr[i] = new int[3] {static_cast<int>(i + 1), 
                             static_cast<int>(i + 2), 
                             static_cast<int>(i + 3)};
    }

    Math::Matrix<int> m1 = {{1, 64}, {45, 4}, {4, 5}};
    Math::Matrix<int> m2(4, 5);
    Math::Matrix<int> m3(arr, 3, 3);
    cout << "Matrix1: " << m1 << "\n";
    cout << "Matrix2: " << m2 << "\n";
    cout << "Matrix3: " << m3 << "\n";

    cout << "\n";
    system("pause");
    return 0;
}
