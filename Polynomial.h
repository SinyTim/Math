#pragma once

#include <vector>



namespace math {



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



}
