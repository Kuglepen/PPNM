#include <iostream>
#include <cmath>
#include <fstream>
#include "integrator.h"
#include <limits>

int calls = 0;

auto f2_count = [](double x){
    ++calls;
    return 1/std::sqrt(x);
};

auto f4_count = [](double x){
    ++calls;
    return std::log(x)/std::sqrt(x);
};

auto f_exp_count = [](double x){
    ++calls;
    return std::exp(-x);
};

auto f_gauss_count = [](double x){
    ++calls;
    return std::exp(-x*x);
};

double erf_my(double z, double acc){

    if(z < 0)
        return -erf_my(-z, acc);

    if(z <= 1){
        auto f = [](double x){
            return std::exp(-x*x);
        };
        return 2/std::sqrt(M_PI) * integrate(f, 0, z, acc, 0);
    }
    else{
        auto f = [z](double t){
            double x = z + (1 - t)/t;
            return std::exp(-x*x)/(t*t);
        };
        return 1 - 2/std::sqrt(M_PI) * integrate(f, 0, 1, acc, 0);
    }
}

int main(){

// A

    auto f1 = [](double x){ return std::sqrt(x); };
    auto f2 = [](double x){ return 1/std::sqrt(x); };
    auto f3 = [](double x){ return std::sqrt(1-x*x); };
    auto f4 = [](double x){ return std::log(x)/std::sqrt(x); };

    std::cout << "sqrt(x):        " << integrate(f1,0,1) << " (exact 2/3)\n";
    std::cout << "1/sqrt(x):      " << integrate(f2,0,1) << " (exact 2)\n";
    std::cout << "sqrt(1-x^2):    " << integrate(f3,0,1) << " (exact pi/2)\n";
    std::cout << "log(x)/sqrt(x): " << integrate(f4,0,1) << " (exact -4)\n";

    double exact = 0.8427007929497148;
    std::cout << "erf(1) ≈ " << erf_my(1, 1e-6)
              << " (exact " << exact << ")\n";

    std::ofstream out("erf_error.dat");

    for(double acc = 1e-1; acc >= 1e-8; acc *= 0.1){
        double val = erf_my(1.0, acc);
        double err = std::abs(val - exact);

        out << acc << " " << err << "\n";
    }

    out.close();

// B

    calls = 0;
    double I2 = integrate(f2_count,0,1);
    int calls_normal = calls;

    calls = 0;
    double I2_CC = integrate_cc(f2_count,0,1);
    int calls_cc = calls;

    std::cout << "\nIntegral 1/sqrt(x):\n";
    std::cout << "  normal = " << I2 << ", calls = " << calls_normal << "\n";
    std::cout << "  CC     = " << I2_CC << ", calls = " << calls_cc << "\n";

    calls = 0;
    double I4 = integrate(f4_count,0,1);
    calls_normal = calls;

    calls = 0;
    double I4_CC = integrate_cc(f4_count,0,1);
    calls_cc = calls;

    std::cout << "\nIntegral log(x)/sqrt(x):\n";
    std::cout << "  normal = " << I4 << ", calls = " << calls_normal << "\n";
    std::cout << "  CC     = " << I4_CC << ", calls = " << calls_cc << "\n";

    std::cout << "\nInfinite interval tests:\n";

    // exp(-x)
    calls = 0;
    double Iexp = integrate_inf(f_exp_count, 0,
        std::numeric_limits<double>::infinity(), 1e-6, 1e-6);

    int calls_exp = calls;

    std::cout << "exp(-x) from 0 to ∞ = " << Iexp
            << " (exact 1), calls = " << calls_exp << "\n";

    // Gaussian
    calls = 0;
    double Igauss = integrate_inf(f_gauss_count,
        -std::numeric_limits<double>::infinity(),
        std::numeric_limits<double>::infinity(), 1e-6, 1e-6);

    int calls_gauss = calls;

    std::cout << "exp(-x^2) from -∞ to ∞ = " << Igauss
            << " (exact " << std::sqrt(M_PI)
            << "), calls = " << calls_gauss << "\n";

    return 0;
}