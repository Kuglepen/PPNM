#pragma once
#include <vector>
#include <cassert>

namespace pp {

// -------- VECTOR --------
struct vector {
    std::vector<double> data;

    vector(int n) : data(n,0.0) {}

    int size() const { return data.size(); }

    double& operator[](int i){
        assert(i>=0 && i<size());
        return data[i];
    }

    double operator[](int i) const {
        assert(i>=0 && i<size());
        return data[i];
    }
};

// -------- MATRIX --------
struct matrix {
    int n,m;
    std::vector<double> data;

    matrix(int n_, int m_) : n(n_), m(m_), data(n_*m_,0.0) {}

    int size1() const { return n; }
    int size2() const { return m; }

    double& operator()(int i,int j){
        return data[i*m+j];
    }

    double operator()(int i,int j) const{
        return data[i*m+j];
    }

    void setid(){
        assert(n==m);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                (*this)(i,j) = (i==j ? 1.0 : 0.0);
    }
};

// -------- DECLARATIONS --------
matrix transpose(const matrix& A);
matrix operator*(const matrix& A, const matrix& B);
matrix diag(const vector& v);

}