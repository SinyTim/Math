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
    Matrix<Type> operator^ (size_t degree) const; // TODO degree == 0?
    bool operator== (const Matrix<Type>& matrix) const;
    Matrix<Type> transpose() const;
    Matrix<Type> invertible() const;
    Type determinant() const;
    size_t rank() const;
    Type** getData() const;
    MatrixSize getSize() const;
    friend std::ostream& operator<< <Type> (std::ostream& out, const Matrix<Type>& matrix);


protected:
    MatrixSize size_;
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

template<class Type>
inline Type & Matrix<Type>::operator()(size_t row, size_t column) {
    return data_[row][column];
}

template<class Type>
Matrix<Type>& Matrix<Type>::operator=(const Matrix<Type>& matrix) {
    if (this == &matrix) {
        return *this;
    }

    for (size_t i = 0; i < size_.rows(); i++) {
        delete [] data_[i];
    }
    delete [] data_;
    
    size_ = matrix.size_;
    data_ = new Type*[size_.rows()];
    for (size_t i = 0; i < size_.rows(); ++i) {
        data_[i] = new Type[size_.columns()];
    }

    for (size_t i = 0; i < size_.rows(); i++) {
        for (size_t j = 0; j < size_.columns(); j++) {
            data_[i][j] = matrix.data_[i][j];
        }
    }
    return *this;
}

template<class Type>
Matrix<Type>& Matrix<Type>::operator+=(const Matrix<Type>& matrix) {
    
    if (!size_.isMatchedForAdditionWith(matrix.size_)) {
        std::cerr << "Error in class Matrix: invalid matrix size for addition.";
        throw;
    }

    for (size_t i = 0; i < size_.rows(); i++) {
        for (size_t j = 0; j < size_.columns(); j++) {
            data_[i][j] += matrix.data_[i][j];
        }
    }

    return *this;
}

template<class Type>
Matrix<Type>& Matrix<Type>::operator-=(const Matrix<Type>& matrix) {
    
    if (!size_.isMatchedForAdditionWith(matrix.size_)) {
        std::cerr << "Error in class Matrix: invalid matrix size for subtraction.";
        throw;
    }

    for (size_t i = 0; i < size_.rows(); i++) {
        for (size_t j = 0; j < size_.columns(); j++) {
            data_[i][j] -= matrix.data_[i][j];
        }
    }

    return *this;
}

template<class Type>
Matrix<Type>& Matrix<Type>::operator*=(const Matrix<Type>& matrix) {
    
    if (!size_.isMatchedForMultiplicationOn(matrix.size_)) {
        std::cerr << "Error in class Matrix: invalid matrix size for multiplication.";
        throw;
    }

    Matrix<Type> temp_argument(matrix);
    Matrix<Type> temp_this(*this);
    Type cell;

    for (size_t i = 0; i < size_.rows(); i++) {
        delete[] data_[i];
    }
    delete[] data_;

    size_ = MatrixSize(size_.rows(), matrix.size_.columns());
    data_ = new Type*[size_.rows()];
    for (size_t i = 0; i < size_.rows(); ++i) {
        data_[i] = new Type[size_.columns()];
    }

    for (size_t i = 0; i < size_.rows(); i++) {
        for (size_t j = 0; j < matrix.size_.columns(); j++) {
            cell = Type();
            for (size_t k = 0; k < size_.columns(); k++) {
                cell += temp_this.data_[i][k] * temp_argument.data_[k][j];
            }
            data_[i][j] = cell;
        }
    }

    return *this;
}

template<class Type>
Matrix<Type>& Matrix<Type>::operator*=(const Type & scalar) {
    
    for (size_t i = 0; i < size_.rows(); i++) {
        for (size_t j = 0; j < size_.columns(); j++) {
            data_[i][j] *= scalar;
        }
    }

    return *this;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator+(const Matrix<Type>& matrix) const {

    if (!size_.isMatchedForAdditionWith(matrix.size_)) {
        std::cerr << "Error in class Matrix: invalid matrix size for addition.";
        throw;
    }

    Matrix<Type> result(size_.rows(), size_.columns());

    for (size_t i = 0; i < size_.rows(); i++) {
        for (size_t j = 0; j < size_.columns(); j++) {
            result[i][j] = data_[i][j] + matrix.data_[i][j];
        }
    }

    return result;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator-(const Matrix<Type>& matrix) const {
    
    if (!size_.isMatchedForAdditionWith(matrix.size_)) {
        std::cerr << "Error in class Matrix: invalid matrix size for subtraction.";
        throw;
    }

    Matrix<Type> result(size_.rows(), size_.columns());

    for (size_t i = 0; i < size_.rows(); i++) {
        for (size_t j = 0; j < size_.columns(); j++) {
            result[i][j] = data_[i][j] - matrix.data_[i][j];
        }
    }

    return result;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator*(const Matrix<Type>& matrix) const {
    
    if (!size_.isMatchedForMultiplicationOn(matrix.size_)) {
        std::cerr << "Error in class Matrix: invalid matrix size for multiplication.";
        throw;
    }

    Matrix<Type> result(size_.rows(), matrix.size_.columns());
    Type cell;


    for (size_t i = 0; i < size_.rows(); i++) {
        for (size_t j = 0; j < matrix.size_.columns(); j++) {
            cell = Type();
            for (size_t k = 0; k < size_.columns(); k++) {
                cell += data_[i][k] * matrix.data_[k][j];
            }
            result.data_[i][j] = cell;
        }
    }

    return result;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator*(const Type & scalar) const {

    Matrix<Type> result(*this);
    result *= scalar;
    return result;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator^(size_t degree) const {

    Matrix<Type> result(*this);
        for (size_t i = 0; i < degree - 1; i++) {
            result *= *this;
        };

        return result;
}

template<class Type>
bool Matrix<Type>::operator==(const Matrix<Type>& matrix) const {
    if (!size_.isMatchedForAdditionWith(matrix.size_)) {
        std::cerr << "Error in class Matrix: invalid matrix size for comparison.";
        throw;
    }

    for (size_t  i = 0; i < size_.columns(); i++) {
        for (size_t j = 0; j < size_.rows(); j++) {
            if (data_[i][j] != matrix.data_[i][j])
                return false;
        }

    }
    return true;
}

template<class Type>
Matrix<Type> Matrix<Type>::transpose() const {
    if (!size_.isMatchedForMultiplicationOn(size_)) {
        std::cerr << "Error in class Matrix: invalid matrix size for transpose.";
        throw;
    }

    Matrix<Type> result(size_.rows(),size_.columns());

    for (size_t i = 0; i < size_.rows()-1; i++) {
        for (size_t j = i + 1; j < size_.columns(); j++) {
            result.data_[i][j] = data_[j][i];
            result.data_[j][i] = data_[i][j];

        }
    }

    for (size_t i = 0; i < size_.columns(); i++) {
        result.data_[i][i] = data_[i][i];
    }

    return result;
}



}
