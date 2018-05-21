#include "MatrixSize.h"



Math::MatrixSize::MatrixSize()
    : _rows(0)
    , _columns(0) {
}

Math::MatrixSize::MatrixSize(size_t rows, size_t columns)
    : _rows(rows)
    , _columns(columns) {
}

Math::MatrixSize::~MatrixSize() = default;

size_t Math::MatrixSize::rows() const {
    return _rows;
}

size_t Math::MatrixSize::columns() const {
    return _columns;
}
