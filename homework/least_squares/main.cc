#include "lsfit.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>

int main(){
    using namespace pp;

    // 1: polynomial
    vector x1 = {0,1,2,3};
    vector y1 = {1,2,5,10};
    vector dy1 = {1,1,1,1};

    auto fs1 = std::vector<std::function<double(double)>>{
        [](double){ return 1.0; },
        [](double z){ return z; },
        [](double z){ return z*z; }
    };

    auto [c1, Sigma1] = lsfit(fs1,x1,y1,dy1);

    // 2: radioactive decay
    vector t  = {1,2,3,4,6,9,10,13,15};
    vector y2 = {117,100,88,72,53,29.5,25.2,15.2,11.1};
    vector dy2 = {6,5,4,4,4,3,3,2,2};

    vector lny(t.size()), dlny(t.size());

    for(int i=0;i<t.size();i++){
        lny[i]  = log(y2[i]);
        dlny[i] = dy2[i]/y2[i];
    }

    auto fs2 = std::vector<std::function<double(double)>>{
        [](double){ return 1.0; },
        [](double z){ return z; }
    };

    auto [c2, Sigma2] = lsfit(fs2, t, lny, dlny);

    double a = exp(c2[0]);
    double lambda = -c2[1];
    double T12 = log(2)/lambda;
    double dlambda = sqrt(Sigma2(1,1));
    double dT12 = log(2)/(lambda*lambda) * dlambda; 

    std::ofstream fout("out.txt");

    fout << "Polynomial coefficients:\n";
    for(int i=0;i<c1.size();i++){
        fout << c1[i] << " ";
    }
    fout << "\n\n";

    fout << "Radioactive decay fit:\n";
    fout << "a = " << a << "\n";
    fout << "lambda = " << lambda << " ± " << dlambda << "\n";
    fout << "Covariance matrix Sigma:\n";
    for(int i=0; i<Sigma2.size1(); i++){
        for(int j=0; j<Sigma2.size2(); j++){
            fout << Sigma2(i,j) << " ";
        }
        fout << "\n";
    }
    fout << "T1/2 = " << T12 << " ± " << dT12 << " days\n";
    fout << "Theory value: 3.6316(14) days\n";

    fout.close();


    std::ofstream out("data.dat");

    for(int i=0;i<t.size();i++){
        out << t[i] << " " << y2[i] << " " << dy2[i] << "\n";
    }

    out.close();

    std::ofstream fitout("fit.dat");

    double dc0 = sqrt(Sigma2(0,0));
    double dc1 = sqrt(Sigma2(1,1));

    for(double tt=0; tt<=15; tt+=0.1){

        // best fit
        double yfit = a * exp(-lambda * tt);

        // 4 combinations
        double a_pp = exp(c2[0] + dc0);
        double a_pm = exp(c2[0] + dc0);
        double a_mp = exp(c2[0] - dc0);
        double a_mm = exp(c2[0] - dc0);

        double lambda_pp = -(c2[1] + dc1);
        double lambda_pm = -(c2[1] - dc1);
        double lambda_mp = -(c2[1] + dc1);
        double lambda_mm = -(c2[1] - dc1);

        double y_pp = a_pp * exp(-lambda_pp * tt);
        double y_pm = a_pm * exp(-lambda_pm * tt);
        double y_mp = a_mp * exp(-lambda_mp * tt);
        double y_mm = a_mm * exp(-lambda_mm * tt);

        // envelope (min/max)
        double y_max = std::max({y_pp, y_pm, y_mp, y_mm});
        double y_min = std::min({y_pp, y_pm, y_mp, y_mm});

        fitout << tt << " " << yfit << " " << y_min << " " << y_max << "\n";
    }

    fitout.close();

    return 0;
}