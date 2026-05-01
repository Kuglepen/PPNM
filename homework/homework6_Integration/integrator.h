#pragma once
#include <functional>
#include <cmath>

double integrate(
    std::function<double(double)> f,
    double a,
    double b,
    double acc = 1e-3,
    double eps = 1e-3,
    double f2 = NAN,
    double f3 = NAN
);

double integrate_cc(
    std::function<double(double)> f,
    double a,
    double b,
    double acc = 1e-3,
    double eps = 1e-3
);

double integrate_inf(
    std::function<double(double)> f,
    double a,
    double b,
    double acc = 1e-3,
    double eps = 1e-3
);