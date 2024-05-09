


#include "fraction.hpp"
#include <iomanip>
#include <iostream>
int main(){
    double d = 0.24412389123891238912389;
    fraction_t<unsigned long> f = d;
    std::cout << std::setprecision(20) << (unsigned long) f.numerator << "/" << (unsigned long) f.denominator << " = " << f.to_double() << " = " << d << std::endl; 
}