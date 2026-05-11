#pragma once
#include <functional>
#include "matrix.h"

namespace pp {

struct ann {
    int n;
    std::function<double(double)> f;
    vector p;

    ann(int n);

    double response(double x) const;
    double response1(double x) const;
    double response2(double x) const;
    double antiderivative(double x) const;

    void train(const vector& xs, const vector& ys);

private:
    double response(const vector& u, double x) const;
    static double safe_b(double b);
    static double phi(double z);
    static double dphi(double z);
    static double ddphi(double z);
    static double intphi(double z);
};

} // namespace pp