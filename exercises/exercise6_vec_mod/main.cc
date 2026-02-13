#include "vec.h"
#include <iostream>
#include <complex>
#include <iomanip>

int main(){
    using namespace vec_funs;

    // 1. Different numeric types (float vs double)
    std::cout << std::setprecision(10);

    vec<double> a(1.123456789, 2.123456789, 3.123456789);
    vec<float>  b(1.123456789f, 2.123456789f, 3.123456789f);
    std::cout << "double vec: " << a << "\n";
    std::cout << "float  vec: " << b << "\n";

    // 2. Mixed scalar types (int with double)
    std::cout << "2 * a = " << 2 * a << " (int * vec<double>)\n";

    // 3. Complex numbers
    using cd = std::complex<double>;
    vec<cd> c(cd(1,1), cd(2,0), cd(0,3));
    std::cout << "complex vec: " << c << "\n";

    // 4. Generic approx works for any type
    vec<double> d(1.123456788,2.123456788,3.123456788);
    std::cout << "a = " << a << "\n";
    std::cout << "d = " << d << "\n";
    if(approx(a,d)){
        std::cout << "approx works for vec<double>\n";
    }

    return 0;
}