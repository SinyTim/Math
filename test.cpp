#include <iostream>
#include "Matrix.h"


using namespace std;


int main() {
    Math::Matrix<int> m1 = {{1, 64}, {2, 4}, {4, 5}}, m2(4, 5);
    cout << m1 << "\n" << m2;

    cout << "\n";
    system("pause");
    return 0;
}
