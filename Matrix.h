#pragma once

#include <iostream>



namespace Math {

    

template <class Type>
class Matrix {

public:
    Matrix(); 
    Matrix(size_t rows, size_t columns);
    Matrix(Type** arr, size_t rows, size_t columns);
    explicit Matrix(const Matrix<Type>& obj);
    virtual ~Matrix();
    Type& operator() (size_t row, size_t column);
    Matrix<Type>& operator= (const Matrix<Type>& matrix);
    Matrix<Type>& operator+= (const Matrix<Type>& matrix);
    Matrix<Type>& operator-= (const Matrix<Type>& matrix);
    Matrix<Type>& operator*= (const Type& scalar);
    Matrix<Type>& operator*= (const Matrix<Type>& matrix);
    Matrix<Type> operator+ (const Matrix<Type>& matrix) const;
    Matrix<Type> operator- (const Matrix<Type>& matrix) const;
    Matrix<Type> operator* (const Type& scalar) const;
    Matrix<Type> operator* (const Matrix<Type>& matrix) const;
    Matrix<Type> operator^ (size_t degree) const;
    bool operator== (const Matrix<Type>& obj) const;
    Type det() const;
    int rank() const;
    Matrix<Type> T() const;
    Matrix<Type> invert() const;
    friend std::ostream& operator<< (std::ostream& os, const Matrix<Type>& matrix);


protected:
    const size_t rows;
    const size_t columns;
    Type** data;
};



template <class Type>
Matrix<Type>::Matrix() 
    : data(nullptr)
    , rows(0)
    , columns(0) {
}

template <class Type>
Matrix<Type>::Matrix(size_t rows, size_t columns) 
    : rows(rows)
    , columns(columns) {

	data = new Type*[rows];
	for (size_t i = 0; i < rows; ++i) {
		data[i] = new Type[columns];
	}

	for (size_t i = 0; i < rows; ++i) {
		for (size_t j = 0; j < columns; ++j) {
			data[i][j] = Type();
		}
	}
}

template <class Type>
Matrix<Type>::Matrix(Type** arr, size_t rows, size_t columns)
    : rows(rows)
    , columns(columns) {

    data = new Type*[rows];
    for (size_t i = 0; i < rows; ++i) {
        data[i] = new Type[columns];
    }

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            data[i][j] = arr[i][j];
        }
    }
}

template<class Type>
Matrix<Type>::Matrix(const Matrix<Type>& obj) 
    : rows(obj.rows)
    , columns(obj.columns) {
    
    data = new Type*[rows];
    for (size_t i = 0; i < rows; ++i) {
        data[i] = new Type[columns];
    }

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            data[i][j] = obj.data[i][j];
        }
    }
}

template <class Type>
Matrix<Type>::~Matrix() {
    for (size_t i = 0; i < rows; ++i) {
        delete[] data[i];
    }
    delete[] data;
}



}
