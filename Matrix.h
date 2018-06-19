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
    explicit Matrix(Type** arr, const MatrixSize& size);
    Matrix(const Matrix<Type>& matrix);
    Matrix(std::initializer_list< std::initializer_list<Type> > list);
    virtual ~Matrix();
    Type& operator() (size_t row, size_t column);
    Type operator() (size_t row, size_t column) const;
    Matrix<Type>& operator= (const Matrix<Type>& matrix);
    Matrix<Type>& operator+= (const Matrix<Type>& matrix);
    Matrix<Type>& operator-= (const Matrix<Type>& matrix);
    Matrix<Type>& operator*= (const Matrix<Type>& matrix);
    Matrix<Type>& operator*= (const Type& scalar);
    Matrix<Type> operator+ (const Matrix<Type>& matrix) const;
    Matrix<Type> operator- (const Matrix<Type>& matrix) const;
    Matrix<Type> operator* (const Matrix<Type>& matrix) const;
    Matrix<Type> operator* (const Type& scalar) const;
    Matrix<Type> operator^ (size_t degree) const;
    bool operator== (const Matrix<Type>& matrix) const;
    bool operator!= (const Matrix<Type>& matrix) const;
    Matrix<Type> withoutRow(size_t row_number) const;
    Matrix<Type> withoutColumn(size_t column_number) const;
    Matrix<Type> transpose() const;
    //Matrix<Type> invertible() const;
    Type determinant() const;
    //size_t rank() const;
    MatrixSize size() const;
    Type** data() const;
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

template <class Type>
Matrix<Type>::Matrix(Type** arr, const MatrixSize& size) 
    : size_(size) {

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
Matrix<Type>::Matrix(const Matrix<Type>& matrix)
    : size_(matrix.size_) {

    data_ = new Type*[size_.rows()];
    for (size_t i = 0; i < size_.rows(); ++i) {
        data_[i] = new Type[size_.columns()];
    }

    for (size_t i = 0; i < size_.rows(); ++i) {
        for (size_t j = 0; j < size_.columns(); ++j) {
            data_[i][j] = matrix.data_[i][j];
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
Type& Matrix<Type>::operator() (size_t row, size_t column) {
    if ((row >= size_.rows()) || (column >= size_.columns())) {
        std::cerr << "Error in class Matrix: invalid parameters.";
        throw;
    }
    return data_[row][column];
}

template<class Type>
Type Matrix<Type>::operator() (size_t row, size_t column) const {
    if ((row >= size_.rows()) || (column >= size_.columns())) {
        std::cerr << "Error in class Matrix: invalid parameters.";
        throw;
    }
    return data_[row][column];
}

template<class Type>
Matrix<Type>& Matrix<Type>::operator= (const Matrix<Type>& matrix) {
    if (this == &matrix) {
        return *this;
    }

    for (size_t i = 0; i < size_.rows(); ++i) {
        delete [] data_[i];
    }
    delete [] data_;
    
    size_ = matrix.size_;
    data_ = new Type*[size_.rows()];
    for (size_t i = 0; i < size_.rows(); ++i) {
        data_[i] = new Type[size_.columns()];
    }

    for (size_t i = 0; i < size_.rows(); ++i) {
        for (size_t j = 0; j < size_.columns(); ++j) {
            data_[i][j] = matrix.data_[i][j];
        }
    }
    return *this;
}

template<class Type>
Matrix<Type>& Matrix<Type>::operator+= (const Matrix<Type>& matrix) {
    
    if (size_ != matrix.size_) {
        std::cerr << "Error in class Matrix: invalid matrix size for addition.";
        throw;
    }

    for (size_t i = 0; i < size_.rows(); ++i) {
        for (size_t j = 0; j < size_.columns(); ++j) {
            data_[i][j] += matrix.data_[i][j];
        }
    }

    return *this;
}

template<class Type>
Matrix<Type>& Matrix<Type>::operator-= (const Matrix<Type>& matrix) {
    
    if (size_ != matrix.size_) {
        std::cerr << "Error in class Matrix: invalid matrix size for subtraction.";
        throw;
    }

    for (size_t i = 0; i < size_.rows(); ++i) {
        for (size_t j = 0; j < size_.columns(); ++j) {
            data_[i][j] -= matrix.data_[i][j];
        }
    }

    return *this;
}

template<class Type>
Matrix<Type>& Matrix<Type>::operator*= (const Matrix<Type>& matrix) {
    
    if (!size_.isMatchedForMultiplicationOn(matrix.size_)) {
        std::cerr << "Error in class Matrix: invalid matrix size for multiplication.";
        throw;
    }

    Matrix<Type> temp_this(*this);
    Matrix<Type> temp_argument(matrix);
    Type result_cell;

    for (size_t i = 0; i < size_.rows(); ++i) {
        delete[] data_[i];
    }
    delete[] data_;

    size_ = MatrixSize(size_.rows(), matrix.size_.columns());
    data_ = new Type*[size_.rows()];
    for (size_t i = 0; i < size_.rows(); ++i) {
        data_[i] = new Type[size_.columns()];
    }

    for (size_t i = 0; i < size_.rows(); ++i) {
        for (size_t j = 0; j < size_.columns(); ++j) {
            result_cell = Type();
            for (size_t k = 0; k < temp_this.size_.columns(); ++k) {
                result_cell += temp_this.data_[i][k] * temp_argument.data_[k][j];
            }
            data_[i][j] = result_cell;
        }
    }

    return *this;
}

template<class Type>
Matrix<Type>& Matrix<Type>::operator*= (const Type& scalar) {
    
    for (size_t i = 0; i < size_.rows(); ++i) {
        for (size_t j = 0; j < size_.columns(); ++j) {
            data_[i][j] *= scalar;
        }
    }

    return *this;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator+ (const Matrix<Type>& matrix) const {

    if (size_ != matrix.size_) {
        std::cerr << "Error in class Matrix: invalid matrix size for addition.";
        throw;
    }

    Matrix<Type> result(*this);
    result += matrix;

    return result;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator- (const Matrix<Type>& matrix) const {
    
    if (size_ != matrix.size_) {
        std::cerr << "Error in class Matrix: invalid matrix size for subtraction.";
        throw;
    }

    Matrix<Type> result(*this);
    result -= matrix;

    return result;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator* (const Matrix<Type>& matrix) const {
    
    if (!size_.isMatchedForMultiplicationOn(matrix.size_)) {
        std::cerr << "Error in class Matrix: invalid matrix size for multiplication.";
        throw;
    }

    Matrix<Type> result(*this);
    result *= matrix;

    return result;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator* (const Type& scalar) const {

    Matrix<Type> result(*this);
    result *= scalar;
    return result;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator^ (size_t degree) const {

    if (degree == 0) {
        std::cerr << "Error in class Matrix: zero degree.";
        throw;
    }

    Matrix<Type> result(*this);
    for (size_t i = 0; i < degree - 1; ++i) {
        result *= *this;
    }

    return result;
}

template<class Type>
bool Matrix<Type>::operator== (const Matrix<Type>& matrix) const {

    if (size_ != matrix.size_) {
        std::cerr << "Error in class Matrix: invalid matrix size for comparison.";
        throw;
    }

    for (size_t  i = 0; i < size_.rows(); ++i) {
        for (size_t j = 0; j < size_.columns(); ++j) {
            if (data_[i][j] != matrix.data_[i][j]) {
                return false;
            }
        }

    }
    return true;
}

template<class Type>
bool Matrix<Type>::operator!= (const Matrix<Type>& matrix) const {
    return !((*this) == matrix);
}

template<class Type>
Matrix<Type> Matrix<Type>::withoutRow(size_t row_number) const {

    if (row_number >= size_.rows()) {
        std::cerr << "Error in class Matrix: invalid row number.";
        throw;
    }

    if (size_.rows() == 1) {
        return Matrix<Type>();
    }

    Matrix<Type> result(size_.rows() - 1, size_.columns());

    size_t i_result = 0;
    for (size_t i = 0; i < size_.rows(); ++i) {
        if (i == row_number) {
            continue;
        }
        for (size_t j = 0; j < size_.columns(); ++j) {
            result(i_result, j) = data_[i][j];
        }
        ++i_result;
    }

    return result;
}

template<class Type>
Matrix<Type> Matrix<Type>::withoutColumn(size_t column_number) const {

    if (column_number >= size_.columns()) {
        std::cerr << "Error in class Matrix: invalid column number.";
        throw;
    }

    if (size_.columns() == 1) {
        return Matrix<Type>();
    }

    Matrix<Type> result(size_.rows(), size_.columns() - 1);

    size_t j_result = 0;
    for (size_t i = 0; i < size_.rows(); ++i) {
        j_result = 0;
        for (size_t j = 0; j < size_.columns(); ++j) {
            if (j == column_number) {
                continue;
            }
            result(i, j_result) = data_[i][j];
            ++j_result;
        }
    }

    return result;
}

template<class Type>
Matrix<Type> Matrix<Type>::transpose() const {

    Matrix<Type> result(size_.columns(), size_.rows());

    for (size_t i = 0; i < size_.rows(); ++i) {
        for (size_t j = 0; j < size_.columns(); ++j) {
            result(j, i) = data_[i][j];
        }
    }

    return result;
}

template<class Type>
Type Matrix<Type>::determinant() const {

    if (!size_.isSquare()) {
        std::cerr << "Error in class Matrix: invalid matrix size for determinant.";
        throw;
    }

    if (size_ == MatrixSize(1, 1)) {
        return data_[0][0];
    }

    Type determinant = Type();
    Matrix<Type> current_minor;

    for (size_t i = 0; i < size_.rows(); ++i) {
        current_minor = this->withoutRow(i);
        current_minor = current_minor.withoutColumn(0);

        if (i % 2 == 0) {
            determinant += data_[i][0] * current_minor.determinant();
        } else {
            determinant -= data_[i][0] * current_minor.determinant();
        }
    }

    return determinant;
}

template<class Type>
MatrixSize Matrix<Type>::size() const {
    return size_;
}

template<class Type>
Type** Matrix<Type>::data() const {
    return data_;
}



}
