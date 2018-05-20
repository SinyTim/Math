#include "MatrixSize.h"



Math::MatrixSize::MatrixSize()
    : rows(0)
    , columns(0) {
}

Math::MatrixSize::MatrixSize(size_t rows, size_t columns)
    : rows(rows)
    , columns(columns) {
}

Math::MatrixSize::~MatrixSize() = default;
