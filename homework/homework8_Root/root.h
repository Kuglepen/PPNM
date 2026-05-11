#pragma once
#include <functional>
#include "matrix.h"

using pp::vector;
using pp::matrix;

// Jacobian (numerical)
matrix Jacobian(
    std::function<vector(vector)> f,
    vector x,
    vector fx
);

// Newton method
vector newton(
    std::function<vector(vector)> f,
    vector x,
    double acc = 1e-6,
    double alpha_min = 1e-3,
    int max_iter = 100
);