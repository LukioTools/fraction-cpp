


#include "fraction.hpp"
#include <iostream>
#include <ostream>
#include <cppostream/vector.hpp>

int main(){
    fraction_t<long> a{5,2};
    fraction_t<long> b{5,7};
    fraction_t<long> c{7,6};
    auto v = fraction_t<long>::normalize_copy<long>(a, b, c);
    std::cout << v << std::endl;
}