#include "ComplexNumber.h"

using namespace Math;

ComplexNumber::ComplexNumber() 
    : real_(0)
    , imaginary_(0) {
}

ComplexNumber::ComplexNumber(double real, double imaginary)
    : real_(real)
    , imaginary_(imaginary) {
}

ComplexNumber::ComplexNumber(const ComplexNumber& obj)
    : real_(obj.real_)
    , imaginary_(obj.imaginary_) {
}

ComplexNumber::~ComplexNumber() = default;

ComplexNumber& ComplexNumber::operator= (const ComplexNumber& complex)
{

	real_ = complex.real_;
	imaginary_ = complex.imaginary_;
	return *this;
}

ComplexNumber& ComplexNumber::operator+= (const ComplexNumber& complex){


	real_ += complex.real_;
	imaginary_ += complex.imaginary_;
	return *this;
}

ComplexNumber& ComplexNumber::operator-= (const ComplexNumber& complex){


	real_ -= complex.real_;
	imaginary_ -= complex.imaginary_;
	return *this;
}

ComplexNumber& ComplexNumber::operator*= (const ComplexNumber& complex){
	double this_real = real_, this_imaginary = imaginary_;

	if (this == &complex){
		real_ = real_*real_-imaginary_*imaginary_;
		imaginary_ = 2*this_real*imaginary_;
		return *this;
	}

	real_ = this_real*complex.real_-this_imaginary*complex.imaginary_;
	imaginary_ = this_real*complex.imaginary_+this_imaginary*complex.real_;
	return *this;
}

ComplexNumber& ComplexNumber::operator/= (const ComplexNumber& complex){
	double this_real = real_, this_imaginary = imaginary_;

	if (this == &complex){
		real_ = 1;
		imaginary_ = 0;
		return *this;
	}

	real_ = (this_real*complex.real_ + this_imaginary*complex.imaginary_) / (complex.real_*complex.real_ + complex.imaginary_*complex.imaginary_);
	imaginary_ = (this_imaginary*complex.real_ - this_real*complex.imaginary_) / (complex.real_*complex.real_ + complex.imaginary_*complex.imaginary_);
	return *this;
}

ComplexNumber ComplexNumber::operator+(const ComplexNumber& complex) const{
	Math::ComplexNumber cmpl(complex.real_+real_,complex.imaginary_+imaginary_);
	return cmpl;
}


std::ostream& Math::operator<< (std::ostream& out, const ComplexNumber& complex){
	if (complex.imaginary_ > 0 && complex.real_ != 0) {
		out << complex.real_ << "+" << complex.imaginary_ << "i";
	} else if (complex.imaginary_ < 0 && complex.real_ != 0) {
		out << complex.real_ << "+(" << complex.imaginary_ << ")i";
	} else if (complex.real_ == 0 && complex.imaginary_ != 0) {
		out << complex.imaginary_ << "i";
	} else {
		out << complex.real_;
	}
	return out;
}