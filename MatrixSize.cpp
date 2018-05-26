#include "MatrixSize.h"



namespace math {



MatrixSize::MatrixSize()
    : rows_(0)
    , columns_(0) {
}

MatrixSize::MatrixSize(size_t rows, size_t columns)
    : rows_(rows)
    , columns_(columns) {
}

MatrixSize::MatrixSize(const MatrixSize& size) 
    : rows_(size.rows_)
    , columns_ (size.columns_) {
}

MatrixSize::~MatrixSize() = default;

MatrixSize& MatrixSize::operator= (const MatrixSize& size) {
    rows_ = size.rows_;
    columns_ = size.columns_;
    return *this;
}

bool MatrixSize::operator== (const MatrixSize& size) const {
    return (rows_ == size.rows_) && (columns_ == size.columns_);
}

bool MatrixSize::operator!= (const MatrixSize& size) const {
    return (rows_ != size.rows_) || (columns_ != size.columns_);
}

bool MatrixSize::isMatchedForMultiplicationOn(const MatrixSize& size) const {
    return (columns_ == size.rows_);
}

size_t MatrixSize::rows() const {
    return rows_;
}

size_t MatrixSize::columns() const {
    return columns_;
}



}
