#include "ann.h"
#include <cmath>
#include <cassert>

namespace pp {

ann::ann(int n)
    : n(n),
      f([](double z) {
          return z * std::exp(-z * z);
      }),
      p(3 * n)
{
    for (int i = 0; i < n; i++) {
        p[i] = -1.0 + 2.0 * i / (n - 1.0);  // a_i
        p[n + i] = 1.0;                     // b_i
        p[2 * n + i] = 1.0;                 // w_i
    }
}

double ann::safe_b(double b) {
    const double eps = 1e-6;
    if (std::abs(b) < eps) {
        return (b < 0 ? -eps : eps);
    }
    return b;
}

double ann::phi(double z) {
    return z * std::exp(-z * z);
}

double ann::dphi(double z) {
    return std::exp(-z * z) * (1.0 - 2.0 * z * z);
}

double ann::ddphi(double z) {
    return 2.0 * z * std::exp(-z * z) * (2.0 * z * z - 3.0);
}

double ann::intphi(double z) {
    return -0.5 * std::exp(-z * z);
}

double ann::response(const vector& u, double x) const {
    assert(u.size() == 3 * n);

    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        double ai = u[i];
        double bi = safe_b(u[n + i]);
        double wi = u[2 * n + i];

        double z = (x - ai) / bi;
        sum += wi * phi(z);
    }
    return sum;
}

double ann::response(double x) const {
    return response(p, x);
}

double ann::response1(double x) const {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        double ai = p[i];
        double bi = safe_b(p[n + i]);
        double wi = p[2 * n + i];

        double z = (x - ai) / bi;
        sum += wi * dphi(z) / bi;
    }
    return sum;
}

double ann::response2(double x) const {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        double ai = p[i];
        double bi = safe_b(p[n + i]);
        double wi = p[2 * n + i];

        double z = (x - ai) / bi;
        sum += wi * ddphi(z) / (bi * bi);
    }
    return sum;
}

double ann::antiderivative(double x) const {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        double ai = p[i];
        double bi = safe_b(p[n + i]);
        double wi = p[2 * n + i];

        double z = (x - ai) / bi;
        sum += wi * bi * intphi(z);
    }
    return sum;
}

void ann::train(const vector& xs, const vector& ys) {
    assert(xs.size() == ys.size());
    assert(xs.size() > 0);

    const int N = xs.size();
    const int m = 3 * n;

    auto cost = [&](const vector& u) {
        double sum = 0.0;
        for (int k = 0; k < N; k++) {
            double r = response(u, xs[k]) - ys[k];
            sum += r * r;
        }
        return sum / N;
    };

    auto gradient = [&](const vector& u) {
        vector g(m);
        for (int i = 0; i < m; i++) g[i] = 0.0;

        for (int k = 0; k < N; k++) {
            double x = xs[k];
            double y = ys[k];
            double r = response(u, x) - y;

            for (int i = 0; i < n; i++) {
                double ai = u[i];
                double bi = safe_b(u[n + i]);
                double wi = u[2 * n + i];

                double z = (x - ai) / bi;
                double phi_z = phi(z);
                double dphi_z = dphi(z);

                g[i]         += (2.0 / N) * r * wi * dphi_z * (-1.0 / bi);
                g[n + i]     += (2.0 / N) * r * wi * dphi_z * (-(x - ai) / (bi * bi));
                g[2 * n + i] += (2.0 / N) * r * phi_z;
            }
        }

        return g;
    };

    double best = cost(p);

    for (int iter = 0; iter < 5000; iter++) {
        vector g = gradient(p);

        if (g.norm() < 1e-6) break;

        vector direction = -g;
        double step = 1.0;
        bool improved = false;

        while (step > 1e-8) {
            vector trial = p + step * direction;

            for (int i = 0; i < n; i++) {
                if (std::abs(trial[n + i]) < 1e-3) {
                    trial[n + i] = (trial[n + i] < 0 ? -1e-3 : 1e-3);
                }
            }

            double c = cost(trial);
            if (c < best) {
                p = trial;
                best = c;
                improved = true;
                break;
            }

            step *= 0.5;
        }

        if (!improved) break;
    }
}

} // namespace pp