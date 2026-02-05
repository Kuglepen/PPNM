#include<iostream>
#include<cmath>
#include"sfuns.h"
#include<numbers>
#include<complex>

using complex=std::complex<double>;

constexpr double PI = std::numbers::pi;
constexpr double E  = std::numbers::e;
constexpr complex I = complex(0,1);

int main() {
//  some numbers calculations

    std::cout << "sqrt(2) = " << sfuns::sqrt2() << "\n";
    std::cout << "two_to_one_fifth" << sfuns::two_to_one_fifth() << "\n";
    std::cout << "e^pi = " << sfuns::e_pow_pi() << "\n";
    std::cout << "e^i = " << std::pow(E,I) << "\n";
    std::cout << "pi^e = " << std::pow(PI,E) << "\n";
    std::cout << "pi^i = " << std::pow(PI,I) << "\n";
    std::cout << "e^i = " << std::pow(E,I) << "\n";
    std::cout << "i^i = " << std::pow(I,I) << "\n";
    std::cout << "ln(i) = " << std::log(I) << "\n";
    
// gamma function stuff

    for (int i = 1; i <= 10; ++i) {
        std::cout << "Γ(" << i << ") = " << sfuns::fgamma(i) << "\n";
    }

    for (int i = 1; i <= 10; ++i) {
        std::cout << "Γ(" << i << ") = " << sfuns::lngamma(i) << "\n";
    }

}