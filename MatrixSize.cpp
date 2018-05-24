#include "MatrixSize.h"



math::MatrixSize::MatrixSize()
    : rows_(0)
    , columns_(0) {
}

math::MatrixSize::MatrixSize(size_t rows, size_t columns)
    : rows_(rows)
    , columns_(columns) {
}

math::MatrixSize::~MatrixSize() = default;

size_t math::MatrixSize::rows() const {
    return rows_;
}

size_t math::MatrixSize::columns() const {
    return columns_;
}
