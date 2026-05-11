#include "minimization.h"
#include "qr.h"
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <limits>

namespace pp {

// FORWARD DIFFERENCE GRADIENT
vector gradient(std::function<double(vector)> phi, vector x){
    vector g(x.size());
    double phix = phi(x);

    for(int i = 0; i < x.size(); i++){
        double dxi = (1.0 + std::abs(x[i])) * std::pow(2.0, -26);

        x[i] += dxi;
        g[i] = (phi(x) - phix) / dxi;
        x[i] -= dxi;
    }

    return g;
}

// FORWARD DIFFERENCE HESSIAN
matrix hessian(std::function<double(vector)> phi, vector x){
    int n = x.size();

    matrix H(n, n);

    vector g0 = gradient(phi, x);

    for(int j = 0; j < n; j++){

        double dxj = (1.0 + std::abs(x[j])) * std::pow(2.0, -13);

        x[j] += dxj;

        vector dg = gradient(phi, x) - g0;

        for(int i = 0; i < n; i++)
            H(i, j) = dg[i] / dxj;

        x[j] -= dxj;
    }

    return H;
}

// CENTRAL DIFFERENCE GRADIENT
vector gradient_central(std::function<double(vector)> phi, vector x){

    vector g(x.size());

    for(int i = 0; i < x.size(); i++){

        double dxi =
            (1.0 + std::abs(x[i]))
            * std::cbrt(std::numeric_limits<double>::epsilon());

        x[i] += dxi;
        double fp = phi(x);

        x[i] -= 2.0*dxi;
        double fm = phi(x);

        x[i] += dxi;

        g[i] = (fp - fm)/(2.0*dxi);
    }

    return g;
}

// CENTRAL DIFFERENCE HESSIAN
matrix hessian_central(std::function<double(vector)> phi, vector x){

    int n = x.size();

    matrix H(n,n);

    for(int j = 0; j < n; j++){

        double dxj =
            (1.0 + std::abs(x[j]))
            * std::cbrt(std::numeric_limits<double>::epsilon());

        x[j] += dxj;
        vector gp = gradient_central(phi, x);

        x[j] -= 2.0*dxj;
        vector gm = gradient_central(phi, x);

        x[j] += dxj;

        vector dg = (gp - gm)/(2.0*dxj);

        for(int i = 0; i < n; i++)
            H(i,j) = dg[i];
    }

    return H;
}

// FORWARD DIFFERENCE NEWTON MINIMIZER
std::pair<vector,int> newton_minimize(
    std::function<double(vector)> phi,
    vector x,
    double acc,
    int max_iter,
    double alpha_min
){
    for(int iter = 0; iter < max_iter; iter++){

        vector g = gradient(phi, x);

        if(g.norm() < acc)
            return {x, iter};

        matrix H = hessian(phi, x);

        // Levenberg regularization
        for(int i = 0; i < H.size1(); i++)
            H(i,i) += 1e-6;

        qr QRH(H);

        vector dx = QRH.solve(-g);

        // stopping criterion
        vector dxtol(x.size());

        for(int i = 0; i < x.size(); i++)
            dxtol[i] =
                (1.0 + std::abs(x[i]))
                * std::pow(2.0, -26);

        if(dx.norm() < dxtol.norm())
            return {x, iter};

        double lambda = 1.0;

        double fx = phi(x);

        vector z = x;

        while(true){

            z = x + lambda*dx;

            double fz = phi(z);

            if(fz < fx)
                break;

            if(lambda < alpha_min)
                break;

            lambda /= 2.0;
        }

        x = z;
    }

    return {x, max_iter};
}

// CENTRAL DIFFERENCE NEWTON MINIMIZER
std::pair<vector,int> newton_minimize_central(
    std::function<double(vector)> phi,
    vector x,
    double acc,
    int max_iter,
    double alpha_min
){
    for(int iter = 0; iter < max_iter; iter++){

        vector g = gradient_central(phi, x);

        if(g.norm() < acc)
            return {x, iter};

        matrix H = hessian_central(phi, x);

        // Levenberg regularization
        for(int i = 0; i < H.size1(); i++)
            H(i,i) += 1e-6;

        qr QRH(H);

        vector dx = QRH.solve(-g);

        vector dxtol(x.size());

        for(int i = 0; i < x.size(); i++)
            dxtol[i] =
                (1.0 + std::abs(x[i]))
                * std::cbrt(std::numeric_limits<double>::epsilon());

        if(dx.norm() < dxtol.norm())
            return {x, iter};

        double lambda = 1.0;

        double fx = phi(x);

        vector z = x;

        while(true){

            z = x + lambda*dx;

            double fz = phi(z);

            if(fz < fx)
                break;

            if(lambda < alpha_min)
                break;

            lambda /= 2.0;
        }

        x = z;
    }

    return {x, max_iter};
}

} // namespace pp