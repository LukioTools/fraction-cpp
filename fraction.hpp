#pragma once





#include <cmath>
#include <cstddef>
#include <iostream>
#include <limits>
#include <numeric>
#include <ostream>
#include <stdexcept>
#include <type_traits>
#include <vector>
template<typename T>
class fraction_t{
public:
    T numerator     = 0;
    T denominator   = 1;


    
    template<class...Va>
    requires(std::is_same_v<Va, fraction_t<T>> && ... ) 
    inline static void normalize(fraction_t<T>& first, Va&...rest){
        size_t lcm = first.denominator;
        ((lcm = std::lcm(lcm, rest.denominator)), ...);
        fraction_t<T> lf(lcm, 1);
        first*=lf;
        (operator*=(rest,lf),...);
        //first.reduce();
        //(rest.reduce(), ...);
    }
    template<typename Tn, class...Va>
    requires(std::is_same_v<Va, fraction_t<T>> && ... ) 
    inline static std::vector<Tn> normalize_copy(const fraction_t<T>& first, const Va&...rest){
        size_t lcm = first.denominator;
        ((lcm = std::lcm(lcm, rest.denominator)), ...);
        fraction_t<T> lf(lcm, 1);
        std::vector<Tn> tn;
        tn.reserve(sizeof...(rest)+1);
        tn.push_back((first*lf).template to<Tn>());
        (
            [&]{
                tn.push_back(operator*(rest,lf).template to<Tn>());
            }(), ...
        );
        return tn;
    }
    template<class Tn>
    Tn to(){
        return Tn(numerator)/Tn(denominator);
    }

    void expand(T t){
        numerator*=t;
        denominator*=t;
    }

    fraction_t<T> expand_copy(T t){
        return {numerator*t, denominator*t};
    }
    void reduce(){
        auto gcd = std::gcd(numerator, denominator);
        numerator = numerator/gcd;
        denominator =denominator/gcd;
        if (numerator < 0 && denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }
    fraction_t<T> reduce_copy() const{
        auto gcd = std::gcd(numerator, denominator);
        fraction_t<T> out(numerator/gcd, denominator/gcd);
        if (out.numerator < 0 && out.denominator < 0) {
            out.numerator = -out.numerator;
            out.denominator = -out.denominator;
        }
        return out;
    }

    void invert(){
        T n = numerator;
        numerator = denominator;
        denominator = n;
    }
    fraction_t<T> invert_copy() const{
        return {denominator, numerator};
    }

    friend fraction_t<T> operator+(const fraction_t<T>& a, const fraction_t<T>& b){
        return {
            a.numerator*b.denominator+b.numerator*a.denominator,
            a.denominator*b.denominator
        };
    }

    friend fraction_t<T> operator-(const fraction_t<T>& a, const fraction_t<T>& b){
        return {
            a.numerator*b.denominator-b.numerator*a.denominator,
            a.denominator*b.denominator
        };
    }

    friend fraction_t<T> operator*(const fraction_t<T>& a, const fraction_t<T>& b){
        return {
            a.numerator*b.numerator,
            a.denominator*b.denominator
        };
    }

    friend fraction_t<T> operator/(const fraction_t<T>& a, const fraction_t<T>& b){
        return {
            a.numerator*b.denominator,
            a.denominator*b.numerator
        };
    }

    friend void operator+=(fraction_t<T>& a, const fraction_t<T>& b){
        a.numerator*=b.denominator;
        a.numerator+=(b.numerator*a.denominator);
        a.denominator*=b.denominator;
    }

    friend void operator-=(fraction_t<T>& a, const fraction_t<T>& b){
        a.numerator*=b.denominator;
        a.numerator-=(b.numerator*a.denominator);
        a.denominator*=b.denominator;
    }

    friend void operator*=(fraction_t<T>& a, const fraction_t<T>& b){
        a.numerator*=b.numerator;
        a.denominator*=b.denominator;
    }

    friend void operator/=(fraction_t<T>& a, const fraction_t<T>& b){
        a.numerator*=b.denominator;
        a.denominator*=b.numerator;
    }

    bool operator>=(fraction_t<T> compare)const{
        return numerator*compare.denominator >= compare.numerator*denominator;
    }
    bool operator<=(fraction_t<T> compare)const{
        return numerator*compare.denominator <= compare.numerator*denominator;
    }
    bool operator>(fraction_t<T> compare)const{
        return numerator*compare.denominator > compare.numerator*denominator;
    }
    bool operator<(fraction_t<T> compare)const{
        return numerator*compare.denominator < compare.numerator*denominator;
    }
    bool operator==(fraction_t<T> compare) const{
        if(denominator == compare.denominator) return numerator == compare.numerator;

    }
    double to_double()const{
        if(denominator == 0) throw std::runtime_error(std::string("fraction_t<") + typeid(T).name() + ">::to_double::denominator == 0");
        return numerator/double(denominator);
    }
    void operator=(T i) noexcept{
        numerator = i;
    }
    void operator=(double input){
        double integral = std::floor(input);
        double frac = input - integral;
        constexpr T precision = std::numeric_limits<T>::max(); // This is the accuracy.
        long gcd_ = std::gcd(long(std::round(frac * precision)), precision);
        denominator = precision / gcd_;
        numerator = round(frac * precision) / gcd_;
        reduce();
        numerator+=integral*denominator;
        reduce();
    }

    friend std::ostream& operator<<(std::ostream& os, const fraction_t<T>& f){
        return os << f.numerator << '/' << f.denominator;
    }

    fraction_t(){}
    fraction_t(T numerator) : numerator(numerator){}
    fraction_t(T numerator, T denominator) : numerator(numerator), denominator(denominator){}
    fraction_t(double d){
        this->operator=(d);
    }
};
