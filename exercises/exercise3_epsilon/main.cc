#include<iostream>
#include<cmath>
#include"sfuns.h"
#include<limits>
#include<iomanip>


int main() {

//Machine epsilon

    float f = 1.0f;
    while ((float)(1.0f + f) != 1.0f) {
        f /= 2.0f;
    }
    f *= 2.0f;

    double d = 1.0;
    while ((double)(1.0 + d) != 1.0) {
        d /= 2.0;
    }
    d *= 2.0;

    long double l = 1.0L;
    while ((long double)(1.0L + l) != 1.0L) {
        l /= 2.0L;
    }
    l *= 2.0L;

    std::cout << "\nComputed epsilons:\n";
    std::cout << "float       eps = " << f << "\n";
    std::cout << "double      eps = " << d << "\n";
    std::cout << "long double eps = " << l << "\n";

    // From <limits>
    std::cout << "\nSystem epsilons (<limits>):\n";
    std::cout << "float       eps = " << std::numeric_limits<float>::epsilon() << "\n";
    std::cout << "double      eps = " << std::numeric_limits<double>::epsilon() << "\n";
    std::cout << "long double eps = " << std::numeric_limits<long double>::epsilon() << "\n";

    //powers of 2
    std::cout << "\nAs powers of two:\n";
    std::cout << "float       = 2^" << std::log2(f) << "\n";
    std::cout << "double      = 2^" << std::log2(d) << "\n";
    std::cout << "long double = 2^" << std::log2(l) << "\n";


//Non-commutativity of addition

    std::cout << "\nNon-commutativity of addition:\n";

    double epsilon=std::pow(2,-52);
    double tiny=epsilon/2;
    double a=1+tiny+tiny;
    double b=tiny+tiny+1;

    std::cout << "a==b ? " << (a==b ? "true":"false") << "\n";
    std::cout << "a>1  ? " << (a>1  ? "true":"false") << "\n";
    std::cout << "b>1  ? " << (b>1  ? "true":"false") << "\n";

    std::cout << std::fixed << std::setprecision(17);
    std::cout << "       tiny=" << tiny << "\n";
    std::cout << "1+tiny+tiny=" << a << "\n";
    std::cout << "tiny+tiny+1=" << b << "\n";

//Comparing doubles: introduction

    std::cout << "\nComparing doubles:\n";

    double d1 = 0.1+0.1+0.1+0.1+0.1+0.1+0.1+0.1;
    double d2 = 8*0.1;

    std::cout << std::fixed << std::setprecision(17);
    std::cout << "d1 = " << d1 << "\n";
    std::cout << "d2 = " << d2 << "\n";
    std::cout << "d1==d2 ? " << (d1==d2 ? "true":"false") << "\n";

//Comparing doubles: the task

    std::cout << "\nApproximate comparison:\n";
    std::cout << "approx(d1,d2) ? "
            << (sfuns::approx(d1, d2) ? "true" : "false") << "\n";


}