#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "rk.h"
#include "problems.h"

using namespace pp;

int main(){

    // PART A: Damped Oscillator

    auto F = oscillator(0.25, 5.0);
    vector y0 = {M_PI - 0.1, 0.0};

    auto [xs, ys] = driver(F, 0.0, 10.0, y0);

    std::ofstream ode("ode.dat");
    for (size_t i = 0; i < xs.size(); i++)
        ode << xs[i] << " " << ys[i][0] << " " << ys[i][1] << "\n";


    // PART B: Relativistic Orbit

    std::ofstream orbitfile("orbit.dat");

    std::vector<double> epss    = {0.0, 0.0, 0.01};
    std::vector<double> uprimes = {0.0, -0.5, -0.5};

    for (size_t i = 0; i < epss.size(); i++){
        auto F = orbit(epss[i]);
        vector init = {1.0, uprimes[i]};

        auto [phi, u] = driver(F, 0.0, 8*M_PI, init, 0.01, 1e-6, 1e-6);

        orbitfile << "# eps=" << epss[i]
                  << " u'(0)=" << uprimes[i] << "\n";

        for (size_t j = 0; j < phi.size(); j++)
            orbitfile << phi[j] << " " << u[j][0] << "\n";

        orbitfile << "\n\n";
    }


    //  PART C: 3-body

    double a = 0;
    double b = 6.3259 / 3.0;

    vector y_init = {
        // positions
        0.97000436, -0.24308753,
        -0.97000436,  0.24308753,
        0.0,          0.0,

        // velocities
        0.4662036850,  0.4323657300,
        0.4662036850,  0.4323657300,
        -0.93240737,   -0.86473146
    };

    auto three_body = [](double /*t*/, vector y){
        vector dydt(12);

        // velocities → position derivatives
        for (int i = 0; i < 6; i++)
            dydt[i] = y[6 + i];

        // accelerations
        for (int i = 0; i < 3; i++){
            vector ri = {y[2*i], y[2*i+1]};
            vector ai(2);

            for (int j = 0; j < 3; j++){
                if (j == i) continue;

                vector rj = {y[2*j], y[2*j+1]};
                vector dr = rj - ri;
                double r = dr.norm();

                ai += dr / (r*r*r);
            }

            dydt[6 + 2*i]     = ai[0];
            dydt[6 + 2*i + 1] = ai[1];
        }

        return dydt;
    };

    auto [tx, ty] = driver(three_body, a, b, y_init, 0.001, 1e-6, 1e-6);

    std::ofstream three("threebody.dat");
    for (size_t i = 0; i < tx.size(); i++){
        three << tx[i];
        for (int j = 0; j < 12; j++)
            three << " " << ty[i][j];
        three << "\n";
    }

    return 0;
}