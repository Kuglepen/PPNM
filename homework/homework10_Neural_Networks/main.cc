#include <iostream>
#include <fstream>
#include <cmath>
#include "ann.h"

int main() {
    const int N = 25;

    pp::vector xs(N);
    pp::vector ys(N);

    for (int i = 0; i < N; i++) {
        double x = -1.0 + 2.0 * i / (N - 1.0);

        xs[i] = x;
        ys[i] = std::cos(5 * x - 1) * std::exp(-x * x);
    }

    pp::ann network(10);
    network.train(xs, ys);

    // original training data
    std::ofstream data("data.txt");

    for (int i = 0; i < N; i++) {
        data << xs[i] << " "
             << ys[i] << "\n";
    }

    // ANN curves
    std::ofstream fit("fit.txt");

    for (double x = -1.0; x <= 1.0; x += 0.005) {

        fit << x << " "
            << network.response(x) << " "
            << network.response1(x) << " "
            << network.response2(x) << " "
            << network.antiderivative(x)
            << "\n";
    }

    return 0;
}