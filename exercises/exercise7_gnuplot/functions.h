#pragma once
#include <vector>
#include <utility>
#include <string>
#include <complex>

namespace functions {

    double erf(double x);
    double sgamma(double x);
    double lngamma(double x);

    std::vector<std::pair<double,double>> load_data(const std::string& filename);
    std::complex<double> cgamma(std::complex<double> z);

}
