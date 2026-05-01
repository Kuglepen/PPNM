#include "integrator.h"
#include <cmath>
#include <algorithm>
#include <limits>

double integrate(
    std::function<double(double)> f,
    double a,
    double b,
    double acc,
    double eps,
    double f2,
    double f3
){
    double h = b - a;

    if (std::isnan(f2)) {
        f2 = f(a + 2*h/6);
        f3 = f(a + 4*h/6);
    }

    double f1 = f(a + h/6);
    double f4 = f(a + 5*h/6);

    double Q = (2*f1 + f2 + f3 + 2*f4)/6 * h; // higher order
    double q = (  f1 + f2 + f3 +   f4)/4 * h; // lower order

    double err = std::abs(Q - q);
    double tol = acc + eps * std::abs(Q);

    if (err < tol) return Q;

    double mid = (a + b)/2;

    return integrate(f, a, mid, acc/std::sqrt(2), eps, f1, f2)
         + integrate(f, mid, b, acc/std::sqrt(2), eps, f3, f4);
}

double integrate_cc(
    std::function<double(double)> f,
    double a,
    double b,
    double acc,
    double eps
){
    auto g = [f,a,b](double theta){
        double x = (a+b)/2 + (b-a)/2 * std::cos(theta);
        return f(x) * std::sin(theta) * (b-a)/2;
    };

    return integrate(g, 0, M_PI, acc, eps);
}

double integrate_inf(
    std::function<double(double)> f,
    double a,
    double b,
    double acc,
    double eps
){
    // (-∞, ∞)
    if(std::isinf(a) && std::isinf(b)){
        auto g = [f](double t){
            double x = t/(1 - t*t);
            double dxdt = (1 + t*t)/((1 - t*t)*(1 - t*t));
            return f(x)*dxdt;
        };
        return integrate_cc(g, -1, 1, acc, eps);
    }

    // (a, ∞)
    if(std::isinf(b)){
        auto g = [f,a](double t){
            double x = a + t/(1 - t);
            double dxdt = 1/((1 - t)*(1 - t));
            return f(x)*dxdt;
        };
        return integrate_cc(g, 0, 1, acc, eps);
    }

    // (-∞, b)
    if(std::isinf(a)){
        auto g = [f,b](double t){
            double x = b - t/(1 - t);
            double dxdt = 1/((1 - t)*(1 - t));
            return f(x)*dxdt;
        };
        return integrate_cc(g, 0, 1, acc, eps);
    }

    // fallback
    return integrate_cc(f, a, b, acc, eps);
}