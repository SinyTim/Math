#pragma once

#include <vector>
#include <iostream>



namespace math {



template <class Type>
class Polynomial;

template<class Type>
std::ostream& operator<< (std::ostream& out, const Polynomial<Type>& polynom) {

    for (size_t i = polynom.coefficients_.size() - 1; i > 0; --i) {

        if (polynom[i] != Type()) {
            out << "(" << polynom[i] << ")*x^" << i;
        }
        if (polynom[i - 1] != Type()) {
            out << " + ";
        }
    }

    if ((polynom[0] != Type()) || (polynom.degree() == 0)) {
        out << "(" << polynom.coefficients_[0] << ")";
    }

    return out;
}



template <class Type>
class Polynomial {

public:
    Polynomial();
    Polynomial(const std::vector<Type>& coefficients);
    Polynomial(const Polynomial<Type>& polynom);
    virtual ~Polynomial();
    Type& operator[] (size_t coefficient_number);
    Type operator[] (size_t coefficient_number) const;
    Polynomial<Type>& operator= (const Polynomial<Type>& polynom);
    Polynomial<Type>& operator+= (const Polynomial<Type>& polynom);
    Polynomial<Type>& operator-= (const Polynomial<Type>& polynom);
    Polynomial<Type>& operator*= (const Polynomial<Type>& polynom);
    Polynomial<Type> operator+ (const Polynomial<Type>& polynom) const;
    Polynomial<Type> operator- (const Polynomial<Type>& polynom) const;
    Polynomial<Type> operator* (const Polynomial<Type>& polynom) const;
    Polynomial<Type> operator/ (const Polynomial<Type>& polynom) const;
    Polynomial<Type> operator% (const Polynomial<Type>& polynom) const;
    bool operator== (const Polynomial<Type>& polynom) const;
    bool operator!= (const Polynomial<Type>& polynom) const;
    Polynomial<Type> gcd(const Polynomial<Type>& polynom) const;
    Polynomial<Type> derivative() const;
    size_t degree() const;
    Type value(const Type& x) const;
    friend std::ostream& operator<< <Type> (std::ostream& out, 
                                            const Polynomial<Type>& polynom);
protected:
    void eraseLeadingZeros();


protected:
    std::vector<Type> coefficients_;
};



template<class Type>
Polynomial<Type>::Polynomial() {
    coefficients_.push_back(Type());
}

template<class Type>
Polynomial<Type>::Polynomial(const std::vector<Type>& coefficients) {

    if (!coefficients.empty()) {
        coefficients_ = coefficients;
    } else {
        coefficients_.push_back(Type());
    }

    size_t i = coefficients_.size() - 1;
    while ((coefficients_[i] == Type()) && (i > 0)) {
        coefficients_.pop_back();
        --i;
    }
}

template<class Type>
Polynomial<Type>::Polynomial(const Polynomial<Type>& polynom) {
    coefficients_ = polynom.coefficients_;
}

template<class Type>
Polynomial<Type>::~Polynomial() = default;

template<class Type>
Type& Polynomial<Type>::operator[] (size_t coefficient_number) {
    if (coefficient_number >= coefficients_.size()) {
        std::cerr << "Error in class Polynomial: invalid coefficient number.";
        throw;
    }
    return coefficients_[coefficient_number];
}

template<class Type>
Type Polynomial<Type>::operator[] (size_t coefficient_number) const {
    if (coefficient_number >= coefficients_.size()) {
        std::cerr << "Error in class Polynomial: invalid coefficient number.";
        throw;
    }
    return coefficients_[coefficient_number];
}

template<class Type>
Polynomial<Type>& Polynomial<Type>::operator= (const Polynomial<Type>& polynom) {
    coefficients_ = polynom.coefficients_;
    return *this;
}

template<class Type>
Polynomial<Type>& Polynomial<Type>::operator+= (const Polynomial<Type>& polynom) {

    size_t min_size = (coefficients_.size() < polynom.coefficients_.size()) ?
                       coefficients_.size() : polynom.coefficients_.size();

    for (size_t i = 0; i < min_size; ++i) {
        coefficients_[i] += polynom[i];
    }

    for (size_t i = min_size; i < polynom.coefficients_.size(); ++i) {
        coefficients_.push_back(polynom[i]);
    }

    eraseLeadingZeros();

    return *this;
}

template<class Type>
Polynomial<Type>& Polynomial<Type>::operator-= (const Polynomial<Type>& polynom) {

    size_t min_size = (coefficients_.size() < polynom.coefficients_.size()) ?
                       coefficients_.size() : polynom.coefficients_.size();

    for (size_t i = 0; i < min_size; ++i) {
        coefficients_[i] -= polynom[i];
    }

    for (size_t i = min_size; i < polynom.coefficients_.size(); ++i) {
        coefficients_.push_back(-polynom[i]);
    }

    eraseLeadingZeros();

    return *this;
}

template<class Type>
Polynomial<Type>& Polynomial<Type>::operator*= (const Polynomial<Type>& polynom) {

    Polynomial<Type> temp_this(*this);
    coefficients_.clear();
    coefficients_.resize(temp_this.degree() + polynom.degree() + 1);

    for (size_t i = 0; i < temp_this.coefficients_.size(); ++i) {
        for (size_t j = 0; j < polynom.coefficients_.size(); ++j) {
            coefficients_[i + j] += temp_this[i] * polynom[j];
        }
    }

    eraseLeadingZeros();

    return *this;
}

template<class Type>
Polynomial<Type> Polynomial<Type>::operator+ (const Polynomial<Type>& polynom) const {
    Polynomial<Type> temp_this(*this);
    temp_this += polynom;
    return temp_this;
}

template<class Type>
Polynomial<Type> Polynomial<Type>::operator- (const Polynomial<Type>& polynom) const {
    Polynomial<Type> temp_this(*this);
    temp_this -= polynom;
    return temp_this;
}

template<class Type>
Polynomial<Type> Polynomial<Type>::operator* (const Polynomial<Type>& polynom) const {
    Polynomial<Type> temp_this(*this);
    temp_this *= polynom;
    return temp_this;
}

template<class Type>
Polynomial<Type> Polynomial<Type>::operator/ (const Polynomial<Type>& polynom) const {
    if (coefficients_.size() < polynom.coefficients_.size()) {
        return Polynomial<Type>();
    }
    if ((polynom.coefficients_.size() == 0)
        || (polynom.coefficients_.size() == 1 && polynom.coefficients_[0] == Type())) {
        std::cerr << "Error in class Polynomial: divide by zero.";
        throw;
    }

    Polynomial<Type> result;
    result.coefficients_.resize(coefficients_.size() - polynom.coefficients_.size() + 1);
    
    Polynomial<Type> temp_this(*this);

    for (size_t i = coefficients_.size() - 1; i >= polynom.coefficients_.size() - 1; --i) {
        Type coef = temp_this.coefficients_[i] / polynom.coefficients_.back();

        result[i - polynom.coefficients_.size() + 1] = coef;

        for (size_t j = 0; j < polynom.coefficients_.size(); ++j) {
            temp_this[i - j] -= coef * (*(polynom.coefficients_.rbegin() + j));
        }
        temp_this.coefficients_.pop_back();
    }

    return result;
}

template<class Type>
Polynomial<Type> Polynomial<Type>::operator% (const Polynomial<Type>& polynom) const {
    Polynomial<Type> quotient;
    quotient = (*this) / polynom;
    return (*this) - (quotient * polynom);
}

template<class Type>
bool Polynomial<Type>::operator== (const Polynomial<Type>& polynom) const {

    if (coefficients_.size() != polynom.coefficients_.size()) {
        return false;
    }
    for (size_t i = 0; i < coefficients_.size(); ++i) {
        if (coefficients_[i] != polynom[i]) {
            return false;
        }
    }

    return true;
}

template<class Type>
bool Polynomial<Type>::operator!= (const Polynomial<Type>& polynom) const {
    return !((*this) == polynom);
}

template<class Type>
Polynomial<Type> Polynomial<Type>::gcd(const Polynomial<Type>& polynom) const {

    Polynomial<Type> temp_this(*this);
    Polynomial<Type> temp_polynom(polynom);
    Polynomial<Type> temp;

    while (temp_polynom != Polynomial<Type>()) {

        temp_this = temp_this % temp_polynom;

        temp = temp_this;
        temp_this = temp_polynom;
        temp_polynom = temp;
    }

    for (size_t i = 0; i < temp_this.coefficients_.size(); ++i) {
        temp_this.coefficients_[i] /= temp_this.coefficients_.back();
    }

    return temp_this;
}

template<class Type>
Polynomial<Type> Polynomial<Type>::derivative() const {
    vector<Type> derivative_coefficients;
    for (size_t i = 1; i < coefficients_.size(); ++i) {
        derivative_coefficients.push_back(coefficients_[i] * i);
    }
    return Polynomial<Type>(derivative_coefficients);
}

template<class Type>
size_t Polynomial<Type>::degree() const {
    return (coefficients_.size() - 1);
}

template<class Type>
Type Polynomial<Type>::value(const Type& x) const {
    Type result = coefficients_[0];
    Type temp;

    for (size_t i = 1; i < coefficients_.size(); ++i) {
        temp = coefficients_[i];
        for (size_t j = 0; j < i; ++j) {
            temp *= x;
        }
        result += temp;
    }
    return result;
}

template<class Type>
void Polynomial<Type>::eraseLeadingZeros() {

    size_t i = coefficients_.size() - 1;

    while ((coefficients_[i] == Type()) && (i > 0)) {
        coefficients_.pop_back();
        --i;
    }
}



}
