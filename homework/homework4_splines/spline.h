#pragma once
#include <vector>

int binsearch(const std::vector<double>& x, double z);

double linterp(const std::vector<double>& x,
               const std::vector<double>& y,
               double z);

double linterpInteg(const std::vector<double>& x,
                    const std::vector<double>& y,
                    double z);

struct qspline {
    std::vector<double> x,y;
    int n;
    std::vector<double> b,c;

    qspline(const std::vector<double>& x,
            const std::vector<double>& y);

    double eval(double z);
    double deriv(double z);
    double integ(double z);
};

#include <functional>

std::function<double(double)>
make_qspline(std::vector<double> x,
             std::vector<double> y);