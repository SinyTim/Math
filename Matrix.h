#pragma once

#include <iostream>
#include "MatrixSize.h"



namespace math {



template <class Type>
class Matrix;

template <class Type>
std::ostream& operator<< (std::ostream& out, const Matrix<Type>& matrix) {
    out << "[\n";
    for (size_t i = 0; i < matrix.size_.rows(); ++i) {
        out << "[ ";
        for (size_t j = 0; j < matrix.size_.columns(); ++j) {
            out << matrix.data_[i][j] << " ";
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
    Matrix(const Matrix<Type>& matrix);
    Matrix(std::initializer_list< std::initializer_list<Type> > list);
    virtual ~Matrix();
    Type& operator() (size_t row, size_t column);
    Matrix<Type>& operator= (const Matrix<Type>& matrix); // if (this != &matrix) { value = matrix.value; } return *this;
    Matrix<Type>& operator+= (const Matrix<Type>& matrix);
    Matrix<Type>& operator-= (const Matrix<Type>& matrix);
    Matrix<Type>& operator*= (const Matrix<Type>& matrix);
    Matrix<Type>& operator*= (const Type& scalar);
    Matrix<Type> operator+ (const Matrix<Type>& matrix) const;
    Matrix<Type> operator- (const Matrix<Type>& matrix) const;
    Matrix<Type> operator* (const Matrix<Type>& matrix) const; // TODO What if 4x0 and 0x3?
    Matrix<Type> operator* (const Type& scalar) const;
    Matrix<Type> operator^ (size_t degree) const;
    bool operator== (const Matrix<Type>& matrix) const;
    Matrix<Type> transpose() const;
    Matrix<Type> invertible() const;
    Type determinant() const;
    size_t rank() const;
    Type** getData() const;
    MatrixSize getSize() const;
    friend std::ostream& operator<< <Type> (std::ostream& out, const Matrix<Type>& matrix);


protected:
    const MatrixSize size_;
    Type** data_;
};



template <class Type>
Matrix<Type>::Matrix() 
    : data_(nullptr)
    , size_(0, 0) {
}

template <class Type>
Matrix<Type>::Matrix(size_t rows, size_t columns) 
    : size_(rows, columns) {
    
	data_ = new Type*[size_.rows()];
	for (size_t i = 0; i < size_.rows(); ++i) {
		data_[i] = new Type[size_.columns()];
	}

	for (size_t i = 0; i < size_.rows(); ++i) {
		for (size_t j = 0; j < size_.columns(); ++j) {
			data_[i][j] = Type();
		}
	}
}

template <class Type>
Matrix<Type>::Matrix(Type** arr, size_t rows, size_t columns)
    : size_(rows, columns) {

    data_ = new Type*[size_.rows()];
    for (size_t i = 0; i < size_.rows(); ++i) {
        data_[i] = new Type[size_.columns()];
    }

    for (size_t i = 0; i < size_.rows(); ++i) {
        for (size_t j = 0; j < size_.columns(); ++j) {
            data_[i][j] = arr[i][j];
        }
    }
}

template<class Type>
Matrix<Type>::Matrix(const Matrix<Type>& obj)
    : size_(obj.size_) {

    data_ = new Type*[size_.rows()];
    for (size_t i = 0; i < size_.rows(); ++i) {
        data_[i] = new Type[size_.columns()];
    }

    for (size_t i = 0; i < size_.rows(); ++i) {
        for (size_t j = 0; j < size_.columns(); ++j) {
            data_[i][j] = obj.data_[i][j];
        }
    }
}

template<class Type>
Matrix<Type>::Matrix(std::initializer_list< std::initializer_list<Type> > list) 
    : size_(list.size(), list.begin()->size()) {

    data_ = new Type*[size_.rows()];
    for (size_t i = 0; i < size_.rows(); ++i) {
        data_[i] = new Type[size_.columns()];
    }
    
    size_t i = 0;
    size_t j = 0;
    for (const auto& row : list) {
        if (row.size() != size_.columns()) {
            std::cerr << "Error in class Matrix: invalid initializer list.";
            throw;
        }
        j = 0;
        for (const auto& element : row) {
            data_[i][j] = element;
            ++j;
        }
        ++i;
    }
}

template <class Type>
Matrix<Type>::~Matrix() {
    for (size_t i = 0; i < size_.rows(); ++i) {
        delete[] data_[i];
    }
    delete[] data_;
}



}
