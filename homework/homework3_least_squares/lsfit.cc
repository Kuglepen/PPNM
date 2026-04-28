#include "lsfit.h"
#include "qr.h"
#include <tuple>

namespace pp {

vector backsub(const matrix& R, const vector& b){
    int n = b.size();
    vector x(n);

    for(int i=n-1;i>=0;i--){
        double sum = 0;
        for(int j=i+1;j<n;j++){
            sum += R(i,j)*x[j];
        }
        x[i] = (b[i]-sum)/R(i,i);
    }
    return x;
}

matrix inverse_upper(const matrix& R){
    int n = R.size1();
    matrix Rinv(n,n);

    for(int i=0;i<n;i++){
        vector e(n);
        e[i] = 1.0;

        vector col = backsub(R,e);

        for(int j=0;j<n;j++){
            Rinv(j,i) = col[j];
        }
    }

    return Rinv;
}

std::tuple<vector,matrix> lsfit(
    const std::vector<std::function<double(double)>>& fs,
    const vector& x,
    const vector& y,
    const vector& dy
){
    int n = x.size();
    int m = fs.size();

    matrix A(n,m);
    vector b(n);

    for(int i=0;i<n;i++){
        b[i] = y[i]/dy[i];
        for(int k=0;k<m;k++){
            A(i,k) = fs[k](x[i])/dy[i];
        }
    }

    matrix R(m,m);
    qr_decomp(A,R);

    vector Qtb = A.T()*b;

    vector c(m);

    for(int i=m-1;i>=0;i--){
        double sum = 0;
        for(int j=i+1;j<m;j++){
            sum += R(i,j)*c[j];
        }
        c[i] = (Qtb[i]-sum)/R(i,i);
    }

    // covariance
    matrix Rinv = inverse_upper(R);
    matrix Sigma = Rinv * Rinv.T();

    return {c, Sigma};
}

}