#pragma once
#include "matrix.h"
#include <functional>

namespace pp {

// harmonic / damped oscillator
std::function<vector(double, vector)> oscillator(double b, double c);

// relativistic orbit
std::function<vector(double, vector)> orbit(double eps);

}