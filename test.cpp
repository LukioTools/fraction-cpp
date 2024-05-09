


#include "fraction.hpp"
#include <iostream>
#include <ostream>


int main(){
    fraction_t<long> a{5,2};
    fraction_t<long> b{5,7};
    fraction_t<long> c{7,6};
    fraction_t<long>::normalize(a, b, c);
    std::cout << a.to_double() << " : " << b.to_double() << " : " << c.to_double() << std::endl;
}