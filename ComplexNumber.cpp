#include "ComplexNumber.h"



Math::ComplexNumber::ComplexNumber() 
    : real_(0)
    , imaginary_(0) {
}

Math::ComplexNumber::ComplexNumber(double real, double imaginary)
    : real_(real)
    , imaginary_(imaginary) {
}

Math::ComplexNumber::ComplexNumber(const ComplexNumber& obj)
    : real_(obj.real_)
    , imaginary_(obj.imaginary_) {
}

Math::ComplexNumber::~ComplexNumber() = default;
