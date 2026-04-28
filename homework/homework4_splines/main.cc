#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "spline.h"

int main(){
    std::vector<double> x, y;

    // data
    for(double i=0;i<=9;i+=0.5){
        x.push_back(i);
        y.push_back(cos(i));
    }

    std::ofstream data_points("data_points.txt");

    for(size_t i=0;i<x.size();i++){
        data_points << x[i] << " " << y[i] << "\n";
    }

    data_points.close();

    //test
    double z = 2.3;

    // test linterp + integral
    std::cout << "linterp: " << linterp(x,y,z) << "\n";
    std::cout << "integral: " << linterpInteg(x,y,z) << "\n";

    // Opret quadratic spline
    qspline qs(x,y);

    // del functional C
    auto f = make_qspline(x,y);
    std::cout << "functional qspline: " << f(2.3) << "\n";

    // lav datafil til plot
    std::ofstream file("data.txt");

    for(double z=0; z<=9; z+=0.001){
        file << z << " "
            << linterp(x,y,z) << " "
            << qs.eval(z) << " "
            << linterpInteg(x,y,z) << " "
            << qs.integ(z) << "\n";
    }

    file.close();

    return 0;
}