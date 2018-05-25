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

MatrixSize::~MatrixSize() = default;

size_t MatrixSize::rows() const {
    return rows_;
}

size_t MatrixSize::columns() const {
    return columns_;
}

MatrixSize & MatrixSize::operator=(const MatrixSize & size) {
    rows_ = size.rows_;
    columns_ = size.columns_;
    return *this;
}

bool MatrixSize::isMatchedForMultiplicationOn(const MatrixSize & size) const {
    if (columns_== size.rows_) {
        return true;
    } else {
        return false;
    }
}

bool MatrixSize::isMatchedForAdditionWith(const MatrixSize & size) const {
    if (columns_ == size.columns_ && rows_ == size.rows_) {
        return true;
    } else {
        return false;
    }
}



}
