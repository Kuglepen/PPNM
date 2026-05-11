#include "rk.h"
#include <cmath>
#include <algorithm>

namespace pp {

std::tuple<vector, vector> rkstep12(
    std::function<vector(double, vector)> f,
    double x,
    vector y,
    double h
){
    vector k0 = f(x, y);
    vector k1 = f(x + h/2, y + k0*(h/2));

    vector yh = y + k1*h;
    vector dy = (k1 - k0)*h;

    return std::make_tuple(yh, dy);
}

std::tuple<std::vector<double>, std::vector<vector>> driver(
    std::function<vector(double, vector)> f,
    double a,
    double b,
    vector yinit,
    double h,
    double acc,
    double eps
){
    double x = a;
    vector y = yinit;

    std::vector<double> xlist;
    std::vector<vector> ylist;

    xlist.push_back(x);
    ylist.push_back(y);

    while(true){
        if(x >= b) break;

        if(x + h > b) h = b - x;

        auto [yh, dy] = rkstep12(f, x, y, h);

        double tol = (acc + eps * yh.norm()) * std::sqrt(h/(b-a));
        double err = dy.norm();

        if(err <= tol){
            x += h;
            y = yh;
            xlist.push_back(x);
            ylist.push_back(y);
        }

        if(err > 0){
            h *= std::min(std::pow(tol/err, 0.25)*0.95, 2.0);
        } else {
            h *= 2;
        }
        double hmax = 0.05;
        h = std::min(h, hmax);
    }

    return std::make_tuple(xlist, ylist);
}

} // namespace pp