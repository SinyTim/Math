#include <iostream>
#include <vector>
#include "Math.h"


using namespace std;


void testMatrix();
void testComplex();
void testPolynom();



int main() {

    //testComplex();
    //testMatrix();
    //testPolynom();

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

    cout << "m5.withoutRow(1): " << m5.withoutRow(1) << '\n';

    cout << "m5.withoutColumn(0): " << m5.withoutColumn(0) << '\n';
    
    cout << "Matrix5.transpose: " << m5.transpose() << '\n';

    cout << "Determinant: " << math::Matrix<int>({
        {7, 1, 1, 14}, 
        {3, 2, 2, 12}, 
        {2, 1, 3, 7}, 
        {1, 0, 0, 0}
    }).determinant() << '\n';

    cout << "Determinant: " << math::Matrix< math::Polynomial<int> >({
        {math::Polynomial<int>({1, 0, 1}), math::Polynomial<int>({1, 2})},
        {math::Polynomial<int>({-1}), math::Polynomial<int>({1, 1})},
    }).determinant() << '\n';

    cout << "Matrix5 size: " << m5.size() << '\n';

    math::Matrix<math::ComplexNumber> m8 = {
        {{2, 1}, {-1, 4}},
        {{0, 0}, {3, -7}}
    };
    cout << "Complex matrix: " << m8 << '\n';
}

void testPolynom() {
    math::Polynomial<double> p1;
    cout << "Polynom1: " << p1 << '\n';

    vector<double> coef2 = {-15, 6, -2, 0, 3, 0};
    math::Polynomial<double> p2(coef2);
    cout << "Polynom2: " << p2 << '\n';

    math::Polynomial<double> p3 = p2;
    cout << "Polynom3: " << p3 << '\n';

    ++p3[3];
    cout << "Polynom3: " << p3 << '\n';

    p2 -= p3;
    cout << "Polynom2: " << p2 << '\n';

    math::Polynomial<double> p4({1, 1});
    p4 *= math::Polynomial<double>({1, 1});
    cout << "Polynom4: " << p4 << '\n';

    math::Polynomial<double> p5({1, 1, 0, 1});
    math::Polynomial<double> p6({1, 1, 1});
    cout << "p5 / p6: " << p5 / p6 << '\n';
    cout << "p5 % p6: " << p5 % p6 << '\n';

    math::Polynomial<double> p7({6, -7, 0, 1});
    math::Polynomial<double> p8({8, -10, 1, 1});
    cout << "p7.gcd(p8): " << p7.gcd(p8) << '\n';

    cout << "p8.derivative(): " << p8.derivative() << '\n';

    cout << "p6.value(2): " << p6.value(2) << '\n';
}
