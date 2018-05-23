#pragma once



namespace Math {



class MatrixSize {
public:
    MatrixSize();
    explicit MatrixSize(size_t rows, size_t columns);
    virtual ~MatrixSize();
    size_t rows() const;
    size_t columns() const;


protected:
    const size_t rows_;
    const size_t columns_;
};



}
