#include "matrix.h"

namespace pp {

matrix transpose(const matrix& A) {
    matrix T(A.size2(), A.size1());
    for(int i = 0; i < A.size1(); ++i)
        for(int j = 0; j < A.size2(); ++j)
            T(j, i) = A(i, j);
    return T;
}

matrix operator*(const matrix& A, const matrix& B) {
    assert(A.size2() == B.size1());
    matrix C(A.size1(), B.size2());
    for(int i = 0; i < A.size1(); ++i)
        for(int j = 0; j < B.size2(); ++j) {
            C(i, j) = 0.0;
            for(int k = 0; k < A.size2(); ++k)
                C(i, j) += A(i, k) * B(k, j);
        }
    return C;
}

matrix diag(const vector& v) {
    int n = v.size();
    matrix D(n, n);
    for(int i = 0; i < n; ++i)
        D(i, i) = v[i];
    return D;
}

} // namespace pp