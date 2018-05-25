#include <iostream>
#include "Matrix.h"
#include "ComplexNumber.h"


using namespace std;


int main() {
    math::MatrixSize size0(5, 6);
    int** arr = new int*[size0.rows()];
    for (size_t i = 0; i < size0.rows(); ++i) {
        arr[i] = new int[size0.columns()];
        for (size_t j = 0; j < size0.columns(); ++j) {
            arr[i][j] = static_cast<int>(i * j + 1 + j);
        }
    }

    math::Matrix<int> m1 = {{1, 64}, {45, 4}, {4, 5}};
    math::Matrix<int> m2(4, 6);
    math::Matrix<int> m3(arr, size0.rows(), size0.columns());
    cout << "Matrix1: " << m1 << "\n";
    cout << "Matrix2: " << m2 << "\n";
    cout << "Matrix3: " << m3 << "\n";

    math::ComplexNumber c1(2, -2), c2(2, -2);

    if(c1==c2)
        cout << "Ok\n";

    math::ComplexNumber c3(5, 10), c4(3, 4);
    cout << c3 * c4 << endl;
    cout << c3 / c4 << endl;

    c4 = c4.conjugate();
    cout << c4.modulus() << endl;

    math::Matrix<math::ComplexNumber> mc = {
        {{2, 1}, {-1, 4}}, 
        {{0, 0}, c1}
    };
    cout << "Complex matrix: " << mc;

    cout << "\n";
    return 0;
}
