#pragma once

#include <iostream>



namespace math {



class MatrixSize {
public:
    MatrixSize();
    MatrixSize(size_t rows, size_t columns);
    MatrixSize(const MatrixSize& size);
    virtual ~MatrixSize();
    MatrixSize& operator= (const MatrixSize& size);
    bool operator== (const MatrixSize& size) const;
    bool operator!= (const MatrixSize& size) const;
    bool isSquare() const;
    bool isMatchedForMultiplicationOn(const MatrixSize& size) const;
    size_t rows() const;
    size_t columns() const;
    friend std::ostream& operator<< (std::ostream& out, const MatrixSize& size);


protected:
    size_t rows_;
    size_t columns_;
};



}
