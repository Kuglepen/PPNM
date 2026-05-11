#include <iostream>
#include <fstream>
#include <cmath>
#include <functional>
#include <stdexcept>
#include <vector>
#include "root.h"
#include "rk.h"

using pp::vector;

struct HydrogenParams {
    double rmin;
    double rmax;
    double h;
    double acc;
    double eps;
};

std::function<vector(double, vector)> hydrogen_rhs(double E){
    return [E](double r, vector y){
        vector dydr(2);
        dydr[0] = y[1];
        dydr[1] = -2.0 * (E + 1.0/r) * y[0];
        return dydr;
    };
}

// Near r=0 the regular solution behaves as
//
//     f(r) ~ r - r^2
//
// This is found by inserting
//
//     f(r) = a r + b r^2 + ...
//
// into the radial Schrödinger equation.
// One gets b = -a, and choosing a = 1 gives
//
//     f(r) ~ r - r^2
//
// Therefore we start the integration at rmin with
//
//     f(rmin) = rmin - rmin^2
//     f'(rmin) = 1 - 2 rmin

std::pair<std::vector<double>, std::vector<vector>> solve_hydrogen(
    double E,
    const HydrogenParams& p
){
    auto F = hydrogen_rhs(E);

    vector y0 = {
        p.rmin - p.rmin*p.rmin,
        1.0 - 2.0*p.rmin
    };

    return driver(F, p.rmin, p.rmax, y0, p.h, p.acc, p.eps);
}

double M_of_E(double E, const HydrogenParams& p){
    auto [r, y] = solve_hydrogen(E, p);
    return y.back()[0];
}

double bisect(
    std::function<double(double)> f,
    double a,
    double b,
    double tol = 1e-10
){
    double fa = f(a);
    double fb = f(b);

    if(fa * fb > 0.0)
        throw std::runtime_error("bisection: root is not bracketed");

    while(std::abs(b - a) > tol){
        double c = 0.5 * (a + b);
        double fc = f(c);

        if(fa * fc <= 0.0){
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }
    }

    return 0.5 * (a + b);
}

std::pair<double,double> bracket_root(
    std::function<double(double)> f,
    double x0,
    double dx = 0.05,
    int max_expand = 20
){
    double a = x0 - dx;
    double b = x0 + dx;
    double fa = f(a);
    double fb = f(b);

    for(int i = 0; i < max_expand; i++){
        if(fa * fb <= 0.0)
            return {a, b};

        dx *= 2.0;
        a = x0 - dx;
        b = x0 + dx;
        fa = f(a);
        fb = f(b);
    }

    throw std::runtime_error("Could not bracket the ground-state root");
}

double find_ground_state_energy(const HydrogenParams& p){
    auto M = [&](double E){
        return M_of_E(E, p);
    };

    auto [a, b] = bracket_root(M, -0.5, 0.05);
    return bisect(M, a, b, 1e-10);
}

void write_wavefunction(const std::string& filename, const HydrogenParams& p){
    double E0 = find_ground_state_energy(p);
    auto [r, y] = solve_hydrogen(E0, p);

    std::ofstream out(filename);
    out << "# r numerical exact\n";

    for(size_t i = 0; i < r.size(); i++){
        double exact = r[i] * std::exp(-r[i]);
        out << r[i] << " " << y[i][0] << " " << exact << "\n";
    }
}

void write_wavefunction_sweep(
    const std::string& filename,
    const HydrogenParams& base,
    const std::vector<double>& values,
    int mode
){
    std::ofstream out(filename);

    for(double v : values){
        HydrogenParams p = base;

        if(mode == 0) p.rmin = v;
        if(mode == 1) p.rmax = v;
        if(mode == 2) p.acc  = v;
        if(mode == 3) p.eps  = v;

        double E0 = find_ground_state_energy(p);
        auto [r, y] = solve_hydrogen(E0, p);

        out << "# parameter = " << v << "\n";
        for(size_t i = 0; i < r.size(); i++){
            double exact = r[i] * std::exp(-r[i]);
            out << r[i] << " " << y[i][0] << " " << exact << "\n";
        }
        out << "\n\n";
    }
}

int main(){

    std::cout << "PART A: Newton\n";

    auto f1 = [](vector x){
        vector r(1);
        r[0] = x[0]*x[0] - 2;
        return r;
    };

    vector x1 = {1.0};
    vector root1 = newton(f1, x1);
    root1.print("sqrt(2) ≈ ");

    auto f2 = [](vector x){
        vector r(2);
        r[0] = x[0]*x[0] + x[1]*x[1] - 1;
        r[1] = x[0] - x[1];
        return r;
    };

    vector x2 = {0.5, 0.5};
    vector root2 = newton(f2, x2);
    root2.print("2D test root ≈ ");

    auto rosen_grad = [](vector x){
        vector g(2);
        double X = x[0];
        double Y = x[1];
        g[0] = -2*(1 - X) - 400*X*(Y - X*X);
        g[1] = 200*(Y - X*X);
        return g;
    };

    vector xr = {-1, 2};
    vector rosen_root = newton(rosen_grad, xr);
    rosen_root.print("Rosenbrock minimum ≈ ");

    auto himmel_grad = [](vector x){
        vector g(2);
        double X = x[0];
        double Y = x[1];
        g[0] = 4*X*(X*X + Y - 11) + 2*(X + Y*Y - 7);
        g[1] = 2*(X*X + Y - 11) + 4*Y*(X + Y*Y - 7);
        return g;
    };

    vector starts[] = {
        {3.1,2.1}, {-2.7,3}, {-3.7,-3.1}, {3.5,-1.8}
    };

    for(auto x0 : starts){
        vector root = newton(himmel_grad, x0);
        root.print("Himmelblau minimum ≈ ");
    }

    std::cout << "\nPART B: Hydrogen shooting\n";

    HydrogenParams base;
    base.rmin = 1e-4;
    base.rmax = 8.0;
    base.h   = 0.05;
    base.acc = 1e-6;
    base.eps = 1e-6;

    double E0 = find_ground_state_energy(base);

    std::cout << "Found ground-state energy E0 = " << E0 << "\n";
    std::cout << "Exact value                  = " << -0.5 << "\n";

    write_wavefunction("hydrogen.dat", base);

    std::ofstream out("out.txt");
    out << "Hydrogen ground state\n";
    out << "rmin = " << base.rmin << "\n";
    out << "rmax = " << base.rmax << "\n";
    out << "h    = " << base.h    << "\n";
    out << "acc  = " << base.acc  << "\n";
    out << "eps  = " << base.eps  << "\n\n";
    out << "Found E0 = " << E0 << "\n";
    out << "Exact E0 = -0.5\n";
    out << "Absolute error = " << std::abs(E0 + 0.5) << "\n";
    out.close();

    write_wavefunction_sweep("wave_rmin.dat", base,{1e-5, 0.1, 0.2, 0.4}, 0);
    write_wavefunction_sweep("wave_rmax.dat", base,{1.0, 3.0, 5.0, 10.0}, 1);
    write_wavefunction_sweep("wave_acc.dat", base,{10.0, 1.0, 1e-1, 1e-5}, 2);
    write_wavefunction_sweep("wave_eps.dat", base,{10.0, 1.0, 1e-1, 1e-5}, 3);

    return 0;
}