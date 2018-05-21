#pragma once

#include <iostream>
#include "MatrixSize.h"



namespace Math {



template <class Type>
class Matrix;

template <class Type>
std::ostream& operator<< (std::ostream& out, const Matrix<Type>& matrix) {
    out << "[\n";
    for (size_t i = 0; i < matrix.size.rows(); ++i) {
        out << "[ ";
        for (size_t j = 0; j < matrix.size.columns(); ++j) {
            out << matrix.data[i][j] << " ";
        }
        out << "]\n";
    }
    out << "]";
    return out;
}

    

template <class Type>
class Matrix {

public:
    Matrix(); 
    explicit Matrix(size_t rows, size_t columns);
    explicit Matrix(Type** arr, size_t rows, size_t columns);
    explicit Matrix(const Matrix<Type>& obj);
    Matrix(std::initializer_list< std::initializer_list<Type> > list);
    virtual ~Matrix();
    Type& operator() (size_t row, size_t column);
    Matrix<Type>& operator= (const Matrix<Type>& matrix); // if (this != &matrix) { value = matrix.value; } return *this;
    Matrix<Type>& operator+= (const Matrix<Type>& matrix);
    Matrix<Type>& operator-= (const Matrix<Type>& matrix);
    Matrix<Type>& operator*= (const Type& scalar);
    Matrix<Type>& operator*= (const Matrix<Type>& matrix);
    Matrix<Type> operator+ (const Matrix<Type>& matrix) const;
    Matrix<Type> operator- (const Matrix<Type>& matrix) const;
    Matrix<Type> operator* (const Type& scalar) const; // TODO What if 4x0 and 0x3?
    Matrix<Type> operator* (const Matrix<Type>& matrix) const;
    Matrix<Type> operator^ (size_t degree) const;
    bool operator== (const Matrix<Type>& obj) const;
    Type det() const;
    int rank() const;
    Matrix<Type> T() const;
    Matrix<Type> invert() const;
    Type** getData() const;
    MatrixSize getSize() const;
    friend std::ostream& operator<< <Type> (std::ostream& out, const Matrix<Type>& matrix);


protected:
    const MatrixSize size;
    Type** data;
};



template <class Type>
Matrix<Type>::Matrix() 
    : data(nullptr)
    , size(0, 0) {
}

template <class Type>
Matrix<Type>::Matrix(size_t rows, size_t columns) 
    : size(rows, columns) {
    
	data = new Type*[size.rows()];
	for (size_t i = 0; i < size.rows(); ++i) {
		data[i] = new Type[size.columns()];
	}

	for (size_t i = 0; i < size.rows(); ++i) {
		for (size_t j = 0; j < size.columns(); ++j) {
			data[i][j] = Type();
		}
	}
}

template <class Type>
Matrix<Type>::Matrix(Type** arr, size_t rows, size_t columns)
    : size(rows, columns) {

    data = new Type*[size.rows()];
    for (size_t i = 0; i < size.rows(); ++i) {
        data[i] = new Type[size.columns()];
    }

    for (size_t i = 0; i < size.rows(); ++i) {
        for (size_t j = 0; j < size.columns(); ++j) {
            data[i][j] = arr[i][j];
        }
    }
}

template<class Type>
Matrix<Type>::Matrix(const Matrix<Type>& obj)
    : size(obj.size) {

    data = new Type*[size.rows()];
    for (size_t i = 0; i < size.rows(); ++i) {
        data[i] = new Type[size.columns()];
    }

    for (size_t i = 0; i < size.rows(); ++i) {
        for (size_t j = 0; j < size.columns(); ++j) {
            data[i][j] = obj.data[i][j];
        }
    }
}

template<class Type>
Matrix<Type>::Matrix(std::initializer_list< std::initializer_list<Type> > list) 
    : size(list.size(), list.begin()->size()) {

    data = new Type*[size.rows()];
    for (size_t i = 0; i < size.rows(); ++i) {
        data[i] = new Type[size.columns()];
    }
    
    size_t i = 0;
    size_t j = 0;
    for (const auto& row : list) {
        if (row.size() != size.columns()) {
            std::cerr << "Error in class Matrix: invalid initializer list.";
            throw;
        }
        j = 0;
        for (const auto& element : row) {
            data[i][j] = element;
            ++j;
        }
        ++i;
    }
}

template <class Type>
Matrix<Type>::~Matrix() {
    for (size_t i = 0; i < size.rows(); ++i) {
        delete[] data[i];
    }
    delete[] data;
}



}
