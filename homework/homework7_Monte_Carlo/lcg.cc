#include "lcg.h"
#include <cmath>

// RNG implementation
lcg::lcg(unsigned long long s) : seed(s) {}

double lcg::operator()() {
    seed = (a * seed + c) % m;
    return double(seed) / double(m);
}

double van_der_corput(int n, int base){
    double x = 0;
    double denom = 1;

    while(n > 0){
        denom *= base;
        x += (n % base) / denom;
        n /= base;
    }

    return x;
}

pp::vector primes(int n){
    pp::vector p(n);
    int count = 0;
    int candidate = 2;

    while(count < n){
        bool is_prime = true;

        for(int i=0;i<count;i++){
            if(candidate % (int)p[i] == 0){
                is_prime = false;
                break;
            }
        }

        if(is_prime){
            p[count] = candidate;
            count++;
        }

        candidate++;
    }

    return p;
}

std::pair<double,double> quasimc(
    std::function<double(pp::vector)> f,
    pp::vector a,
    pp::vector b,
    int N
){
    int dim = a.size();

    double V = 1.0;
    for(int i=0;i<dim;i++)
        V *= (b[i] - a[i]);

    auto p = primes(dim);

    double sum = 0;
    double sum2 = 0;

    pp::vector x(dim);

    for(int i=0;i<N;i++){
        for(int k=0;k<dim;k++){
            double u = van_der_corput(i+1, p[k]);
            x[k] = a[k] + u*(b[k]-a[k]);
        }

        double fx = f(x);
        sum += fx;
        sum2 += fx*fx;
    }

    double mean = sum/N;
    double var = std::max(0.0, sum2/N - mean*mean);
    double sigma = std::sqrt(var);

    return {mean*V, sigma*V/std::sqrt(N)};
}