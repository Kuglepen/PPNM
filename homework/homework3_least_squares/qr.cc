#include "qr.h"
#include <cmath>

namespace pp {

void qr_decomp(matrix& A, matrix& R){
    int n = A.size1();
    int m = A.size2();

    R = matrix(m,m);

    for(int k = 0; k < m; k++){
        // compute norm
        double norm = 0;
        for(int i = 0; i < n; i++){
            norm += A(i,k)*A(i,k);
        }
        norm = std::sqrt(norm);

        R(k,k) = norm;

        // normalize column k
        for(int i = 0; i < n; i++){
            A(i,k) /= norm;
        }

        // orthogonalize remaining columns
        for(int j = k+1; j < m; j++){
            double dot = 0;
            for(int i = 0; i < n; i++){
                dot += A(i,k)*A(i,j);
            }

            R(k,j) = dot;

            for(int i = 0; i < n; i++){
                A(i,j) -= A(i,k)*dot;
            }
        }
    }
}

} // namespace pp