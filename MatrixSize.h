#pragma once



namespace math {



class MatrixSize {
public:
    MatrixSize();
    MatrixSize(size_t rows, size_t columns);
    MatrixSize(const MatrixSize& size);
    virtual ~MatrixSize();
    MatrixSize& operator= (const MatrixSize& size);
    bool operator== (const MatrixSize& size) const;
    bool operator!= (const MatrixSize& size) const;
    bool isMatchedForMultiplicationOn(const MatrixSize& size) const;
    size_t rows() const;
    size_t columns() const;


protected:
    size_t rows_;
    size_t columns_;
};



}
