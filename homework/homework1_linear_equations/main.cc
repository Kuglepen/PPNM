#include <iostream>
#include <random>
#include <string>
#include <cstdlib>
#include <fstream>
#include <chrono>

#include "matrix.h"
#include "qr.h"

using namespace std;

// -------- random ----------
double rand_double(){
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_real_distribution<> dis(0.0,1.0);
    return dis(gen);
}

pp::matrix random_matrix(int n,int m){
    pp::matrix A(n,m);
    for(int i=0;i<n;i++)
    for(int j=0;j<m;j++)
        A(i,j)=rand_double();
    return A;
}

pp::vector random_vector(int n){
    pp::vector v(n);
    for(int i=0;i<n;i++) v[i]=rand_double();
    return v;
}

// -------- main ----------
int main(){

    int n = 5;

    // timing
    {
        ofstream out("data.dat");

        for(int N = 10; N <= 500; N += 10){

            pp::matrix A = random_matrix(N,N);

            auto start = chrono::high_resolution_clock::now();

            pp::qr decomp(A);

            auto end = chrono::high_resolution_clock::now();

            double time = chrono::duration<double>(end - start).count();

            out << N << " " << time << "\n";
        }

        out.close();
    }

    cout<<"n = "<<n<<"\n";

    // 1. QR TEST
    pp::matrix A = random_matrix(n,n);
    pp::qr decomp(A);

    cout<<"\n--- Checking Q^T Q = I ---\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            double sum=0;
            for(int k=0;k<n;k++)
                sum+=decomp.Q(k,i)*decomp.Q(k,j);

            if(i==j) cout<<sum-1<<" ";
            else cout<<sum<<" ";
        }
        cout<<"\n";
    }

    cout<<"\n--- Checking QR - A ---\n";
    pp::matrix QR = decomp.Q * decomp.R;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cout<<QR(i,j)-A(i,j)<<" ";
        cout<<"\n";
    }

    // 2. SOLVE TEST
    cout<<"\n--- Solve test ---\n";

    pp::vector b = random_vector(n);
    pp::vector x = decomp.solve(b);
    pp::vector Ax = A*x;

    cout<<"Ax - b:\n";
    for(int i=0;i<n;i++)
        cout<<Ax[i]-b[i]<<" ";
    cout<<"\n";

    // 3. DETERMINANT
    cout<<"\n--- Determinant ---\n";
    cout<<"det(A) = "<<decomp.det()<<"\n";

    // 4. INVERSE TEST
    cout<<"\n--- Inverse test ---\n";

    pp::matrix B = decomp.inverse();
    pp::matrix AB = A*B;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j) cout<<AB(i,j)-1<<" ";
            else cout<<AB(i,j)<<" ";
        }
        cout<<"\n";
    }

    return 0;
}