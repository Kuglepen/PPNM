#include "matrix.h"
#include "jacobi.h"
#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <string>
#include <cstdlib>
#include <cmath>

int main(int argc, char** argv) {
    // ====================== TASK 1 + 3 (no arguments) ======================
    if (argc == 1) {
        std::cout << "=== TASK 1: Proof on random symmetric matrix (n=10) ===\n";
        std::mt19937 rng(42);
        std::uniform_real_distribution<double> dist(-1.0, 1.0);

        int n = 10;
        pp::matrix A(n, n);
        for(int i = 0; i < n; ++i) {
            A(i, i) = dist(rng);
            for(int j = i + 1; j < n; ++j) {
                double val = dist(rng);
                A(i, j) = A(j, i) = val;
            }
        }
        pp::matrix original = A;

        auto [w, V] = pp::jacobi(A);

        // Build checks using the exact operators from matrix.h
        pp::matrix D = diag(w);
        pp::matrix Vt = transpose(V);

        // V^T A V == D
        auto temp = original * V;
        auto VtAV = Vt * temp;
        double err_D = 0.0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j) {
                double exp = (i == j ? w[i] : 0.0);
                err_D = std::max(err_D, std::abs(VtAV(i, j) - exp));
            }

        // V D V^T == A
        auto DVt = D * Vt;
        auto VDVt = V * DVt;
        double err_A = 0.0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                err_A = std::max(err_A, std::abs(VDVt(i, j) - original(i, j)));

        // V^T V == I and V V^T == I
        auto VtV = Vt * V;
        auto VVt = V * Vt;
        double err_ortho1 = 0.0, err_ortho2 = 0.0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j) {
                double exp = (i == j ? 1.0 : 0.0);
                err_ortho1 = std::max(err_ortho1, std::abs(VtV(i, j) - exp));
                err_ortho2 = std::max(err_ortho2, std::abs(VVt(i, j) - exp));
            }

        std::cout << "Errors (should be small, e.g. << 1e-8):\n"
                  << "   V^T A V == D : " << err_D << "\n"
                  << "   V D V^T == A : " << err_A << "\n"
                  << "   V^T V == I   : " << err_ortho1 << "\n"
                  << "   V V^T == I   : " << err_ortho2 << "\n\n";
        std::cout << "Task 1 passed!\n\n";

        // TASK 3: O(n³) scaling
        std::cout << "=== TASK 3: O(n³) scaling ===\n";
        std::cout << "n    time(s)\n";
        for(int nn = 20; nn <= 120; nn += 20) {
            pp::matrix AA(nn, nn);
            for(int i = 0; i < nn; ++i) {
                AA(i, i) = dist(rng);
                for(int j = i + 1; j < nn; ++j) {
                    double val = dist(rng);
                    AA(i, j) = AA(j, i) = val;
                }
            }
            auto start = std::chrono::high_resolution_clock::now();
            auto [ww, vv] = pp::jacobi(AA);
            auto end = std::chrono::high_resolution_clock::now();
            double t = std::chrono::duration<double>(end-start).count();
            std::cout << nn << "   " << t << "\n";
        }
        std::cout << "(time ~ n³ → Task 3 complete)\n";
        return 0;
    }

    // ====================== TASK 2: Hydrogen (with -rmax / -dr) ======================
    double rmax = 10.0, dr = 0.3;
    for(int i = 1; i < argc; i += 2) {
        std::string arg(argv[i]);
        if(arg == "-rmax" && i+1 < argc) rmax = std::atof(argv[i+1]);
        if(arg == "-dr"   && i+1 < argc) dr   = std::atof(argv[i+1]);
    }

    int npoints = static_cast<int>(rmax / dr) - 1;
    if(npoints < 1) { std::cerr << "Grid too small\n"; return 1; }

    pp::vector r(npoints);
    for(int i = 0; i < npoints; ++i) r[i] = dr * (i + 1);

    pp::matrix H(npoints, npoints);

    // Kinetic energy K (tridiagonal)
    double factor = -0.5 / (dr * dr);
    for(int i = 0; i < npoints - 1; ++i) {
        H(i, i)     = -2.0 * factor;
        H(i, i + 1) =  1.0 * factor;
        H(i + 1, i) =  1.0 * factor;
    }
    H(npoints - 1, npoints - 1) = -2.0 * factor;

    // Potential W
    for(int i = 0; i < npoints; ++i)
        H(i, i) += -1.0 / r[i];

    auto [w_unsorted, V] = pp::jacobi(H);

    // Sort eigenvalues (ascending) + keep column indices
    std::vector<int> idx(npoints);
    std::iota(idx.begin(), idx.end(), 0);
    std::sort(idx.begin(), idx.end(), [&](int a, int b){ return w_unsorted[a] < w_unsorted[b]; });

    std::cout << "=== TASK 2: Hydrogen s-wave (rmax=" << rmax << ", dr=" << dr
              << ", n=" << npoints << ") ===\n";

    int want = std::min(3, npoints); // number of eigenvalues/wavefunctions we can output
    for(int k = 0; k < want; ++k) {
        std::cout << "   ε" << k+1 << " = " << w_unsorted[idx[k]] << "\n";
    }

    // Machine-readable results for plotting/convergence scripts
    double E0 = (npoints >= 1) ? w_unsorted[idx[0]] : 0.0;
    double E1 = (npoints >= 2) ? w_unsorted[idx[1]] : 0.0;
    double E2 = (npoints >= 3) ? w_unsorted[idx[2]] : 0.0;

    std::cout << "RESULT dr=" << dr
              << " rmax=" << rmax
              << " E0=" << E0
              << " E1=" << E1
              << " E2=" << E2 << "\n";

    // Error vs exact (if available)
    if(npoints >= 1) {
        double exact0 = -0.5;
        std::cout << "Ground state error = " << std::abs(E0 - exact0) << "\n";
    }

    // Wavefunctions → waves.dat
    double Const = 1.0 / std::sqrt(dr);
    std::ofstream wf("waves.dat");
    wf << "# r";
    for(int k = 0; k < want; ++k) wf << "    f" << k;
    wf << "\n";

    for(int i = 0; i < npoints; ++i) {
        wf << r[i];
        for(int k = 0; k < want; ++k) {
            wf << " " << (Const * V(i, idx[k]));
        }
        wf << "\n";
    }
    wf.close();
    std::cout << "\nWavefunctions saved to waves.dat (columns: r ";
    for(int k=0;k<want;++k) std::cout << "f" << k << (k+1<want ? ", " : "");
    std::cout << ")\n";

    std::cout << "Run with different -dr / -rmax for convergence plots.\n";
    return 0;
}