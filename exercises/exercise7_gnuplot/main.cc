#include <iostream>
#include <fstream>
#include <vector>
#include "functions.h"

int main() {

    // 1 erf
    std::ofstream curve("erf_curve.dat");

    for (double x = 0.0; x <= 3.5; x += 0.01) {
        curve << x << " " << functions::erf(x) << "\n";
    }

    curve.close();

    // 2 gamma
    std::ofstream gamma_curve("gamma_curve.dat");

    for (double x = -5.0; x <= 5.0; x += 0.01) {

        if (std::abs(x - std::round(x)) < 1e-3) {
            gamma_curve << "\n"; // Add a blank line to indicate a discontinuity
            continue;
        }

        gamma_curve << x << " " << functions::sgamma(x) << "\n";
    }

    gamma_curve.close();

    // 3 lngamma
    std::ofstream lngamma_curve("lngamma_curve.dat");

    for (double x = 0.0; x <= 5.0; x += 0.01) {
        lngamma_curve << x << " " << functions::lngamma(x) << "\n";
    }

    lngamma_curve.close();

    // extra complex gamma

    std::ofstream out("gamma_complex.dat");

    for (double x = -4.0; x <= 4.0; x += 0.05) {
        for (double y = -4.0; y <= 4.0; y += 0.05) {

            std::complex<double> z(x, y);

            // skip poles on real axis (negative integers and zero)
            if (std::abs(y) < 1e-6 && x <= 0 && std::abs(x - std::round(x)) < 1e-3)
                continue;

            double val = std::abs(functions::cgamma(z));
            if (!std::isfinite(val)) continue;
            if (val > 6.0) val = 6.0;

            out << x << " " << y << " " << val << "\n";
        }
        out << "\n";
    }

    out.close();

    // Load data from erf_data.txt
    auto data = functions::load_data("erf_data.txt");

    std::ofstream points("erf_points.dat");

    for (const auto& [x, y] : data) {
        points << x << " " << y << "\n";
    }

    points.close();

    // load data from gammafn_data.txt
    auto gamma_data = functions::load_data("gammaf_data.txt");

    std::ofstream gamma_points("gamma_points.dat");

    for (const auto& [x, y] : gamma_data) {
        gamma_points << x << " " << y << "\n";
    }

    gamma_points.close();

    // load data from gammaf_data.txt (for ln Gamma)
    auto gamma_data_log = functions::load_data("gammaf_data.txt");

    std::ofstream lngamma_points("lngamma_points.dat");

    for (const auto& [x, y] : gamma_data_log) {
        lngamma_points << x << " " << std::log(y) << "\n";
    }

    lngamma_points.close();

    return 0;

}