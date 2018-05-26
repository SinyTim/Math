#include <iostream>
#include "Matrix.h"
#include "ComplexNumber.h"


using namespace std;


void testMatrix();
void testComplex();



int main() {
    testMatrix();
    testComplex();

    cout << "\n";
    return 0;
}



void testMatrix() {
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

    math::Matrix<math::ComplexNumber> mc = {
        {{2, 1}, {-1, 4}},
        {{0, 0}, {3, -7}}
    };
    cout << "Complex matrix: " << mc;

    math::Matrix<int> m4 = { { 1, 64 },{ 45, 4 },{ 4, 5 } };
    math::Matrix<int> m5 = { { 2, 6 },{ 452, 7 },{ 0, 5 } };
    m4 += m5;
    cout << "Matrix4: " << m4 << "\n";

    m4 *= 5;
    cout << "Matrix4: " << m4 << "\n";

    math::Matrix<int> m6 = { { 3, 3, 3 },{ 3, 3, 3 } };
    math::Matrix<int> m7 = { { 1 },{ 1 },{ 1 } };
    m4 = m6;
    m4 *= m7;
    cout << "Matrix4: " << m4 << "\n";
    math::Matrix<int> m8(4, 0);
    math::Matrix<int> m9(0, 3);
    cout << m8 * m9 << endl;

    math::Matrix<int> m10 = { { 2, 6, 5 },{ 452, 7, 10 },{ 15, 8, 42 } };
    cout << "Matrix10: " << m10 << "\n";
    cout << "Transposed m10: " << m10.transpose() << endl;
    cout << "m10 in 3 degree" << (m10 ^ 3) << endl;
    m9 = m10;
    if(m9==m10){
        cout << "m9 == m10";
    } else {
        cout << "m9 != m10";
    }
    cout << '\n';
}

void testComplex() {
    math::ComplexNumber c1(2, -2), c2(2, -2);
    c2 *= 1.0000000001;

    if (c1 == c2) {
        cout << c1 << " == " << c2;
    } else {
        cout << c1 << " != " << c2;
    }
    cout << '\n';

    math::ComplexNumber c3(5, 10), c4(3, 4);
    cout << c3 * c4 << endl;
    cout << c3 / c4 << endl;

    cout << c4.conjugate() << endl;
    cout << c4.modulus() << endl;
}
