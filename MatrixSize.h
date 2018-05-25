#pragma once



namespace math {



class MatrixSize {
public:
    MatrixSize();
    explicit MatrixSize(size_t rows, size_t columns);
    virtual ~MatrixSize();
    size_t rows() const;
    size_t columns() const;
    MatrixSize& operator=(const MatrixSize& size);
    bool isMatchedForMultiplicationOn(const MatrixSize& size) const;
    bool isMatchedForAdditionWith(const MatrixSize& size) const;


protected:
    size_t rows_;
    size_t columns_;
};



}
