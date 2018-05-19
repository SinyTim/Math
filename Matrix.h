#pragma once

#include <iostream>



namespace Math {

    

template <class Type>
class Matrix {

public:
    Matrix(); 
    Matrix(int rows, int columns);
    Matrix(Type** arr, int rows, int columns);
    Matrix(const Matrix<Type>& obj);
    virtual ~Matrix();
    Type& operator() (int row, int column);
    Matrix<Type>& operator= (const Matrix<Type>& matrix);
    Matrix<Type>& operator+= (const Matrix<Type>& matrix);
    Matrix<Type>& operator-= (const Matrix<Type>& matrix);
    Matrix<Type>& operator*= (const Type& scalar);
    Matrix<Type>& operator*= (const Matrix<Type>& matrix);
    Matrix<Type> operator+ (const Matrix<Type>& matrix) const;
    Matrix<Type> operator- (const Matrix<Type>& matrix) const;
    Matrix<Type> operator* (const Type& scalar) const;
    Matrix<Type> operator* (const Matrix<Type>& matrix) const;
    Matrix<Type> operator^ (unsigned int degree) const;
    bool operator== (const Matrix<Type>& obj) const;
    Type det() const;
    int rank() const;
    Matrix<Type> T() const;
    Matrix<Type> invert() const;
    friend std::ostream& operator<< (std::ostream& os, const Matrix<Type>& matrix);


protected:
    const int rows;
    const int columns;
    Type** data;
};



template <class Type>
Matrix<Type>::Matrix() 
    : data(nullptr)
    , rows(0)
    , columns(0) {
}

template <class Type>
Matrix<Type>::Matrix(int rows, int columns) {
	data = new Type*[rows];
	for (size_t i = 0; i < rows; ++i) {
		data[i] = new Type[columns];
	}

	for (size_t i = 0; i < rows; ++i) {
		for (size_t j = 0; j < columns; ++j) {
			data[i][j] = Type();
		}
	}

	this->rows = rows;
	this->columns = columns;
}

template <class Type>
Matrix<Type>::Matrix(Type** arr, int rows, int columns) {
    data = new Type*[rows];
    for (size_t i = 0; i < rows; ++i) {
        data[i] = new Type[columns];
    }

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            data[i][j] = arr[i][j];
        }
    }

    this->rows = rows;
    this->columns = columns;
}

template <class Type>
Matrix<Type>::~Matrix() {
    for (size_t i = 0; i < rows; ++i) {
        delete[] data[i];
    }
    delete[] data;
}



}
