#pragma once
#include <functional>
#include <utility>
#include <cmath>
#include <algorithm>
#include "matrix.h"

using pp::vector;

// RNG
struct lcg {
    unsigned long long seed;
    unsigned long long a = 1664525;
    unsigned long long c = 1013904223;
    unsigned long long m = 1ULL << 32;

    lcg(unsigned long long s);

    double operator()();
};

// Monte Carlo
template<typename RNG>
std::pair<double,double> plainmc(
    std::function<double(vector)> f,
    vector a,
    vector b,
    int N,
    RNG& rng
){
    int dim = a.size();
    double V = 1.0;

    for(int i=0;i<dim;i++)
        V *= (b[i] - a[i]);

    double sum = 0.0;
    double sum2 = 0.0;

    vector x(dim);

    for(int i=0;i<N;i++){
        for(int k=0;k<dim;k++)
            x[k] = a[k] + rng()*(b[k] - a[k]);

        double fx = f(x);
        sum += fx;
        sum2 += fx*fx;
    }

    double mean = sum/N;
    double variance = std::max(0.0, sum2/N - mean*mean);
    double sigma = std::sqrt(variance);

    return {mean*V, sigma*V/std::sqrt(N)};
}

// Quasi-MC
double van_der_corput(int n, int base);

pp::vector primes(int n);

std::pair<double,double> quasimc(
    std::function<double(pp::vector)> f,
    pp::vector a,
    pp::vector b,
    int N
);