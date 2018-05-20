#pragma once

#include <iostream>



namespace Math {



class ComplexNumber {
public:
    ComplexNumber();
    explicit ComplexNumber(double re, double im);
    explicit ComplexNumber(const ComplexNumber& obj);
    virtual ~ComplexNumber();
    ComplexNumber& operator= (const ComplexNumber& complex);
    ComplexNumber& operator+= (const ComplexNumber& complex);
    ComplexNumber& operator-= (const ComplexNumber& complex);
    ComplexNumber& operator*= (const ComplexNumber& complex);
    ComplexNumber& operator/= (const ComplexNumber& complex);
    ComplexNumber operator+ (const ComplexNumber& complex) const;
    ComplexNumber operator- (const ComplexNumber& complex) const;
    ComplexNumber operator* (const ComplexNumber& complex) const;
    ComplexNumber operator/ (const ComplexNumber& complex) const;
    bool operator== (const ComplexNumber& complex) const;
    ComplexNumber conjugate() const;
    double modulus() const;
    friend std::ostream& operator<< (std::ostream& out, const ComplexNumber& complex);


protected:
    double re;
    double im;
};



}
