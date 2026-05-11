#include "root.h"
#include "qr.h"
#include <cmath>

// Jacobian (numerical)
matrix Jacobian(
    std::function<vector(vector)> f,
    vector x,
    vector fx
){
    int n = x.size();
    matrix J(n,n);

    vector dx(n);
    for(int i=0;i<n;i++)
        dx[i] = std::max(std::abs(x[i]),1.0)*std::pow(2,-26);

    for(int j=0;j<n;j++){
        x[j] += dx[j];
        vector df = f(x) - fx;

        for(int i=0;i<n;i++)
            J(i,j) = df[i]/dx[j];

        x[j] -= dx[j];
    }

    return J;
}

// Newton method
vector newton(
    std::function<vector(vector)> f,
    vector x,
    double acc,
    double alpha_min,
    int max_iter
){
    vector fx = f(x);

    for(int iter=0; iter<max_iter; iter++){

        if(fx.norm() < acc) break;

        matrix J = Jacobian(f, x, fx);
        pp::qr QRJ(J);

        vector Dx = QRJ.solve(-fx);

        double alpha = 1.0;
        vector z, fz;

        while(true){
            z = x + alpha*Dx;
            fz = f(z);

            if(fz.norm() < fx.norm()) break;
            if(alpha < alpha_min) break;

            alpha /= 2.0;
        }

        x = z;
        fx = fz;

        // stopping condition
        vector dx(x.size());
        for(int i=0;i<x.size();i++)
            dx[i] = std::max(std::abs(x[i]),1.0)*std::pow(2,-26);

        if(Dx.norm() < dx.norm()) break;
    }

    return x;
}