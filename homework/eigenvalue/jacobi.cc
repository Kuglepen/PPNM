#include "jacobi.h"
#include <cmath>
#include <limits>

namespace pp {

void timesJ(matrix& A, int p, int q, double theta) {
    double c = std::cos(theta), s = std::sin(theta);
    for(int i = 0; i < A.size1(); ++i) {
        double aip = A(i, p), aiq = A(i, q);
        A(i, p) = c * aip - s * aiq;
        A(i, q) = s * aip + c * aiq;
    }
}

void Jtimes(matrix& A, int p, int q, double theta) {
    double c = std::cos(theta), s = std::sin(theta);
    for(int j = 0; j < A.size1(); ++j) {
        double apj = A(p, j), aqj = A(q, j);
        A(p, j) =  c * apj + s * aqj;
        A(q, j) = -s * apj + c * aqj;
    }
}

std::tuple<vector, matrix> jacobi(matrix A) {
    int n = A.size1();
    matrix V(n, n);
    V.setid();
    vector w(n);

    const double tol = 1e-12;
    bool changed;
    int max_sweeps = 1000; // safety cap to avoid infinite loops
    int sweep = 0;

    do {
        changed = false;
        ++sweep;
        for(int p = 0; p < n-1; ++p) {
            for(int q = p+1; q < n; ++q) {
                double apq = A(p, q), app = A(p, p), aqq = A(q, q);

                // If apq is already tiny skip the rotation — small speedup & stability
                if (std::abs(apq) < 1e-16 * (std::abs(app) + std::abs(aqq) + 1.0)) continue;

                double theta = 0.5 * std::atan2(2.0*apq, aqq - app);
                double c = std::cos(theta), s = std::sin(theta);

                double new_app = c*c*app - 2*s*c*apq + s*s*aqq;
                double new_aqq = s*s*app + 2*s*c*apq + c*c*aqq;

                if(std::abs(new_app - app) > tol || std::abs(new_aqq - aqq) > tol) {
                    changed = true;
                    timesJ(A, p, q, theta);      // A ← A * J
                    Jtimes(A, p, q, -theta);     // A ← J^T * A
                    timesJ(V, p, q, theta);      // V ← V * J
                }
            }
        }
        if(sweep > max_sweeps) break;
    } while(changed);

    for(int i = 0; i < n; ++i) w[i] = A(i, i);
    return std::make_tuple(w, V);
}

} // namespace pp