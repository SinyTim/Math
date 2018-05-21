#include "MatrixSize.h"



Math::MatrixSize::MatrixSize()
    : rows_(0)
    , columns_(0) {
}

Math::MatrixSize::MatrixSize(size_t rows, size_t columns)
    : rows_(rows)
    , columns_(columns) {
}

Math::MatrixSize::~MatrixSize() = default;

size_t Math::MatrixSize::rows() const {
    return rows_;
}

size_t Math::MatrixSize::columns() const {
    return columns_;
}
