#include <iostream>
#include "Matrix.h"
#include "ComplexNumber.h"


using namespace std;


void testMatrix();
void testComplex();



int main() {
    //testComplex();
    testMatrix();

    cout << "\n";
    system("pause");
    return 0;
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

void testMatrix() {
    math::Matrix<double> m1;
    cout << "Matrix1: " << m1 << '\n';

    math::Matrix<double> m2(2, 3);
    cout << "Matrix2: " << m2 << '\n';

    math::MatrixSize size3(3, 2);
    double** arr = new double*[size3.rows()];
    for (size_t i = 0; i < size3.rows(); ++i) {
        arr[i] = new double[size3.columns()];
        for (size_t j = 0; j < size3.columns(); ++j) {
            arr[i][j] = static_cast<double>(i * j + 1 + j);
        }
    }
    math::Matrix<double> m3(arr, size3);
    cout << "Matrix3: " << m3 << '\n';

    math::Matrix<double> m4 = m3;
    cout << "Matrix4: " << m4 << '\n';

    math::Matrix<double> m5 = {
        {2, 17}, 
        {1, 0}, 
        {5, -1}
    };
    cout << "Matrix5: " << m5 << '\n';

    ++m5(0, 1);
    cout << "Matrix5: " << m5 << '\n';

    m1 = m5;
    cout << "Matrix1: " << m1 << '\n';

    m1 -= m3;
    cout << "Matrix1: " << m1 << '\n';

    m1 *= {{1}, {2}};
    cout << "Matrix1: " << m1 << '\n';

    m1 *= -1 / 6.;
    cout << "Matrix1: " << m1 << '\n';

    cout << "Matrix5 + Matrix5: " << m5 + m5 << '\n';

    cout << "Matrix2 * Matrix5: " << m2 * m5 << '\n';

    cout << "Matrix5 * 2: " << m5 * 2 << '\n';

    math::Matrix<double> m6 = {{2, 1}, {1, 3}};
    cout << "Matrix6 ^ 7: " << (m6 ^ 7) << '\n';

    math::Matrix<double> m7 = {{1, 0}, {0, 1}};
    if (m7 == (m7 ^ 70)) {
        cout << "m7 == m7 ^ 70";
    } else {
        cout << "m7 != m7 ^ 70";
    }
    cout << '\n';
    
    cout << "Matrix5.transpose: " << m5.transpose() << '\n';

    cout << "Matrix5 size: " << m5.size() << '\n';

    math::Matrix<math::ComplexNumber> m8 = {
        {{2, 1}, {-1, 4}},
        {{0, 0}, {3, -7}}
    };
    cout << "Complex matrix: " << m8 << '\n';
}
