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



}
