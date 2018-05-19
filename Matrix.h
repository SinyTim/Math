#pragma once

#include <iostream>



namespace Math {



template <class Type>
class Matrix;

template <class Type>
std::ostream& operator<< (std::ostream& out, const Matrix<Type>& matrix) {
    out << "[\n";
    for (size_t i = 0; i < matrix.rows; ++i) {
        out << "[ ";
        for (size_t j = 0; j < matrix.columns; ++j) {
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
    Matrix(size_t rows, size_t columns);
    Matrix(Type** arr, size_t rows, size_t columns);
    Matrix(std::initializer_list< std::initializer_list<Type> > list); // TODO надо обработать throw.
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
    friend std::ostream& operator<< <Type> (std::ostream& out, const Matrix<Type>& matrix);


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
Matrix<Type>::Matrix(std::initializer_list< std::initializer_list<Type> > list) 
    : rows(list.size())
    , columns(list.begin()->size()) {

    data = new Type*[rows];
    for (size_t i = 0; i < rows; ++i) {
        data[i] = new Type[columns];
    }
    
    size_t i = 0;
    size_t j = 0;
    for (const auto& row : list) {
        if (row.size() != columns) {
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
