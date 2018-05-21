#pragma once



namespace Math {



class MatrixSize {
public:
    MatrixSize();
    MatrixSize(size_t rows, size_t columns);
    ~MatrixSize();
    size_t rows() const;
    size_t columns() const;


private:
    const size_t _rows;
    const size_t _columns;
};



}
