#include "qr.h"
#include <cmath>
#include <stdexcept>

namespace pp {

// Gram-Schmidt
qr::qr(const matrix& A) : Q(A), R(A.size2(), A.size2()) {

    int n = Q.size1();
    int m = Q.size2();

    for(int j = 0; j < m; j++){

        // norm
        double norm = 0;
        for(int i = 0; i < n; i++)
            norm += Q(i,j)*Q(i,j);

        norm = std::sqrt(norm);

        if(norm == 0) throw std::runtime_error("Matrix is rank deficient");

        R(j,j) = norm;

        // normalize column j
        for(int i = 0; i < n; i++)
            Q(i,j) /= norm;

        // orthogonalize remaining columns
        for(int k = j+1; k < m; k++){

            double dot = 0;
            for(int i = 0; i < n; i++)
                dot += Q(i,j)*Q(i,k);

            R(j,k) = dot;

            for(int i = 0; i < n; i++)
                Q(i,k) -= Q(i,j)*dot;
        }
    }
}

// Solve Ax = b
vector qr::solve(const vector& b) const {

    int m = R.size2();

    // y = Q^T b
    vector y(m);

    for(int i = 0; i < m; i++){
        y[i] = 0;
        for(int k = 0; k < Q.size1(); k++)
            y[i] += Q(k,i)*b[k];
    }

    vector x(m);

    for(int i = m-1; i >= 0; i--){
        double sum = y[i];

        for(int k = i+1; k < m; k++)
            sum -= R(i,k)*x[k];

        x[i] = sum / R(i,i);
    }

    return x;
}

// Determinant
double qr::det() const {
    double d = 1;
    for(int i = 0; i < R.size2(); i++)
        d *= R(i,i);
    return d;
}

// Inverse
matrix qr::inverse() const {

    int n = Q.size1();
    int m = Q.size2();

    matrix B(m,m);

    vector e(n);

    for(int i = 0; i < m; i++){

        // reset e
        for(int j = 0; j < n; j++) e[j] = 0;

        e[i] = 1;

        vector x = solve(e);

        for(int k = 0; k < m; k++)
            B(k,i) = x[k];
    }

    return B;
}

}