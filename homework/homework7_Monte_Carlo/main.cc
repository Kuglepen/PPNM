#include <iostream>
#include <fstream>
#include <cmath>
#include "lcg.h"
#include <random>

using pp::vector;

int main(){

    // UNIT CIRCLE
    auto circle = [](vector x){
        return (x[0]*x[0] + x[1]*x[1] <= 1.0) ? 1.0 : 0.0;
    };

    vector a = {-1.0, -1.0};
    vector b = { 1.0,  1.0};

    double exact = M_PI;

    lcg rng(12345);

    std::ofstream dataA("mc_plain.dat");
    std::ofstream out("out.txt");

    dataA << "# N estimated actual\n";

    int Ns[] = {1,10,100,1000,10000,100000,1000000};

    for(int N : Ns){

        auto [I, err] = plainmc(circle, a, b, N, rng);
        double actual = std::abs(I - exact);

        dataA << N << " " << err << " " << actual << "\n";

        out << "Estimated area of unit circle: "
            << I << " ± " << err
            << " with sample size: " << N << "\n";
    }

    // ELLIPSOID
    auto ellipsoid = [](vector x){
        double val =
            x[0]*x[0]/(1*1) +
            x[1]*x[1]/(2*2) +
            x[2]*x[2]/(3*3);

        return (val <= 1.0) ? 1.0 : 0.0;
    };

    vector a3 = {-1,-2,-3};
    vector b3 = { 1, 2, 3};

    int N = 1000000;

    auto [V, errV] = plainmc(ellipsoid, a3, b3, N, rng);

    double exactV = 4.0/3.0 * M_PI * 1 * 2 * 3;

    out << "\nEstimated volume of the ellipsoid: "
        << V << " ± " << errV << "\n";

    out << "Actual volume of the ellipsoid: "
        << exactV << "\n";
    
    std::ofstream dataB("mc_quasi.dat");

    dataB << "# N lcg mt quasi actual_lcg actual_mt actual_quasi\n";

    int Ns2[] = {10,100,1000,10000,100000};

    for(int N : Ns2){

        // reset LCG each time (important!)
        lcg rng_lcg(12345);

        auto [I_lcg, err_lcg] = plainmc(circle, a, b, N, rng_lcg);

        // standard C++ RNG
        std::mt19937_64 gen(12345);
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        auto rng_mt = [&]() { return dist(gen); };

        auto [I_mt, err_mt] = plainmc(circle, a, b, N, rng_mt);

        // quasi-random
        auto [I_quasi, err_quasi] = quasimc(circle, a, b, N);

        double actual_lcg   = std::abs(I_lcg - exact);
        double actual_mt    = std::abs(I_mt - exact);
        double actual_quasi = std::abs(I_quasi - exact);

        dataB << N << " "
            << err_lcg << " "
            << err_mt << " "
            << err_quasi << " "
            << actual_lcg << " "
            << actual_mt << " "
            << actual_quasi << "\n";
    }

    dataB.close();
    dataA.close();
    out.close();

    return 0;
}