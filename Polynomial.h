#pragma once

#include <vector>



namespace Math {



template <class Type>
class Polynomial {

public:
    Polynomial();
    explicit Polynomial(const std::vector<Type>& coefficients);
    explicit Polynomial(const Polynomial<Type>& polynom);
    Polynomial(std::initializer_list<Type> list);
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
