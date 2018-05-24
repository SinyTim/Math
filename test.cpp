#include <iostream>
#include "Matrix.h"
#include "ComplexNumber.h"


using namespace std;


int main() {
    Math::MatrixSize size0(5, 6);
    int** arr = new int*[size0.rows()];
    for (size_t i = 0; i < size0.rows(); ++i) {
        arr[i] = new int[size0.columns()];
        for (size_t j = 0; j < size0.columns(); ++j) {
            arr[i][j] = static_cast<int>(i * j + 1 + j);
        }
    }

    Math::Matrix<int> m1 = {{1, 64}, {45, 4}, {4, 5}};
    Math::Matrix<int> m2(4, 6);
    Math::Matrix<int> m3(arr, size0.rows(), size0.columns());
    cout << "Matrix1: " << m1 << "\n";
    cout << "Matrix2: " << m2 << "\n";
    cout << "Matrix3: " << m3 << "\n";

	Math::ComplexNumber c1(2,2), c2(2,2),c3;
	c3 = c1 + c2;;
	cout << c1;
    cout << "\n";
    system("pause");
    return 0;
}
