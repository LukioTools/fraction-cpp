#pragma once





#include <cmath>
#include <limits>
#include <numeric>
#include <stdexcept>
template<typename T>
class fraction_t{
public:
    T numerator     = 0;
    T denominator   = 1;


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
            a.numerator*b.denominator*b.numerator*a.denominator,
            a.denominator*b.denominator
        };
    }

    friend fraction_t<T> operator/(const fraction_t<T>& a, const fraction_t<T>& b){
        return {
            a.numerator*b.denominator/b.numerator*a.denominator,
            a.denominator*b.denominator
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
        a.numerator*=b.denominator;
        a.numerator*=(b.numerator*a.denominator);
        a.denominator*=b.denominator;
    }

    friend void operator/=(fraction_t<T>& a, const fraction_t<T>& b){
        a.numerator*=b.denominator;
        a.numerator/=(b.numerator*a.denominator);
        a.denominator*=b.denominator;
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

    fraction_t(){}
    fraction_t(T numerator) : numerator(numerator){}
    fraction_t(T numerator, T denominator) : numerator(numerator), denominator(denominator){}
    fraction_t(double d){
        this->operator=(d);
    }
};
