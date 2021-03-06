#include "ComplexNumber.h"

#include <cmath>



namespace math {



ComplexNumber::ComplexNumber() 
    : real_(0)
    , imaginary_(0) {
}

ComplexNumber::ComplexNumber(double real, double imaginary)
    : real_(real)
    , imaginary_(imaginary) {
}

ComplexNumber::ComplexNumber(const ComplexNumber& complex)
    : real_(complex.real_)
    , imaginary_(complex.imaginary_) {
}

ComplexNumber::~ComplexNumber() = default;

ComplexNumber& ComplexNumber::operator= (const ComplexNumber& complex) {
    real_ = complex.real_;
    imaginary_ = complex.imaginary_;
    return *this;
}

ComplexNumber& ComplexNumber::operator+= (const ComplexNumber& complex) {
    real_ += complex.real_;
    imaginary_ += complex.imaginary_;
    return *this;
}

ComplexNumber& ComplexNumber::operator-= (const ComplexNumber& complex) {
    real_ -= complex.real_;
    imaginary_ -= complex.imaginary_;
    return *this;
}

ComplexNumber& ComplexNumber::operator*= (const ComplexNumber& complex) {
    double this_real = real_;
    double this_imaginary = imaginary_;

    if (this == &complex) {
        real_ = this_real * this_real - this_imaginary * this_imaginary;
        imaginary_ = 2 * this_real * this_imaginary;
        return *this;
    }

    real_ = this_real * complex.real_ - this_imaginary * complex.imaginary_;
    imaginary_ = this_real * complex.imaginary_ + this_imaginary * complex.real_;
    return *this;
}

ComplexNumber& ComplexNumber::operator/= (const ComplexNumber& complex) {
    if (complex.real_ == 0 && complex.imaginary_ == 0) {
        std::cerr << "Error in class ComplexNumber: division by zero.";
        throw;
    }

    if (this == &complex) {
        real_ = 1;
        imaginary_ = 0;
        return *this;
    }

    double this_real = real_;
    double this_imaginary = imaginary_;

    real_ = (this_real * complex.real_ + this_imaginary * complex.imaginary_)
        / (complex.real_ * complex.real_ + complex.imaginary_ * complex.imaginary_);
    imaginary_ = (this_imaginary * complex.real_ - this_real * complex.imaginary_)
        / (complex.real_ * complex.real_ + complex.imaginary_ * complex.imaginary_);
    return *this;
}

ComplexNumber ComplexNumber::operator+ (const ComplexNumber& complex) const {
    return ComplexNumber(real_ + complex.real_, 
                         imaginary_ + complex.imaginary_);
}

ComplexNumber ComplexNumber::operator- (const ComplexNumber& complex) const {
    return ComplexNumber(real_ - complex.real_,
                         imaginary_ - complex.imaginary_);
}

ComplexNumber ComplexNumber::operator* (const ComplexNumber& complex) const {
    return ComplexNumber(real_ * complex.real_ - imaginary_ * complex.imaginary_,
                         real_ * complex.imaginary_ + imaginary_ * complex.real_);
}

ComplexNumber ComplexNumber::operator/ (const ComplexNumber& complex) const {
    if (complex.real_ == 0 && complex.imaginary_ == 0) {
        std::cerr << "Error in class ComplexNumber: division by zero.";
        throw;
    }

    double result_real = (real_ * complex.real_ + imaginary_ * complex.imaginary_) 
        / (complex.real_ * complex.real_ + complex.imaginary_ * complex.imaginary_);

    double result_imaginary = (imaginary_ * complex.real_ - real_ * complex.imaginary_) 
        / (complex.real_ * complex.real_ + complex.imaginary_ * complex.imaginary_);

    return ComplexNumber(result_real, result_imaginary);
}

bool ComplexNumber::operator== (const ComplexNumber& complex) const {
    const double EPS = 1E-9;

    return ((fabs(real_ - complex.real_) < EPS) &&
            (fabs(imaginary_ - complex.imaginary_) < EPS));
}

bool ComplexNumber::operator!= (const ComplexNumber& complex) const {
    return !((*this) == complex);
}

ComplexNumber ComplexNumber::conjugate() const {
    return ComplexNumber(real_, -imaginary_);
}

double ComplexNumber::modulus() const {
    return sqrt(real_ * real_ + imaginary_ * imaginary_);
}

std::ostream& operator<< (std::ostream& out, const ComplexNumber& complex) {
    if (complex.real_ != 0) {
        out << complex.real_;
    }
    if (complex.imaginary_ > 0 && complex.real_ != 0) {
        out << '+';
    }
    if (complex.imaginary_ != 0) {
        if (complex.imaginary_ == 1) {
            out << 'i';
        } else if (complex.imaginary_ == -1) {
            out << "-i";
        } else {
            out << complex.imaginary_ << 'i';
        }
    }
    
    if (complex.real_ == 0 && complex.imaginary_ == 0) {
        out << '0';
    }
    return out;
}



}
