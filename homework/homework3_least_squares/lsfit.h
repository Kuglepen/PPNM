#pragma once
#include "matrix.h"
#include <vector>
#include <functional>
#include <tuple>

namespace pp {
    std::tuple<vector,matrix> lsfit(
        const std::vector<std::function<double(double)>>& fs,
        const vector& x,
        const vector& y,
        const vector& dy
    );
}