#pragma once
#include "matrix.h"
#include <functional>
#include <utility>
#include <vector>

namespace pp {

using Objective = std::function<double(const vector&)>;

vector numerical_gradient(const Objective& f, const vector& x);

struct Result {
    vector x;
    double fx = 0.0;
    double grad_norm = 0.0;
    int steps = 0;
    bool converged = false;
};

Result quasi_newton_minimize(
    const Objective& f,
    const vector& x0,
    int m = 5,
    double acc = 1e-6,
    int max_iter = 1000,
    double alpha_min = 1.0 / 1024.0,
    double armijo_c1 = 1e-4
);

}