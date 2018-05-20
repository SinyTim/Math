#include "ComplexNumber.h"



Math::ComplexNumber::ComplexNumber() 
    : re(0)
    , im(0) {
}

Math::ComplexNumber::ComplexNumber(double re, double im)
    : re(re)
    , im(im) {
}

Math::ComplexNumber::ComplexNumber(const ComplexNumber& obj)
    : re(obj.re)
    , im(obj.im) {
}

Math::ComplexNumber::~ComplexNumber() = default;
