#pragma once



namespace Math {


template <class Type>
class Matrix {

public:
    Matrix(); 
    Matrix(int rows, int columns);
    Matrix(const Matrix& obj);
    ~Matrix();
    Type& operator() (int row, int column);
    Matrix<Type>& operator= (const Matrix& matrix);
    Matrix<Type>& operator+= (const Matrix& matrix);
    Matrix<Type>& operator-= (const Matrix& matrix);
    Matrix<Type>& operator*= (const Type& scalar);
    Matrix<Type>& operator*= (const Matrix& matrix);
    Matrix<Type> operator+ (const Matrix& matrix) const;
    Matrix<Type> operator- (const Matrix& matrix) const;
    Matrix<Type> operator* (const Type& scalar) const;
    Matrix<Type> operator* (const Matrix& matrix) const;
    Matrix<Type> operator^ (unsigned int degree) const;
    bool operator== (const Matrix& obj) const;
    Type det() const;
    int rank() const;
    Matrix<Type> T() const;
    Matrix<Type> invert() const;
    friend ostream& operator<< (ostream& os, const Matrix<Type>& matrix);


private:
    const int rows;
    const int columns;
    Type** data;
};


}
