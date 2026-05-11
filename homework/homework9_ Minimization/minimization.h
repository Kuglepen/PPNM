#pragma once
#include <functional>
#include <utility>
#include "matrix.h"

namespace pp {

using pp::vector;
using pp::matrix;

// FORWARD DIFFERENCE
vector gradient(std::function<double(vector)> phi, vector x);

matrix hessian(std::function<double(vector)> phi, vector x);

std::pair<vector,int> newton_minimize(
    std::function<double(vector)> phi,
    vector x0,
    double acc = 1e-3,
    int max_iter = 1000,
    double alpha_min = 1.0/1024.0
);

// CENTRAL DIFFERENCE
vector gradient_central(
    std::function<double(vector)> phi,
    vector x
);

matrix hessian_central(
    std::function<double(vector)> phi,
    vector x
);

std::pair<vector,int> newton_minimize_central(
    std::function<double(vector)> phi,
    vector x0,
    double acc = 1e-3,
    int max_iter = 1000,
    double alpha_min = 1.0/1024.0
);

} // namespace pp