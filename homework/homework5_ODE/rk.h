#pragma once
#include <functional>
#include <tuple>
#include <vector>
#include "matrix.h"

namespace pp {

std::tuple<vector, vector> rkstep12(
    std::function<vector(double, vector)> f,
    double x,
    vector y,
    double h
);

std::tuple<std::vector<double>, std::vector<vector>> driver(
    std::function<vector(double, vector)> f,
    double a,
    double b,
    vector yinit,
    double h = 0.125,
    double acc = 0.01,
    double eps = 0.01
);

}