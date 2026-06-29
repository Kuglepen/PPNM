#include "quasi_newton.h"
#include <cmath>
#include <limits>
#include <algorithm>

namespace pp {

namespace {

struct Update {
    vector u;
    double denom;
};

vector apply_inverse_hessian(const vector& v, const std::vector<Update>& hist) {
    // B v = v + sum_k u_k * (u_k^T v)/(u_k^T y_k)
    vector r = v;

    for(const auto& up : hist) {
        if(std::abs(up.denom) <= 0.0 || !std::isfinite(up.denom)) continue;
        double coeff = dot(up.u, v) / up.denom;
        r += up.u * coeff;
    }

    return r;
}

} // namespace

vector numerical_gradient(const Objective& f, const vector& x) {
    vector g(x.size());
    double fx = f(x);

    const double h0 = std::sqrt(std::numeric_limits<double>::epsilon());

    for(int i = 0; i < x.size(); i++) {
        double h = (1.0 + std::abs(x[i])) * h0;

        vector xp = x;
        xp[i] += h;

        g[i] = (f(xp) - fx) / h;
    }

    return g;
}

Result quasi_newton_minimize(
    const Objective& f,
    const vector& x0,
    int m,
    double acc,
    int max_iter,
    double alpha_min,
    double armijo_c1
) {
    Result res;
    res.x = x0;
    // Low memory storage:
    // only the last m SR1 update vectors are kept.
    // No inverse Hessian matrix is stored explicitly.
    std::vector<Update> hist;
    hist.reserve(m);

    double fx = f(res.x);
    vector g = numerical_gradient(f, res.x);

    for(int iter = 0; iter < max_iter; ++iter) {
        res.steps = iter;
        res.fx = fx;
        res.grad_norm = g.norm();
        if(res.grad_norm < acc) {
            res.converged = true;
            return res;
        }

        // Search direction: p = -B g
        vector Bg = apply_inverse_hessian(g, hist);
        vector p = -Bg;

        double gtp = dot(g, p);

        // If the direction is not downhill, reset the memory and fall back to steepest descent
        if(!std::isfinite(gtp) || gtp >= 0.0) {
            hist.clear();
            p = -g;
            gtp = dot(g, p);
        }

        double lambda = 1.0;
        vector x_new = res.x;
        double f_new = fx;

        bool hit_min_lambda = false;

        while(true) {
            x_new = res.x + lambda * p;
            f_new = f(x_new);

            if(f_new < fx + armijo_c1 * lambda * gtp)
                break;

            if(lambda <= alpha_min) {
                hit_min_lambda = true;
                break;
            }

            lambda *= 0.5;
        }

        vector g_new = numerical_gradient(f, x_new);

        // rank-1 update vector
        vector s = x_new - res.x;
        vector y = g_new - g;

        vector By = apply_inverse_hessian(y, hist);
        vector u = s - By;
        double denom = dot(u, y);

        if(hit_min_lambda) {
            // As in the notes: if the line search hits the minimum lambda,
            // reset the approximate inverse Hessian memory.
            hist.clear();
        } else {
            double scale = u.norm() * y.norm();
            if(std::isfinite(denom) && std::abs(denom) > 1e-6 * scale) {
                hist.push_back(Update{u, denom});
                // discard oldest update
                if((int)hist.size() > m)
                    hist.erase(hist.begin());
            }
        }

        res.x = x_new;
        fx = f_new;
        g = g_new;
    }

    res.steps = max_iter;
    res.fx = fx;
    res.grad_norm = g.norm();
    res.converged = false;
    return res;
}

}