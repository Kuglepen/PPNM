#include "problems.h"
#include <cmath>

namespace pp {

std::function<vector(double, vector)> oscillator(double b, double c){
    return [=](double /*x*/, vector y){
        vector dydx(2);
        dydx[0] = y[1];
        dydx[1] = -b*y[1] - c*std::sin(y[0]);
        return dydx;
    };
}

std::function<vector(double, vector)> orbit(double eps){
    return [=](double /*phi*/, vector y){
        vector dydx(2);
        dydx[0] = y[1];
        dydx[1] = 1 - y[0] + eps*y[0]*y[0];
        return dydx;
    };
}

}