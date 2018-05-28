#pragma once

#include <vector>
#include <iostream>



namespace math {


template <class Type>
class Polynomial;

template<class Type>
std::ostream& operator<<(std::ostream& out, const Polynomial<Type>& polynom) {
    if (polynom.coefficients_.size() > 1 ) {
        out << polynom.coefficients_[polynom.coefficients_.size() - 1]
            << "x^" << polynom.coefficients_.size() - 1;
        for (size_t i = polynom.coefficients_.size() - 2; i > 0; --i) {
            if (polynom.coefficients_[i] != Type()) {
                out << " + " << polynom.coefficients_[i] << "*x^" << i;
            }
        }
        if (polynom.coefficients_[0] != Type()) {
            out << polynom.coefficients_[0];
        }

    } else {
        out << polynom.coefficients_[0];
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
    Polynomial<Type> gcd(const Polynomial<Type>& polynom) const;
    Polynomial<Type> derivative() const;
    size_t degree() const;
    Type value(const Type& x) const;
//    std::vector<> roots() const;
    friend std::ostream& operator<< <Type> (std::ostream& out, 
                                            const Polynomial<Type>& polynom);


protected:
    std::vector<Type> coefficients_;
};



template<class Type>
Polynomial<Type>::Polynomial() {
    coefficients_.push_back(Type());
}

template<class Type>
Polynomial<Type>::Polynomial(const std::vector<Type>& coefficients) {
    coefficients_ = coefficients;
}

template<class Type>
Polynomial<Type>::Polynomial(const Polynomial<Type>& polynom) {
    coefficients_ = polynom.coefficients_;
}

template<class Type>
Polynomial<Type>::~Polynomial() {}

template<class Type>
Type& Polynomial<Type>::operator[](size_t coefficient_number) {
    return coefficients_[coefficient_number];
}

template<class Type>
Polynomial<Type>& Polynomial<Type>::operator=(const Polynomial<Type>& polynom) {
    coefficients_ = polynom.coefficients_;
    return *this;
}

template<class Type>
Polynomial<Type>& Polynomial<Type>::operator+=(const Polynomial<Type>& polynom) {
    size_t minSize = coefficients_.size() < polynom.coefficients_.size() ?
        coefficients_.size() : polynom.coefficients_.size();

    for (size_t i = 0; i < minSize; ++i) {
        coefficients_[i] += polynom.coefficients_[i];
    }

    for (size_t i = minSize; i < polynom.coefficients_.size(); ++i) {
        coefficients_.push_back(polynom.coefficients_[i]);
    }

    size_t i = coefficients_.size()-1;
    while (coefficients_[i] == Type()) {
        --i;
    }
    coefficients_.resize(i+1);

    return *this;
}

template<class Type>
Polynomial<Type>& Polynomial<Type>::operator-=(const Polynomial<Type>& polynom) {
    size_t minSize = coefficients_.size() < polynom.coefficients_.size() ?
        coefficients_.size() : polynom.coefficients_.size();

    for (size_t i = 0; i < minSize; ++i) {
        coefficients_[i] -= polynom.coefficients_[i];
    }

    for (size_t i = minSize; i < polynom.coefficients_.size(); ++i) {
        coefficients_.push_back(-polynom.coefficients_[i]);
    }

    size_t i = coefficients_.size() - 1;
    while (coefficients_[i] == Type() ) {
        --i;
    }
    coefficients_.resize(i + 1);

    return *this;
}

template<class Type>
Polynomial<Type>& Polynomial<Type>::operator*=(const Polynomial<Type>& polynom) {
    Polynomial<Type> temp_this(*this);
    coefficients_.clear();
    coefficients_.resize(temp_this.coefficients_.size() + polynom.coefficients_.size() - 1);

    for (size_t i = 0; i < temp_this.coefficients_.size(); ++i) {
        for (size_t j = 0; j < polynom.coefficients_.size(); j++) {
            coefficients_[i + j] += temp_this.coefficients_[i] * polynom.coefficients_[j];
        }
    }

    return *this;
}

template<class Type>
Polynomial<Type> Polynomial<Type>::operator+(const Polynomial<Type>& polynom) const {
    Polynomial<Type> temp_this(*this);
    temp_this += polynom;
    return temp_this;
}

template<class Type>
Polynomial<Type> Polynomial<Type>::operator-(const Polynomial<Type>& polynom) const {
    Polynomial<Type> temp_this(*this);
    temp_this -= polynom;
    return temp_this;
}

template<class Type>
inline Polynomial<Type> Polynomial<Type>::operator*(const Polynomial<Type>& polynom) const {
    Polynomial<Type> temp_this(*this);
    temp_this *= polynom;
    return temp_this;
}

template<class Type>
Polynomial<Type> Polynomial<Type>::operator/(const Polynomial<Type>& polynom) const {
    if (coefficients_.size() < polynom.coefficients_.size()) {
        return Polynomial<Type>();
    }
    Polynomial<Type> res;
    Polynomial<Type> temp_this(*this);
    for (size_t i = coefficients_.size()-1; i >= polynom.coefficients_.size()-1; --i) {
        Type coef = temp_this.coefficients_[i] /
            *polynom.coefficients_.rbegin();
        
        std::vector<Type> tempV;
        tempV.resize(i + 1 - polynom.coefficients_.size());
        tempV.push_back(coef);
        Polynomial<Type> tempSum(tempV);
        res += tempSum;

        for (size_t j = 0; j < polynom.coefficients_.size(); ++j) {
            temp_this.coefficients_[i-j] -= coef * (*(polynom.coefficients_.rbegin()+j));
        }
        temp_this.coefficients_.resize(temp_this.coefficients_.size() - 1);
    }

    return res;
}

template<class Type>
Polynomial<Type> Polynomial<Type>::operator%(const Polynomial<Type>& polynom) const {
    Polynomial<Type> div;
    div = (*this) / polynom;
    return (*this)-div*polynom;
}



}
