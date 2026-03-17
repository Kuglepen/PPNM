#pragma once
#include "matrix.h"
#include <tuple>

namespace pp {
    void timesJ(matrix& A, int p, int q, double theta);
    void Jtimes(matrix& A, int p, int q, double theta);
    std::tuple<vector, matrix> jacobi(matrix A);   // A copied (by value)
}